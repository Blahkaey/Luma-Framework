#pragma once
#if !OFFLINE_PATCHER
#include "..\..\..\Core\includes\shader_patching.h"
#else
#include "..\..\..\External/WDK/includes/d3d11TokenizedProgramFormat.hpp"
#endif
#include <cstdint>
#include <vector>
#include <utility>

struct OperandInfo {
    uint32_t operand_type;      // D3D10_SB_OPERAND_TYPE
    uint32_t register_index;    // The register number (e.g., 0 for o0, 1 for cb1)
    uint32_t byte_offset;       // Offset within the instruction where the register index is stored
    uint32_t instruction_offset;    // Offset within the instruction where OperandToken0 starts
};

struct InstructionOperands {
    std::vector<OperandInfo> constant_buffer_reads;  // CB reads (source operands)
    std::vector<OperandInfo> output_writes;           // Output writes (dest operands)
};

// Track extended opcode info that affects operand layout
struct ExtendedOpcodeInfo {
    uint32_t type;
    bool has_resource_dim;
    bool has_resource_return_type;
    uint32_t resource_dimension;
    uint32_t structure_stride;
};

// Helper function to decode operand index representation and get the index value
uint32_t decode_operand_index(const std::byte* instruction, 
                               uint32_t& current_offset,
                               uint32_t index_representation,
                               uint32_t operand_type) {
    uint32_t index_value = 0;
    
    switch (index_representation) {
        case D3D10_SB_OPERAND_INDEX_IMMEDIATE32: {
            // Index is a single DWORD
            index_value = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 4;
            break;
        }
        case D3D10_SB_OPERAND_INDEX_IMMEDIATE64: {
            // Index is two DWORDs (64-bit)
            uint32_t low = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 8;  // Skip both DWORDs
            index_value = low;    // Usually use low 32 bits for register index
            break;
        }
        case D3D10_SB_OPERAND_INDEX_RELATIVE: {
            // Relative addressing - need to parse another operand inline
            uint32_t rel_op_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 4;
            
            // Check if this relative operand is extended
            if (rel_op_token & D3D10_SB_OPERAND_EXTENDED_MASK) {
                current_offset += 4; // Skip extended operand token
                
                // Check for double extended
                uint32_t next_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset - 4);
                if (next_token & D3D10_SB_OPERAND_DOUBLE_EXTENDED_MASK) {
                    current_offset += 4; // Skip second extended token
                }
            }
            
            // Get index dimension of the relative operand
            uint32_t rel_index_dim = DECODE_D3D10_SB_OPERAND_INDEX_DIMENSION(rel_op_token);
            
            // Skip indices for relative operand
            for (uint32_t dim = 0; dim < rel_index_dim; dim++) {
                uint32_t rel_index_rep = DECODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(dim, rel_op_token);
                
                // Handle immediate values
                if (rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE32 ||
                    rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE) {
                    current_offset += 4;
                } else if (rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE64 ||
                           rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE64_PLUS_RELATIVE) {
                    current_offset += 8;
                }
                
                // Handle relative part for plus_relative types
                if (rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE ||
                    rel_index_rep == D3D10_SB_OPERAND_INDEX_IMMEDIATE64_PLUS_RELATIVE) {
                    // Skip the nested relative operand
                    uint32_t nested_rel = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
                    current_offset += 4;
                    if (nested_rel & D3D10_SB_OPERAND_EXTENDED_MASK) {
                        current_offset += 4;
                        if (*reinterpret_cast<const uint32_t*>(instruction + current_offset - 4) & D3D10_SB_OPERAND_DOUBLE_EXTENDED_MASK) {
                            current_offset += 4;
                        }
                    }
                    // Skip nested indices (simplified - assume 1D immediate for register)
                    current_offset += 4;
                }
            }
            index_value = 0; // Unknown for relative addressing
            break;
        }
        case D3D10_SB_OPERAND_INDEX_IMMEDIATE32_PLUS_RELATIVE: {
            // Immediate DWORD followed by relative operand
            index_value = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 4;
            
            // Skip the relative part
            uint32_t rel_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 4;
            if (rel_token & D3D10_SB_OPERAND_EXTENDED_MASK) {
                current_offset += 4;
                if (*reinterpret_cast<const uint32_t*>(instruction + current_offset - 4) & D3D10_SB_OPERAND_DOUBLE_EXTENDED_MASK) {
                    current_offset += 4;
                }
            }
            // Skip relative operand indices (simplified for register index)
            current_offset += 4;
            break;
        }
        case D3D10_SB_OPERAND_INDEX_IMMEDIATE64_PLUS_RELATIVE: {
            // Two DWORDs followed by relative operand
            index_value = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 8;
            
            // Skip the relative part
            uint32_t rel_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
            current_offset += 4;
            if (rel_token & D3D10_SB_OPERAND_EXTENDED_MASK) {
                current_offset += 4;
                if (*reinterpret_cast<const uint32_t*>(instruction + current_offset - 4) & D3D10_SB_OPERAND_DOUBLE_EXTENDED_MASK) {
                    current_offset += 4;
                }
            }
            // Skip relative operand indices (simplified for register index)
            current_offset += 4;
            break;
        }
    }
    
    return index_value;
}

// Parse extended opcodes and return info about how they modify operand layout
ExtendedOpcodeInfo parse_extended_opcodes(const std::byte* instruction, 
                                          uint32_t& current_offset,
                                          uint32_t instruction_length) {
    ExtendedOpcodeInfo ext_info = {};
    ext_info.type = D3D10_SB_EXTENDED_OPCODE_EMPTY;
    ext_info.has_resource_dim = false;
    ext_info.has_resource_return_type = false;
    
    // Keep parsing extended opcodes as long as the extended bit is set
    bool has_extended = (*(uint32_t*)instruction & D3D10_SB_OPCODE_EXTENDED_MASK) != 0;
    
    while (has_extended && current_offset < instruction_length * 4) {
        uint32_t ext_opcode_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
        uint32_t ext_type = DECODE_D3D10_SB_EXTENDED_OPCODE_TYPE(ext_opcode_token);
        
        switch (ext_type) {
            case D3D10_SB_EXTENDED_OPCODE_SAMPLE_CONTROLS:
                // Sample controls adds extra operands for texture coordinates and sampler
                ext_info.type = ext_type;
                // SAMPLE instruction with controls has: sampler, texture, coordinates
                break;
                
            case D3D11_SB_EXTENDED_OPCODE_RESOURCE_DIM:
                // Resource dimension extended opcode adds a resource dimension operand
                ext_info.has_resource_dim = true;
                ext_info.resource_dimension = DECODE_D3D11_SB_EXTENDED_RESOURCE_DIMENSION(ext_opcode_token);
                if (ext_info.resource_dimension == D3D11_SB_RESOURCE_DIMENSION_STRUCTURED_BUFFER) {
                    ext_info.structure_stride = DECODE_D3D11_SB_EXTENDED_RESOURCE_DIMENSION_STRUCTURE_STRIDE(ext_opcode_token);
                }
                break;
                
            case D3D11_SB_EXTENDED_OPCODE_RESOURCE_RETURN_TYPE:
                // Resource return type adds return type operands for each component
                ext_info.has_resource_return_type = true;
                break;
        }
        
        current_offset += 4;
        
        // Check if there are more extended opcodes
        has_extended = (ext_opcode_token & D3D10_SB_OPCODE_EXTENDED_MASK) != 0;
    }
    
    return ext_info;
}

// Main function to extract operand information from a single instruction
InstructionOperands get_instruction_operands(const std::byte* instruction) {
    InstructionOperands result;
    
    // Read OpcodeToken0
    uint32_t opcode_token0 = *reinterpret_cast<const uint32_t*>(instruction);
    uint32_t current_offset = 4; // Start after OpcodeToken0
    
    // Get opcode type and instruction length
    uint32_t opcode_type = DECODE_D3D10_SB_OPCODE_TYPE(opcode_token0);
    uint32_t instruction_length = DECODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(opcode_token0);
    uint32_t instruction_end = instruction_length * 4;
    
    // Parse extended opcodes that modify operand layout
    ExtendedOpcodeInfo ext_info = parse_extended_opcodes(instruction, current_offset, instruction_length);
    
    // Handle special opcodes that have specific operand layouts
    bool is_sample_instruction = (ext_info.type == D3D10_SB_EXTENDED_OPCODE_SAMPLE_CONTROLS);
    
    // Parse operands until we reach the end of the instruction
    while (current_offset < instruction_end) {
        // Read OperandToken0
        uint32_t operand_token0 = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
        uint32_t operand_start = current_offset;
        current_offset += 4;
        
        // Get operand type
        uint32_t operand_type = DECODE_D3D10_SB_OPERAND_TYPE(operand_token0);
        
        // Check for extended operand tokens
        bool has_extended = (operand_token0 & D3D10_SB_OPERAND_EXTENDED_MASK) != 0;
        if (has_extended) {
            // Skip extended operand token(s)
            while (current_offset < instruction_end) {
                uint32_t ext_operand_token = *reinterpret_cast<const uint32_t*>(instruction + current_offset);
                current_offset += 4;
                
                // Check if there's another extended operand token
                if (!(ext_operand_token & D3D10_SB_OPERAND_DOUBLE_EXTENDED_MASK)) {
                    break;
                }
            }
        }
        
        // Get index dimension
        uint32_t index_dim = DECODE_D3D10_SB_OPERAND_INDEX_DIMENSION(operand_token0);
        
        // Handle different operand types
        switch (operand_type) {
            case D3D10_SB_OPERAND_TYPE_IMMEDIATE32: {
                uint32_t num_components = DECODE_D3D10_SB_OPERAND_NUM_COMPONENTS(operand_token0);
                if (num_components == D3D10_SB_OPERAND_1_COMPONENT) {
                    current_offset += 4;
                } else if (num_components == D3D10_SB_OPERAND_4_COMPONENT) {
                    current_offset += 16;
                }
                continue; // Skip to next operand
            }
            
            case D3D10_SB_OPERAND_TYPE_IMMEDIATE64: {
                uint32_t num_components = DECODE_D3D10_SB_OPERAND_NUM_COMPONENTS(operand_token0);
                if (num_components == D3D10_SB_OPERAND_1_COMPONENT) {
                    current_offset += 8;
                } else if (num_components == D3D10_SB_OPERAND_4_COMPONENT) {
                    current_offset += 32;
                }
                continue; // Skip to next operand
            }
            
            case D3D10_SB_OPERAND_TYPE_SAMPLER:
            case D3D10_SB_OPERAND_TYPE_RESOURCE: {
                // For sample instructions, track resource and sampler indices
                if (index_dim > 0) {
                    for (uint32_t dim = 0; dim < index_dim; dim++) {
                        uint32_t index_rep = DECODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(dim, operand_token0);
                        uint32_t index_value = decode_operand_index(instruction, current_offset, index_rep, operand_type);
                    }
                }
                continue; // These are not CB or output registers
            }
            
            default: {
                // Process indices for the operand
                for (uint32_t dim = 0; dim < index_dim; dim++) {
                    uint32_t index_rep = DECODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(dim, operand_token0);
                    
                    // Record the offset where the index value will be read
                    uint32_t index_offset = current_offset;
                    
                    // Decode the index and advance the offset
                    uint32_t index_value = decode_operand_index(instruction, current_offset, index_rep, operand_type);
                    
                    // For constant buffers: dim 0 is the cb register slot (cb0, cb1, etc.)
                    if (operand_type == D3D10_SB_OPERAND_TYPE_CONSTANT_BUFFER && dim == 0) {
                        OperandInfo info;
                        info.operand_type = operand_type;
                        info.register_index = index_value;
                        info.byte_offset = index_offset;
                        info.instruction_offset = operand_start;
                        result.constant_buffer_reads.push_back(info);
                    }
                    // For outputs: dim 0 is the output register index (o0, o1, etc.)
                    else if ((operand_type == D3D10_SB_OPERAND_TYPE_OUTPUT ||
                              operand_type == D3D11_SB_OPERAND_TYPE_OUTPUT_DEPTH_GREATER_EQUAL ||
                              operand_type == D3D11_SB_OPERAND_TYPE_OUTPUT_DEPTH_LESS_EQUAL ||
                              operand_type == D3D10_SB_OPERAND_TYPE_OUTPUT_DEPTH) && dim == 0) {
                        OperandInfo info;
                        info.operand_type = operand_type;
                        info.register_index = index_value;
                        info.byte_offset = index_offset;
                        info.instruction_offset = operand_start;
                        result.output_writes.push_back(info);
                    }
                }
                break;
            }
        }
    }
    
    return result;
}

void AnalyzeShaderInstructionAtPosition(std::byte* shader_code, uint32_t position) {
    std::byte* instruction_start = shader_code + position;
    InstructionOperands analysis = get_instruction_operands(instruction_start);
    
    // Process constant buffer accesses
    for (const auto& cb_access : analysis.constant_buffer_reads) {
        printf("Constant Buffer access:\n");
        printf("  CB Slot offset: %u\n", cb_access.byte_offset);
        printf("  CB Slot value: %u\n", cb_access.register_index);
    }
    
    // Process output accesses
    for (const auto& out_access : analysis.output_writes) {
        printf("Output access:\n");
        printf("  Output index offset: %u\n", out_access.byte_offset);
        printf("  Output index value: %u\n", out_access.register_index);
    }
}