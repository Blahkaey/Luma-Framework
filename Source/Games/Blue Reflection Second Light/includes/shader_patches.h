#pragma once
#if !OFFLINE_PATCHER
#include "..\..\..\Core\includes\shader_patching.h"
#else
#include "..\..\..\External/WDK/includes/d3d11TokenizedProgramFormat.hpp"
#endif
#include "..\includes/shader_helper.h"

struct RDEFHeader
{
   char chunk_name[4]; // 'RDEF'
   uint32_t chunk_size;
   uint32_t constant_buffer_count;
   uint32_t constant_buffer_offset;
   uint32_t resource_binding_count;
   uint32_t resource_binding_offset;
   uint8_t version_minor;
   uint8_t version_major;
   uint16_t program_type;
   uint32_t flags;
   uint32_t creator_string_offset;
};

struct ConstantBufferDesc
{
   uint32_t name_offset;
   uint32_t variable_count;
   uint32_t variable_desc_offset;
   uint32_t size;
   uint32_t flags;
   uint32_t cbuffer_type;
};

struct ResourceBindingDesc
{
   uint32_t name_offset;
   uint32_t input_type;
   uint32_t resource_return_type;
   uint32_t view_dimension;
   uint32_t sample_count;
   uint32_t bind_point;
   uint32_t bind_count;
   uint32_t flags;
};

struct VariableDesc
{
   uint32_t name_offset;
   uint32_t data_offset;
   uint32_t size;
   uint32_t flags;
   uint32_t type_offset;
   uint32_t default_value_offset;
   uint32_t start_texture;
   uint32_t texture_size;
   uint32_t start_sampler;
   uint32_t sampler_size;
};

struct VariableTypeDesc
{
   uint16_t variable_class;
   uint16_t variable_type;
   uint16_t row_count;
   uint16_t column_count;
   uint16_t element_count;
   uint16_t member_count;
   uint32_t member_offset;
   uint8_t reserved[16];
   uint32_t name_offset;
};

struct DXBCSignatureEntry
{
   uint32_t name_offset;
   uint32_t semantic_index;
   uint32_t value_type;
   uint32_t component_type;
   uint32_t reg;
   uint8_t component_mask;
   uint8_t read_write_mask;
};

struct SHEXHeader
{
   char chunk_name[4]; // 'SHEX'
   uint32_t chunk_size;
   uint8_t version;
   uint16_t type;
   uint32_t dword_count;
};

struct OutputWriteEntry
{
   uint32_t index = 255;
   uint32_t index_offset;
   uint32_t instruction_length;
   uint32_t instruction_offset;
};

void PatchVertexShader(std::vector<std::byte>& shader_code)
{
   DXBCHeader* dxbc_header = (DXBCHeader*)&shader_code[0];

   for (uint32_t i = 0; i < dxbc_header->chunk_count; ++i)
   {
      if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "RDEF", 4) == 0)
      {
         uint32_t rdef_offset = dxbc_header->chunk_offsets[i];
         std::byte* rdef = &shader_code[dxbc_header->chunk_offsets[i]];
         RDEFHeader* rdef_header = (RDEFHeader*)rdef;
         uint32_t rdef_header_offset = rdef_offset + 8;
         uint32_t inserted_bytes = 0;
         ConstantBufferDesc* constant_buffers = (ConstantBufferDesc*)&shader_code[rdef_header_offset + rdef_header->constant_buffer_offset];
         ResourceBindingDesc* resource_bindings = (ResourceBindingDesc*)&shader_code[rdef_header_offset + rdef_header->resource_binding_offset];
         
         int globals_cb_index = -1;
         for (uint32_t j = 0; j < rdef_header->constant_buffer_count; ++j)
         {
            const char* name = (char*)&shader_code[rdef_header_offset + constant_buffers[j].name_offset];
            if (strcmp(name, "$Globals") == 0)
            {
               globals_cb_index = j;
               break;
            }
         }
         
         if (globals_cb_index == -1)
            return; // $Globals not found

         // Size is 12 byte to avoid padding bytes
         const char new_cb_name[] = "GlobalsPrev";
         inserted_bytes += sizeof(new_cb_name);
         inserted_bytes += sizeof(ResourceBindingDesc);
         inserted_bytes += sizeof(ConstantBufferDesc);
         std::vector<uint32_t> td;
         std::vector<std::string> vn;
         std::vector<VariableDesc> vd(constant_buffers[globals_cb_index].variable_count);
         for (uint32_t j = 0; j < rdef_header->constant_buffer_count; ++j)
         {
            for (uint32_t l = 0; l < constant_buffers[j].variable_count; ++l)
            {
               VariableDesc* variable_desc = (VariableDesc*)&shader_code[rdef_header_offset + constant_buffers[j].variable_desc_offset + l * sizeof(VariableDesc)];
               //variable_type_desc->name_offset += inserted_bytes;
               if (std::find(td.begin(), td.end(), variable_desc->type_offset) == td.end()) {
                  td.emplace_back(variable_desc->type_offset);
               }
               variable_desc->type_offset += inserted_bytes;
               if (j == globals_cb_index)
               {
                  vd[l] = (*variable_desc);
                  std::string name = (const char*)&shader_code[rdef_header_offset + variable_desc->name_offset];
                  vn.push_back(name + "Prev");
               }
               variable_desc->name_offset += inserted_bytes;
            }
            constant_buffers[j].name_offset += sizeof(ResourceBindingDesc);
            constant_buffers[j].variable_desc_offset += inserted_bytes;
         }
         for (uint32_t j = 0; j < td.size(); ++j)
         {
            VariableTypeDesc* variable_type_desc = (VariableTypeDesc*)&shader_code[rdef_header_offset + td[j]];
            variable_type_desc->name_offset += inserted_bytes;
         }
         
         rdef_header->constant_buffer_count += 1;
         ConstantBufferDesc cbd;
         cbd = constant_buffers[globals_cb_index];
         cbd.name_offset = rdef_header->constant_buffer_offset + sizeof(ResourceBindingDesc);
         cbd.variable_desc_offset = rdef_header->chunk_size + inserted_bytes;
         
         shader_code.insert(
            shader_code.begin() + rdef_header_offset + rdef_header->constant_buffer_offset,
            sizeof(new_cb_name) + sizeof(ConstantBufferDesc),
            std::byte{}
         );
         memcpy(
            shader_code.data() + rdef_header_offset + rdef_header->constant_buffer_offset,
            new_cb_name,
            sizeof(new_cb_name)
         );
         memcpy(
           shader_code.data() + rdef_header_offset + rdef_header->constant_buffer_offset + sizeof(new_cb_name),
           &cbd,
           sizeof(cbd)
        );
         
         rdef = &shader_code[dxbc_header->chunk_offsets[i]];
         rdef_header = (RDEFHeader*)rdef;
         dxbc_header = (DXBCHeader*)&shader_code[0];
         resource_bindings = (ResourceBindingDesc*)&shader_code[rdef_header_offset + rdef_header->resource_binding_offset];
         
         for (uint32_t j = 0; j < rdef_header->resource_binding_count; ++j)
         {
            resource_bindings[j].name_offset += sizeof(ResourceBindingDesc);
         }
         rdef_header->constant_buffer_offset += sizeof(ResourceBindingDesc) + sizeof(new_cb_name);
         rdef_header->chunk_size += inserted_bytes;
         rdef_header->creator_string_offset += inserted_bytes;
         
         ResourceBindingDesc globals_bd;
         globals_bd.name_offset = rdef_header->constant_buffer_offset - sizeof(new_cb_name);
         globals_bd.input_type = 0;
         globals_bd.resource_return_type = 0;
         globals_bd.view_dimension = 0;
         globals_bd.sample_count = 0;
         globals_bd.bind_point = 5; //cb5
         globals_bd.bind_count = 1;
         globals_bd.flags = 0;
         rdef_header->resource_binding_count += 1;
         shader_code.insert(
            shader_code.begin() + rdef_header_offset + 60 + (rdef_header->resource_binding_count - 1) * sizeof(ResourceBindingDesc),
            (std::byte*)&globals_bd,
            (std::byte*)&globals_bd + sizeof(ResourceBindingDesc)
         );
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         rdef_header = (RDEFHeader*)rdef;
         rdef = &shader_code[dxbc_header->chunk_offsets[i]];
         uint32_t prev_cb_insert_offset = rdef_header->chunk_size;
         uint32_t prev_cb_string_table_offset = prev_cb_insert_offset + sizeof(VariableDesc) * vd.size();
         uint32_t total_string_size = 0;
         for (uint32_t j = 0; j < vd.size(); ++j)
         {
            if (j == 0)
            {
               vd[j].name_offset = prev_cb_string_table_offset;
            }
            else
            {
               vd[j].name_offset = vd[j-1].name_offset + (uint32_t)vn[j-1].length() + 1;
            }
            total_string_size += vn[j].length() + 1;
         }
         
         if (total_string_size % 4 != 0)
            total_string_size += 4 - (total_string_size % 4);
         
         inserted_bytes += total_string_size + vd.size() * sizeof(VariableDesc);
         rdef_header->chunk_size += total_string_size + vd.size() * sizeof(VariableDesc);
         
         shader_code.insert(
      shader_code.begin() + rdef_header_offset + prev_cb_insert_offset,
      sizeof(VariableDesc) * vd.size() + total_string_size,
            std::byte{}
         );
         
         uint32_t current_string_offset = rdef_header_offset + prev_cb_string_table_offset;
         for (const auto& str : vn)
         {
            uint32_t str_size = (uint32_t)str.length() + 1; // Include null terminator
            memcpy(shader_code.data() + current_string_offset, str.c_str(), str_size);
            current_string_offset += str_size;
         }
         
         for (uint32_t j = 0; j < vd.size(); ++j)
         {
            memcpy(shader_code.data() + rdef_header_offset + j * sizeof(VariableDesc) + prev_cb_insert_offset, &vd[j], sizeof(VariableDesc));
         }
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
         {
            dxbc_header->chunk_offsets[j] += inserted_bytes;
         }
      }
      else if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "OSGN", 4) == 0)
      {
         std::byte* osgn = &shader_code[dxbc_header->chunk_offsets[i]];
         uint32_t osgn_size = *(uint32_t*)(osgn + 4);
         uint32_t osgn_entry_count = *(uint32_t*)(osgn + 8);
         DXBCSignatureEntry* osgn_entries = (DXBCSignatureEntry*)(osgn + 16);
         uint32_t texcoord_name_offset = 0;
         uint32_t texcoord_last_index = 0;
         uint32_t inserted_bytes = sizeof(DXBCSignatureEntry)*2;
         for (uint32_t j = 0; j < osgn_entry_count; ++j)
         {
            const char* name = (const char*)(osgn + 8 + osgn_entries[j].name_offset);
            if (strncmp(name, "TEXCOORD", 8) == 0)
            {
               texcoord_last_index++;
               if (texcoord_name_offset == 0)
               {
                  texcoord_name_offset = osgn_entries[j].name_offset;
               }
            }
            osgn_entries[j].name_offset += sizeof(DXBCSignatureEntry)*2;
         }
         auto Align4 = [](uint32_t v)
         {
            return (v + 3) & ~3;
         };
         
         if (texcoord_name_offset == 0)
         {
            uint32_t old_aligned_end = dxbc_header->chunk_offsets[i] + 8 + osgn_size;
            const char texcoord_name[] = "TEXCOORD";
            texcoord_name_offset = osgn_size;
            uint32_t new_end = old_aligned_end + sizeof(texcoord_name);
            uint32_t new_aligned_end = Align4(new_end);
            uint32_t string_insert_size = new_aligned_end - old_aligned_end;

            // Insert TEXCOORD + alignment padding
            shader_code.insert(
                shader_code.begin() + old_aligned_end,
                string_insert_size,
                std::byte{}
            );
            memcpy(
                shader_code.data() + old_aligned_end,
                texcoord_name,
                sizeof(texcoord_name)
            );

            inserted_bytes += string_insert_size;
            
            dxbc_header = (DXBCHeader*)&shader_code[0];
            osgn = &shader_code[dxbc_header->chunk_offsets[i]];
         }
         DXBCSignatureEntry current_pos_signature;
         current_pos_signature.name_offset = texcoord_name_offset+sizeof(DXBCSignatureEntry)*2;
         current_pos_signature.semantic_index = texcoord_last_index;
         current_pos_signature.value_type = 0;
         current_pos_signature.component_type = 3;
         current_pos_signature.reg = osgn_entry_count;
         current_pos_signature.component_mask = 15;
         current_pos_signature.read_write_mask = 0;
         
         DXBCSignatureEntry previous_pos_signature;
         previous_pos_signature.name_offset = texcoord_name_offset+sizeof(DXBCSignatureEntry)*2;
         previous_pos_signature.semantic_index = texcoord_last_index+1;
         previous_pos_signature.value_type = 0;
         previous_pos_signature.component_type = 3;
         previous_pos_signature.reg = osgn_entry_count+1;
         previous_pos_signature.component_mask = 15;
         previous_pos_signature.read_write_mask = 0;
         
         *(uint32_t*)(osgn + 4) += inserted_bytes;
         *(uint32_t*)(osgn + 8) += 2;
         shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + 16 + osgn_entry_count * sizeof(DXBCSignatureEntry),
            (std::byte*)&current_pos_signature,
            (std::byte*)&current_pos_signature + sizeof(DXBCSignatureEntry));
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + 16 + (osgn_entry_count+1) * sizeof(DXBCSignatureEntry),
            (std::byte*)&previous_pos_signature,
            (std::byte*)&previous_pos_signature + sizeof(DXBCSignatureEntry));
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
         {
            dxbc_header->chunk_offsets[j] += inserted_bytes;
         }
      }
      else if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "SHEX", 4) == 0)
      {
         std::byte* shex = &shader_code[dxbc_header->chunk_offsets[i]];
         SHEXHeader* shex_header = (SHEXHeader*)shex;
         
         uint32_t pos = 16;
         uint32_t sv_position_index = 0;
         uint32_t original_output_count = 0;
         uint32_t first_instruction_offset = 0;
         uint32_t last_sv_position_write_offset = 0;
         // +8 from shex chunk header
         uint32_t ret_insert_offset = shex_header->dword_count * 4 + 8 - 4;
         std::vector<OutputWriteEntry> output_write_offsets;
         std::vector<uint32_t> cb_global_read_offsets;
         
         bool has_inserted_output_dcl = false;
         
         D3D10_SB_OPCODE_TYPE prev_opcode_type = D3D10_SB_NUM_OPCODES;
         for (;;)
         {
            D3D10_SB_OPCODE_TYPE opcode_type = DECODE_D3D10_SB_OPCODE_TYPE(*(uint32_t*)(shex + pos));
            const uint32_t len = DECODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(*(uint32_t*)(shex + pos));
            
            if (opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT_SIV)
            {
               D3D10_SB_NAME type = DECODE_D3D10_SB_NAME(*(uint32_t*)(shex + pos + 3 * 4));
               if (type == D3D10_SB_NAME_POSITION)
                  sv_position_index = *(uint32_t*)(shex + pos + 2 * 4);
            }
            
            if (opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT)
            {
               original_output_count = *(uint32_t*)(shex + pos + 2 * 4);
            }
            
            if (opcode_type == D3D10_SB_OPCODE_DCL_CONSTANT_BUFFER)
            {
               std::vector<uint32_t> shader_patch(len);
               memcpy(&shader_patch[0], shex + pos, len * 4);
               shader_patch[len - 2] = 5;
               shader_code.insert(
                  shader_code.begin() + dxbc_header->chunk_offsets[i] + pos + len * 4,
                  (std::byte*)&shader_patch[0],
                  (std::byte*)(&shader_patch[0] + shader_patch.size())
               );
               
               shex = &shader_code[dxbc_header->chunk_offsets[i]];
               shex_header = (SHEXHeader*)shex;
               shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
               shex_header->dword_count += shader_patch.size();
               dxbc_header = (DXBCHeader*)&shader_code[0];
               for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
               {
                  dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
               }
               prev_opcode_type = D3D10_SB_NUM_OPCODES;
               pos += shader_patch.size() * 4;
               ret_insert_offset += shader_patch.size() * 4;
            }
            //else if ((opcode_type != D3D10_SB_OPCODE_DCL_OUTPUT && prev_opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT) ||
            //         (opcode_type != D3D10_SB_OPCODE_DCL_OUTPUT && prev_opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT_SIV))
            else if ( (opcode_type != D3D10_SB_OPCODE_DCL_OUTPUT && opcode_type != D3D10_SB_OPCODE_DCL_OUTPUT_SIV) &&
                      (prev_opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT || prev_opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT_SIV) )
            {
               uint32_t opcode_token =
                  ENCODE_D3D10_SB_OPCODE_TYPE(D3D10_SB_OPCODE_DCL_OUTPUT) |
                  ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(3) |
                  ENCODE_D3D10_SB_INSTRUCTION_SATURATE(false);
               uint32_t operand_token =
                  ENCODE_D3D10_SB_OPERAND_NUM_COMPONENTS(D3D10_SB_OPERAND_4_COMPONENT) |
                  ENCODE_D3D10_SB_OPERAND_4_COMPONENT_SELECTION_MODE(D3D10_SB_OPERAND_4_COMPONENT_MASK_MODE) |
                  ENCODE_D3D10_SB_OPERAND_4_COMPONENT_MASK(0xF0) |
                  ENCODE_D3D10_SB_OPERAND_TYPE(D3D10_SB_OPERAND_TYPE_OUTPUT) |
                  ENCODE_D3D10_SB_OPERAND_INDEX_DIMENSION(D3D10_SB_OPERAND_INDEX_1D) |
                  ENCODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(0, D3D10_SB_OPERAND_INDEX_IMMEDIATE32);
               std::vector<uint32_t> shader_patch{
                  opcode_token,
                  operand_token, original_output_count+1,
                  opcode_token,
                  operand_token, original_output_count+2,
               };

               shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + pos, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
               shex = &shader_code[dxbc_header->chunk_offsets[i]];
               shex_header = (SHEXHeader*)shex;
               shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
               shex_header->dword_count += shader_patch.size();
               dxbc_header = (DXBCHeader*)&shader_code[0];
               for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
               {
                  dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
               }
               prev_opcode_type = D3D10_SB_NUM_OPCODES;
               pos += shader_patch.size() * sizeof(uint32_t);
               ret_insert_offset += shader_patch.size() * 4;
               
               if (opcode_type == D3D10_SB_OPCODE_DCL_TEMPS)
               {
                  first_instruction_offset = pos + len * 4;
               }
               else
               {
                  first_instruction_offset = pos;
                  // we need to read this instruction as well
                  pos -= len * 4;
               }
               
               has_inserted_output_dcl = true;
            }
            else if (first_instruction_offset != 0)
            {
               //AnalyzeShaderInstructionAtPosition(shex, pos);
               
               std::byte* instruction_start = shex + pos;
               InstructionOperands analysis = get_instruction_operands(instruction_start);
               // Process constant buffer accesses
               for (const auto& cb_access : analysis.constant_buffer_reads) {
                  if (cb_access.register_index == 0)
                  {
                     uint32_t offset = cb_access.byte_offset + pos;
                     cb_global_read_offsets.push_back(offset);
                  }
               }
    
               // Process output accesses
               for (const auto& out_access : analysis.output_writes) {
                  uint32_t offset = out_access.byte_offset + pos;
                  
                  OutputWriteEntry sv;
                  sv.index = out_access.register_index;
                  sv.index_offset = offset;
                  sv.instruction_length = len;
                  sv.instruction_offset = pos;
                  output_write_offsets.push_back(sv);
                  
                  if (out_access.register_index == sv_position_index)
                  {
                     last_sv_position_write_offset = pos + len * 4;
                  }
               }
            }
            
            if (pos + len * 4 >= shex_header->chunk_size + 8)
            {
               break;
            }
            
            prev_opcode_type = opcode_type;
            pos += len * 4;
         }
         
         // duplicate from first instruction to last sv_position write instruction
         // nop any output write and replace any cb0 read to cb5
         if (last_sv_position_write_offset - first_instruction_offset > 0)
         {
            uint32_t patch_length = (last_sv_position_write_offset - first_instruction_offset) / 4;
            std::vector<uint32_t> shader_patch(patch_length);
            memcpy(&shader_patch[0], shex + first_instruction_offset, patch_length * 4);
            
            for (auto& cb_read : cb_global_read_offsets)
            {
               if (cb_read < last_sv_position_write_offset)
               {
                  uint32_t index = (cb_read - first_instruction_offset) / 4;
                  shader_patch[index] = 5;
               }
            }

            uint32_t shader_output_inserted_bytes = 0;
            const uint32_t nop_opcode = ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(1) | D3D10_SB_OPCODE_NOP;
            for (auto& output_write : output_write_offsets)
            {
               if (output_write.index_offset < last_sv_position_write_offset)
               {
                  if (output_write.index == sv_position_index)
                  {
                     const uint32_t index = (output_write.index_offset - first_instruction_offset) / 4;
                     shader_patch[index] = original_output_count+2;
                                       
                     // duplicate sv_position output write in the original shader_code
                     {
                        std::vector<uint32_t> shader_output_copy(output_write.instruction_length);
                        memcpy(&shader_output_copy[0], shex + output_write.instruction_offset + shader_output_inserted_bytes, output_write.instruction_length * 4);
                        shader_output_copy[(output_write.index_offset - output_write.instruction_offset)/4] = original_output_count+1;
                        
                        shader_code.insert(
                           shader_code.begin() + dxbc_header->chunk_offsets[i] + output_write.instruction_offset + shader_output_inserted_bytes,
                           (std::byte*)&shader_output_copy[0],
                           (std::byte*)(&shader_output_copy[0] + shader_output_copy.size())
                        );
            
                        shex = &shader_code[dxbc_header->chunk_offsets[i]];
                        shex_header = (SHEXHeader*)shex;
                        shex_header->chunk_size += shader_output_copy.size() * sizeof(uint32_t);
                        shex_header->dword_count += shader_output_copy.size();
                        dxbc_header = (DXBCHeader*)&shader_code[0];
                        for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
                        {
                           dxbc_header->chunk_offsets[j] += shader_output_copy.size() * sizeof(uint32_t);
                        }
                     
                        shader_output_inserted_bytes += output_write.instruction_length * 4;
                     }
                  }
                  else
                  {
                     const uint32_t index = (output_write.instruction_offset - first_instruction_offset) / 4;
                     for (uint32_t j = 0; j < output_write.instruction_length; ++j)
                     {
                        shader_patch[index + j] = nop_opcode;
                     }
                  }
               }
            }
            // insert before ret
            shader_code.insert(
               shader_code.begin() + dxbc_header->chunk_offsets[i] + ret_insert_offset + shader_output_inserted_bytes,
               (std::byte*)&shader_patch[0],
               (std::byte*)(&shader_patch[0] + shader_patch.size())
            );
            
            shex = &shader_code[dxbc_header->chunk_offsets[i]];
            shex_header = (SHEXHeader*)shex;
            shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
            shex_header->dword_count += shader_patch.size();
            dxbc_header = (DXBCHeader*)&shader_code[0];
            for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
            {
               dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
            }
         }
      }
   }
   
   dxbc_header->file_size = shader_code.size();
   Hash::MD5::Digest md5_digest = CalcDXBCHash(shader_code.data(), shader_code.size());
   std::memcpy(&dxbc_header->hash, &md5_digest.data, DXBCHeader::hash_size);
}

void PatchPixelShader(std::vector<std::byte>& shader_code)
{
   DXBCHeader* dxbc_header = (DXBCHeader*)&shader_code[0];
   
   uint32_t input_count_from_signature = 0;

   for (uint32_t i = 0; i < dxbc_header->chunk_count; ++i)
   {
      if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "ISGN", 4) == 0)
      {
         std::byte* isgn = &shader_code[dxbc_header->chunk_offsets[i]];
         uint32_t isgn_size = *(uint32_t*)(isgn + 4);
         uint32_t isgn_entry_count = *(uint32_t*)(isgn + 8);
         DXBCSignatureEntry* isgn_entries = (DXBCSignatureEntry*)(isgn + 16);
         uint32_t texcoord_name_offset = 0;
         uint32_t texcoord_last_index = 0;
         uint32_t inserted_bytes = sizeof(DXBCSignatureEntry)*2;
         
         input_count_from_signature = isgn_entry_count;
         
         for (uint32_t j = 0; j < isgn_entry_count; ++j)
         {
            const char* name = (const char*)(isgn + 8 + isgn_entries[j].name_offset);
            if (strncmp(name, "TEXCOORD", 8) == 0)
            {
               texcoord_last_index++;
               if (texcoord_name_offset == 0)
               {
                  texcoord_name_offset = isgn_entries[j].name_offset;
               }
            }
            isgn_entries[j].name_offset += sizeof(DXBCSignatureEntry)*2;
         }
         auto Align4 = [](uint32_t v)
         {
            return (v + 3) & ~3;
         };
         
         if (texcoord_name_offset == 0)
         {
            uint32_t old_aligned_end = dxbc_header->chunk_offsets[i] + 8 + isgn_size;
            const char texcoord_name[] = "TEXCOORD";
            texcoord_name_offset = isgn_size;
            uint32_t new_end = old_aligned_end + sizeof(texcoord_name);
            uint32_t new_aligned_end = Align4(new_end);
            uint32_t string_insert_size = new_aligned_end - old_aligned_end;

            // Insert TEXCOORD + alignment padding
            shader_code.insert(
                shader_code.begin() + old_aligned_end,
                string_insert_size,
                std::byte{}
            );
            memcpy(
                shader_code.data() + old_aligned_end,
                texcoord_name,
                sizeof(texcoord_name)
            );

            inserted_bytes += string_insert_size;
            
            dxbc_header = (DXBCHeader*)&shader_code[0];
            isgn = &shader_code[dxbc_header->chunk_offsets[i]];
         }
         DXBCSignatureEntry current_pos_signature;
         current_pos_signature.name_offset = texcoord_name_offset+sizeof(DXBCSignatureEntry)*2;
         current_pos_signature.semantic_index = texcoord_last_index;
         current_pos_signature.value_type = 0;
         current_pos_signature.component_type = 3;
         current_pos_signature.reg = isgn_entry_count;
         current_pos_signature.component_mask = 15;
         current_pos_signature.read_write_mask = 15;
         
         DXBCSignatureEntry previous_pos_signature;
         previous_pos_signature.name_offset = texcoord_name_offset+sizeof(DXBCSignatureEntry)*2;
         previous_pos_signature.semantic_index = texcoord_last_index+1;
         previous_pos_signature.value_type = 0;
         previous_pos_signature.component_type = 3;
         previous_pos_signature.reg = isgn_entry_count+1;
         previous_pos_signature.component_mask = 15;
         previous_pos_signature.read_write_mask = 15;
         
         *(uint32_t*)(isgn + 4) += inserted_bytes;
         *(uint32_t*)(isgn + 8) += 2;
         shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + 16 + isgn_entry_count * sizeof(DXBCSignatureEntry),
            (std::byte*)&current_pos_signature,
            (std::byte*)&current_pos_signature + sizeof(DXBCSignatureEntry));
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + 16 + (isgn_entry_count+1) * sizeof(DXBCSignatureEntry),
            (std::byte*)&previous_pos_signature,
            (std::byte*)&previous_pos_signature + sizeof(DXBCSignatureEntry));
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
         {
            dxbc_header->chunk_offsets[j] += inserted_bytes;
         }
      }
      else if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "OSGN", 4) == 0)
      {
         std::byte* osgn = &shader_code[dxbc_header->chunk_offsets[i]];
         uint32_t osgn_size = *(uint32_t*)(osgn + 4);
         uint32_t osgn_entry_count = *(uint32_t*)(osgn + 8);
         DXBCSignatureEntry* osgn_entries = (DXBCSignatureEntry*)(osgn + 16);
         uint32_t sv_target_name_offset = 0;
         uint32_t sv_target_last_index = 0;
         uint32_t inserted_bytes = sizeof(DXBCSignatureEntry);
         for (uint32_t j = 0; j < osgn_entry_count; ++j)
         {
            const char* name = (const char*)(osgn + 8 + osgn_entries[j].name_offset);
            if (strncmp(name, "SV_Target", 9) == 0)
            {
               sv_target_last_index++;
               if (sv_target_name_offset == 0)
               {
                  sv_target_name_offset = osgn_entries[j].name_offset;
               }
            }
            osgn_entries[j].name_offset += sizeof(DXBCSignatureEntry);
         }
         auto Align4 = [](uint32_t v)
         {
            return (v + 3) & ~3;
         };
         
         if (sv_target_name_offset == 0)
         {
            uint32_t old_aligned_end = dxbc_header->chunk_offsets[i] + 8 + osgn_size;
            const char sv_target_name[] = "SV_Target";
            sv_target_name_offset = osgn_size;
            uint32_t new_end = old_aligned_end + sizeof(sv_target_name);
            uint32_t new_aligned_end = Align4(new_end);
            uint32_t string_insert_size = new_aligned_end - old_aligned_end;

            // Insert sv_target + alignment padding
            shader_code.insert(
                shader_code.begin() + old_aligned_end,
                string_insert_size,
                std::byte{}
            );
            memcpy(
                shader_code.data() + old_aligned_end,
                sv_target_name,
                sizeof(sv_target_name)
            );

            inserted_bytes += string_insert_size;
            
            dxbc_header = (DXBCHeader*)&shader_code[0];
            osgn = &shader_code[dxbc_header->chunk_offsets[i]];
         }
         DXBCSignatureEntry current_pos_signature;
         current_pos_signature.name_offset = sv_target_name_offset+sizeof(DXBCSignatureEntry);
         current_pos_signature.semantic_index = sv_target_last_index;
         current_pos_signature.value_type = 0;
         current_pos_signature.component_type = 3;
         current_pos_signature.reg = osgn_entry_count;
         current_pos_signature.component_mask = 3;
         current_pos_signature.read_write_mask = 12;
         
         *(uint32_t*)(osgn + 4) += inserted_bytes;
         *(uint32_t*)(osgn + 8) += 1;
         shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + 16 + osgn_entry_count * sizeof(DXBCSignatureEntry),
            (std::byte*)&current_pos_signature,
            (std::byte*)&current_pos_signature + sizeof(DXBCSignatureEntry));
         
         dxbc_header = (DXBCHeader*)&shader_code[0];
         for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
         {
            dxbc_header->chunk_offsets[j] += inserted_bytes;
         }
      }
      else if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "SHEX", 4) == 0)
      {
         std::byte* shex = &shader_code[dxbc_header->chunk_offsets[i]];
         SHEXHeader* shex_header = (SHEXHeader*)shex;
         
         uint32_t pos = 16;
         uint32_t original_output_count = 0;
         uint32_t original_input_count = 1;  // v0 being SV_Position
         uint32_t temp_register_count = 0;
         uint32_t temp_dcl_insert_offset = 0;
         // +8 from shex chunk header
         uint32_t ret_insert_offset = shex_header->dword_count * 4 + 8 - 4;
         
         bool has_inserted_inputs = false;
         
         D3D10_SB_OPCODE_TYPE prev_opcode_type = D3D10_SB_NUM_OPCODES;
         
         for (;;)
         {
            D3D10_SB_OPCODE_TYPE opcode_type = DECODE_D3D10_SB_OPCODE_TYPE(*(uint32_t*)(shex + pos));
            uint32_t len;
            if (opcode_type != D3D10_SB_OPCODE_CUSTOMDATA)
            {
               len = DECODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(*(uint32_t*)(shex + pos));
            }
            else
            {
               len = *(uint32_t*)(shex + pos + 4);
            }
            
            if (opcode_type == D3D10_SB_OPCODE_DCL_INPUT_PS || opcode_type == D3D10_SB_OPCODE_DCL_INPUT_PS_SIV)
            {
               original_input_count = *(uint32_t*)(shex + pos + 2 * 4);
            }
            if (opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT)
            {
               original_output_count = *(uint32_t*)(shex + pos + 2 * 4) + 1;
            }
            if (opcode_type == D3D10_SB_OPCODE_DCL_TEMPS)
            {
               temp_register_count = *(uint32_t*)(shex + pos + 1 * 4);
            }
            
            //if ((opcode_type != D3D10_SB_OPCODE_DCL_INPUT_PS && prev_opcode_type == D3D10_SB_OPCODE_DCL_INPUT_PS) ||
            //    (opcode_type != D3D10_SB_OPCODE_DCL_INPUT_PS && prev_opcode_type == D3D10_SB_OPCODE_DCL_INPUT_SIV))
            if ( (opcode_type != D3D10_SB_OPCODE_DCL_INPUT_PS && opcode_type != D3D10_SB_OPCODE_DCL_INPUT_PS_SIV) &&
                 (prev_opcode_type == D3D10_SB_OPCODE_DCL_INPUT_PS || prev_opcode_type == D3D10_SB_OPCODE_DCL_INPUT_PS_SIV) )
            {
               uint32_t opcode_token =
                  ENCODE_D3D10_SB_OPCODE_TYPE(D3D10_SB_OPCODE_DCL_INPUT_PS) |
                  ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(3) |
                  ENCODE_D3D10_SB_INSTRUCTION_SATURATE(false) |
                  ENCODE_D3D10_SB_INPUT_INTERPOLATION_MODE(D3D10_SB_INTERPOLATION_LINEAR);
               uint32_t operand_token =
                  ENCODE_D3D10_SB_OPERAND_NUM_COMPONENTS(D3D10_SB_OPERAND_4_COMPONENT) |
                  ENCODE_D3D10_SB_OPERAND_4_COMPONENT_SELECTION_MODE(D3D10_SB_OPERAND_4_COMPONENT_MASK_MODE) |
                  ENCODE_D3D10_SB_OPERAND_4_COMPONENT_MASK(0xF0) |
                  ENCODE_D3D10_SB_OPERAND_TYPE(D3D10_SB_OPERAND_TYPE_INPUT) |
                  ENCODE_D3D10_SB_OPERAND_INDEX_DIMENSION(D3D10_SB_OPERAND_INDEX_1D) |
                  ENCODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(0, D3D10_SB_OPERAND_INDEX_IMMEDIATE32);
               std::vector<uint32_t> shader_patch{
                  opcode_token,
                  operand_token, original_input_count+1,
                  opcode_token,
                  operand_token, original_input_count+2,
               };

               shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + pos, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
               shex = &shader_code[dxbc_header->chunk_offsets[i]];
               shex_header = (SHEXHeader*)shex;
               shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
               shex_header->dword_count += shader_patch.size();
               dxbc_header = (DXBCHeader*)&shader_code[0];
               for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
               {
                  dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
               }
               prev_opcode_type = D3D10_SB_NUM_OPCODES;
               pos += shader_patch.size() * sizeof(uint32_t);
               ret_insert_offset += shader_patch.size() * 4;
               
               has_inserted_inputs = true;
            }
            else if (opcode_type != D3D10_SB_OPCODE_DCL_OUTPUT && prev_opcode_type == D3D10_SB_OPCODE_DCL_OUTPUT)
            {
               if (!has_inserted_inputs)
               {
                  original_input_count = input_count_from_signature - 1;
                  uint32_t opcode_token =
                     ENCODE_D3D10_SB_OPCODE_TYPE(D3D10_SB_OPCODE_DCL_INPUT_PS) |
                     ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(3) |
                     ENCODE_D3D10_SB_INSTRUCTION_SATURATE(false) |
                     ENCODE_D3D10_SB_INPUT_INTERPOLATION_MODE(D3D10_SB_INTERPOLATION_LINEAR);
                  uint32_t operand_token =
                     ENCODE_D3D10_SB_OPERAND_NUM_COMPONENTS(D3D10_SB_OPERAND_4_COMPONENT) |
                     ENCODE_D3D10_SB_OPERAND_4_COMPONENT_SELECTION_MODE(D3D10_SB_OPERAND_4_COMPONENT_MASK_MODE) |
                     ENCODE_D3D10_SB_OPERAND_4_COMPONENT_MASK(0xF0) |
                     ENCODE_D3D10_SB_OPERAND_TYPE(D3D10_SB_OPERAND_TYPE_INPUT) |
                     ENCODE_D3D10_SB_OPERAND_INDEX_DIMENSION(D3D10_SB_OPERAND_INDEX_1D) |
                     ENCODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(0, D3D10_SB_OPERAND_INDEX_IMMEDIATE32);
                  std::vector<uint32_t> shader_patch{
                     opcode_token,
                     operand_token, original_input_count+1,
                     opcode_token,
                     operand_token, original_input_count+2,
                  };

                  shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + pos, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
                  shex = &shader_code[dxbc_header->chunk_offsets[i]];
                  shex_header = (SHEXHeader*)shex;
                  shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
                  shex_header->dword_count += shader_patch.size();
                  dxbc_header = (DXBCHeader*)&shader_code[0];
                  for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
                  {
                     dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
                  }
                  prev_opcode_type = D3D10_SB_NUM_OPCODES;
                  pos += shader_patch.size() * sizeof(uint32_t);
                  ret_insert_offset += shader_patch.size() * 4;
                  
                  has_inserted_inputs = true;
               }
               
               {
                  uint32_t opcode_token =
                     ENCODE_D3D10_SB_OPCODE_TYPE(D3D10_SB_OPCODE_DCL_OUTPUT) |
                     ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(3) |
                     ENCODE_D3D10_SB_INSTRUCTION_SATURATE(false);
                  uint32_t operand_token =
                     ENCODE_D3D10_SB_OPERAND_NUM_COMPONENTS(D3D10_SB_OPERAND_4_COMPONENT) |
                     ENCODE_D3D10_SB_OPERAND_4_COMPONENT_SELECTION_MODE(D3D10_SB_OPERAND_4_COMPONENT_MASK_MODE) |
                     ENCODE_D3D10_SB_OPERAND_4_COMPONENT_MASK(0x30) |
                     ENCODE_D3D10_SB_OPERAND_TYPE(D3D10_SB_OPERAND_TYPE_OUTPUT) |
                     ENCODE_D3D10_SB_OPERAND_INDEX_DIMENSION(D3D10_SB_OPERAND_INDEX_1D) |
                     ENCODE_D3D10_SB_OPERAND_INDEX_REPRESENTATION(0, D3D10_SB_OPERAND_INDEX_IMMEDIATE32);
                  std::vector<uint32_t> shader_patch{
                     opcode_token,
                     operand_token, original_output_count,
                  };

                  shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + pos, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
                  shex = &shader_code[dxbc_header->chunk_offsets[i]];
                  shex_header = (SHEXHeader*)shex;
                  shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
                  shex_header->dword_count += shader_patch.size();
                  dxbc_header = (DXBCHeader*)&shader_code[0];
                  for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
                  {
                     dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
                  }
                  prev_opcode_type = D3D10_SB_NUM_OPCODES;
                  pos += shader_patch.size() * sizeof(uint32_t);
                  ret_insert_offset += shader_patch.size() * 4;
                  
                  temp_dcl_insert_offset = pos;
               }
            }
            
            if (pos + len * 4 >= shex_header->chunk_size + 8)
            {
               break;
            }
            
            prev_opcode_type = opcode_type;
            pos += len * 4;
         }
         
         if (original_output_count != 0)
         {
            if (temp_register_count == 0)
            {
               uint32_t opcode_token =
                  ENCODE_D3D10_SB_OPCODE_TYPE(D3D10_SB_OPCODE_DCL_TEMPS) |
                  ENCODE_D3D10_SB_TOKENIZED_INSTRUCTION_LENGTH(2) |
                  ENCODE_D3D10_SB_INSTRUCTION_SATURATE(false);
               std::vector<uint32_t> shader_patch{
                  opcode_token,
                  1,
               };

               shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + temp_dcl_insert_offset, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
               shex = &shader_code[dxbc_header->chunk_offsets[i]];
               shex_header = (SHEXHeader*)shex;
               shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
               shex_header->dword_count += shader_patch.size();
               dxbc_header = (DXBCHeader*)&shader_code[0];
               for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
               {
                  dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
               }
               
               ret_insert_offset += shader_patch.size() * 4;
            }
            
            {
               std::vector<uint32_t> shader_patch{
                  0x0700000E, 0x00100032, 0x00000000, 0x00101046, original_input_count+1, 0x00101FF6, original_input_count+1, //div r0.xy, v2.xyxx, v2.wwww
                  0x0700000E, 0x001000C2, 0x00000000, 0x00101406, original_input_count+2, 0x00101FF6, original_input_count+2, //div r0.zw, v3.xxxy, v3.wwww
                  0x08000000, 0x00100032, 0x00000000, 0x80100AE6, 0x00000041, 0x00000000, 0x00100046, 0x00000000, //add r0.xy, -r0.zwzz, r0.xyxx
                  0x0A000038, 0x00102032, original_output_count, 0x00100046, 0x00000000, 0x00004002, 0x3F000000, 0xBF000000, 0x00000000, 0x00000000, //mul o1.xy, r0.xyxx, l(0.500000, -0.500000, 0.000000, 0.000000)
               };
               
               shader_code.insert(shader_code.begin() + dxbc_header->chunk_offsets[i] + ret_insert_offset, (std::byte*)&shader_patch[0], (std::byte*)(&shader_patch[0] + shader_patch.size()));
               shex = &shader_code[dxbc_header->chunk_offsets[i]];
               shex_header = (SHEXHeader*)shex;
               shex_header->chunk_size += shader_patch.size() * sizeof(uint32_t);
               shex_header->dword_count += shader_patch.size();
               dxbc_header = (DXBCHeader*)&shader_code[0];
               for (uint32_t j = i + 1; j < dxbc_header->chunk_count; ++j)
               {
                  dxbc_header->chunk_offsets[j] += shader_patch.size() * sizeof(uint32_t);
               }
            }
         }
            
      }
   }
   
   dxbc_header->file_size = shader_code.size();
   Hash::MD5::Digest md5_digest = CalcDXBCHash(shader_code.data(), shader_code.size());
   std::memcpy(&dxbc_header->hash, &md5_digest.data, DXBCHeader::hash_size);
}

void PatchComputeShader(std::vector<std::byte>& shader_code)
{
}

uint16_t GetShaderProgramType(std::vector<std::byte>& shader_code)
{
   DXBCHeader* dxbc_header = (DXBCHeader*)&shader_code[0];

   for (uint32_t i = 0; i < dxbc_header->chunk_count; ++i)
   {
      if (strncmp((const char*)&shader_code[dxbc_header->chunk_offsets[i]], "SHEX", 4) == 0)
      {
         std::byte* shex = &shader_code[dxbc_header->chunk_offsets[i]];
         uint16_t type = *(uint16_t*)(shex + 10);
         return type;
      }
   }
   return 0xFFF0;
}