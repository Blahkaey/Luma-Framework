#pragma once
#include <unordered_map>

inline std::unordered_map<uint32_t, uint16_t> g_local_to_world_offset = {
   {0x0356F78E, 16 * 16},	// A_Shader_to_draw_outline_model.
   {0x04A1EA4C, 5 * 16},	// A_Shader_to_draw_outline_model.
   {0x293B2E0B, 19 * 16},	// A_Shader_to_draw_outline_model.
   {0x4440DE88, 14 * 16},	// A_Shader_to_draw_outline_model.
   {0x4C466497, 14 * 16},	// A_Shader_to_draw_outline_model.
   {0x611E488A, 17 * 16},	// A_Shader_to_draw_outline_model.
   {0x645829EA, 16 * 16},	// A_Shader_to_draw_outline_model.
   {0x78210FD8, 17 * 16},	// A_Shader_to_draw_outline_model.
   {0x82C24BE3, 8 * 16},	// A_Shader_to_draw_outline_model.
   {0x8495D5F6, 7 * 16},	// A_Shader_to_draw_outline_model.
   {0x8E38B29A, 16 * 16},	// A_Shader_to_draw_outline_model.
   {0x8E851138, 4 * 16},	// A_Shader_to_draw_outline_model.
   {0x92DBF940, 5 * 16},	// A_Shader_to_draw_outline_model.
   {0xB34C8293, 14 * 16},	// A_Shader_to_draw_outline_model.
   {0xD2ECB593, 14 * 16},	// A_Shader_to_draw_outline_model.
   {0xD909A60A, 19 * 16},	// A_Shader_to_draw_outline_model.
   {0xEB7A0C61, 4 * 16},	// A_Shader_to_draw_outline_model.
   {0xEDB78642, 16 * 16},	// A_Shader_to_draw_outline_model.
   {0x70F00C4A, 7 * 16},	// Calm_Water_Shader
   {0xEDDCA1AE, 10 * 16},	// Calm_Water_Shader
   {0xEA1841C3, 10 * 16},	// Calm_Water_Shader_2
   {0xFA582144, 7 * 16},	// Calm_Water_Shader_2
   {0xA81299B1, 5 * 16},	// Cloud_Particle_Shader
   {0x04B1C137, 4 * 16},	// e3d_scroll
   {0x1C631C71, 4 * 16},	// e3d_scroll
   {0x398DD324, 4 * 16},	// e3d_scroll
   {0x52418053, 4 * 16},	// e3d_scroll
   {0xF385A5BE, 4 * 16},	// e3d_scroll
   {0x668F8B18, 8 * 16},	// Grass_Shader
   {0x238BCC5A, 5 * 16},	// Grass_ShadowMap_Shader
   {0x474383BF, 4 * 16},	// Grass_ShadowMap_Shader
   {0x5B824617, 4 * 16},	// Grass_ShadowMap_Shader
   {0x70BB6E14, 4 * 16},	// Grass_ShadowMap_Shader
   {0xDE757C14, 4 * 16},	// Grass_ShadowMap_Shader
   {0xE25E5B55, 5 * 16},	// Grass_ShadowMap_Shader
   {0x23EB397E, 8 * 16},	// Offscreen_Glitch_Shader
   {0x12B3E01C, 4 * 16},	// PBKTF-GbL2wRtt2
   {0x237AC43E, 4 * 16},	// PBKTF-GbL2wRtt2
   {0x46BA3379, 4 * 16},	// PBKTF-GbL2wRtt2
   {0x73517008, 4 * 16},	// PBKTF-GbL2wRtt2
   {0x8AB6B6A1, 4 * 16},	// PBKTF-GbL2wRtt2
   {0xACABAB36, 4 * 16},	// PBKTF-GbL2wRtt2
   {0xB527EC97, 4 * 16},	// PBKTF-GbL2wRtt2
   {0xCDBAC663, 4 * 16},	// PBKTF-GbL2wRtt2
   {0xF57609A6, 4 * 16},	// PBKTF-GbL2wRtt2
   {0x254B32AB, 7 * 16},	// Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
   {0x7232FFB9, 14 * 16},	// Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
   {0x749149DC, 14 * 16},	// Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
   {0xF02A37E5, 7 * 16},	// Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
   {0x06F4EC5C, 11 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x1540FFFE, 14 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x2D6AA3A4, 4 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x502FD233, 7 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x605F5CA1, 4 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x666D52AF, 7 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x6AFAF3E3, 4 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x71544EF8, 11 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0xD1FADED5, 7 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0xE0819B17, 14 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0xE2E374EB, 14 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0xF157920A, 14 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0xF7E638B3, 7 * 16},	// Physically-Based_Standard_Tree_Branch_Shader
   {0x010F34CF, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x04187F5A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x043C2F23, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x045F38B8, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x046F96A7, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x05348533, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x058D0BC7, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x06A470E0, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x06D13970, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0772F590, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x07CAEEC4, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x08AA4669, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x08D5F9D7, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0951450F, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0992E0C5, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x09BBD8AD, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x09D8466E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0A308B77, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0A5D9762, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0A760BA6, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0C56C93E, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0CEA0817, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0ECBDF79, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0FA0E581, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0FC98679, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0FEE645B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0FEE74F2, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x0FF19F20, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x10F55BF3, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1113491C, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1203AC9F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x12075375, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x12649DC5, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x12D53B44, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x130A07DD, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x131CBAA1, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x132DE147, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x13C1ABAA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x15137C6F, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x15B712EE, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1612D129, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1680E2C9, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x173282FE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1794FF8F, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x18A59EE7, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x19016D6C, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x19709E29, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1A428594, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1A4F6E69, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1B86412F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1C1B0ACB, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1C4AD91D, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1C9EC128, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1D844421, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1E87DFFD, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x1F22D15B, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x200C9AD4, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x203266D7, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x20D5D741, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2158E72E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x218A506B, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x21CD6D47, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x23017892, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x24677A9B, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x254E0303, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x25A8A16D, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x26EB8C02, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x272A9D11, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x298D7188, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2B899114, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2BC0E4B5, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2CDD74FE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2EA8C591, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2F78EC1E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2F80F598, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x2F8FE069, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x310F464C, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x319296C8, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3214319D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x322A335B, 14 * 16},	// Physically_Based_Standard_Both_Shader
   {0x32E4BB1A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x343D5E12, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x36143A1D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x38DAA23F, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x394D4CDE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3B300010, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3B404DD1, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3BE93107, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3C071463, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3C719B18, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3D609E5D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3DD7EBB1, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3E59C011, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3E82721A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3E949842, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3F016156, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3F8D6A66, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3FBB5126, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x3FEC1BFA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x40D7991E, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x41E44886, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x430A8D59, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x44E4A66F, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x46E476BD, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x47E214D4, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4843381E, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x48624F1E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x48743E85, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4A4F0607, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4C4BEB5F, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4CDD0A92, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4D686CF9, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x4ED959F8, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x509DEB46, 6 * 16},	// Physically_Based_Standard_Both_Shader
   {0x51D11DE0, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x53A1F4AA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x55A2D5FE, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x573CEE7D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x57680896, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x57725D24, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x57857AD2, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5786D973, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x57F4D135, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x590191F8, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x598C2F47, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5A10ECD3, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5AB22C71, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5B48E663, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5BAEA1A5, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5BC7DE13, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5BF7B53B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5C9FF5E6, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5CE31F63, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5CE6B8D5, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5DA649B7, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x5EAD3F8F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x60433B8C, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x609B79A3, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x60ECD382, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x610A24E6, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x61BC7DAC, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x61E3D2FE, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x62213C22, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x634B606C, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x635E8B59, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x636F71BD, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x68B78F7A, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x690AB5D7, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x69140051, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6C658942, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6C70F00D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6D0D9438, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6D184A7E, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6D2FFCD6, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x6DF34034, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x716EB73A, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x72D0AD0F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x7397CA8B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x747E1CA9, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x74C54B11, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x76629643, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x77292CFA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x778A910D, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x782354FE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x79E26415, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x79F69077, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x7B7103CF, 6 * 16},	// Physically_Based_Standard_Both_Shader
   {0x7E22CECC, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x7F328100, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x80A4AF6B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x812E4B53, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x81AA32B5, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x822D71C0, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x82FA67AB, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x83ADE925, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x83EF1126, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8451C64F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8516E767, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x85DE0AED, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x863B36C3, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x86C2ADFE, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x883D5101, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x886456C5, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x88FD0794, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x896F6AE8, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x89C81C51, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8AB2C54E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8B6FBC2D, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8BC43BBF, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8C45EF74, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8CD6C035, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8D63F9AE, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0x8FA8BCE5, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x90BE3AA2, 9 * 16},	// Physically_Based_Standard_Both_Shader
   {0x919A05CA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x924C6051, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x93BD9931, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x93F63F7A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x94EB98FD, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x95625FBD, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x958765AE, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x985B19CA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9A2FD35B, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9AA48399, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9B315C6E, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9B389161, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9B466828, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9B6D98BD, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9B929F29, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9BAFF123, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9BF62C76, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9CBFB107, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9CDD6F2D, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9E5AC71B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9EC065AE, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9F384924, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0x9FF79B84, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA0B29C32, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA1C53534, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA1E48BC6, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA311DE48, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA31DCA39, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA45072BD, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA513919A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA58488E2, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA5EE5A8F, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA72BF812, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA7F7B83D, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA89ABE68, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xA9B08BAE, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAA78773A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAA7F11F0, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAAEAEFCB, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAD4A5127, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xADD53C42, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAE377F33, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAE8CEC3D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xAEC60C4C, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB1354D71, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB16C058A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB2C579FA, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB672D51D, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB6AFFC2F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB6D2BE06, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB77A1B5D, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB84D6C74, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB8AE4747, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xB9F6E206, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBB575237, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBBA81CD7, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBCC8000A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBD3A7FDA, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBF37889C, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xBFFAE4DA, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC0F0B147, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC207F742, 7 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC3EB32BE, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC4097456, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC4C0A0B5, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC51AD711, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC5909EA7, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC64E65F8, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC6B51E16, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC71577E0, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC7C6E4FC, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC88DF8A2, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC8DDB3D6, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC9C9E31C, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xC9FCF617, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCA4F9D3A, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCAA332EE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCB52337B, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCB93470F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCBA4A49A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCBA9EB86, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCBF985DC, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCD16E4CA, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCD8B25DB, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCD99F333, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCF2062FC, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xCF8A7A5D, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD07E9815, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD1A75E70, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD23A05C9, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD3565A52, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD3C491B9, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD58C95B8, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD6B28C5B, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD76BF7C7, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD7DBC6C7, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD7F1A482, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD8737B56, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xD9F1136D, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDA02C0E2, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDA6ABA42, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDAE6C516, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDBE8853B, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDC951FDE, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDCB930B2, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDE9A1A37, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDF4DD2D6, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDF5BAC56, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xDFD6A64A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE0B6F506, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE146094B, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE2E809F8, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE3166DE9, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE33B7E2E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE3E52D3F, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE47FDB43, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE6088AE6, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE71371CB, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE72E8E30, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE8125174, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE8384FC4, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xE9662D50, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEA5A3CD1, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEAD54366, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEB78334B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEB9C77DC, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEBD38238, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEBF3C70F, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xECFDFE24, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xED551978, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xED7BD18A, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xED8678EF, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEDBDF144, 11 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEDD9E255, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEE8984D9, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xEF9AD76A, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF0C80079, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF0EEFB00, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF18168A3, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF2399900, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF3750CA8, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF38AA098, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF38AD66D, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF59C98FE, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF60FD467, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF67B7F8B, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF87792F2, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF8AC509C, 8 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF9B3C845, 4 * 16},	// Physically_Based_Standard_Both_Shader
   {0xF9B9BEE2, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFBC0BFA5, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFC0CB704, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFCE4C8DB, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFCEEFC28, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFDF5C69E, 12 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFE2F2549, 15 * 16},	// Physically_Based_Standard_Both_Shader
   {0xFF672EA2, 5 * 16},	// Physically_Based_Standard_Both_Shader
   {0x091F0E7B, 4 * 16},	// Physically_Based_Standard_Shader
   {0x0C4608F3, 8 * 16},	// Physically_Based_Standard_Shader
   {0x1048BD17, 4 * 16},	// Physically_Based_Standard_Shader
   {0x186218A6, 12 * 16},	// Physically_Based_Standard_Shader
   {0x196A10D5, 5 * 16},	// Physically_Based_Standard_Shader
   {0x1F7B1860, 4 * 16},	// Physically_Based_Standard_Shader
   {0x29058484, 4 * 16},	// Physically_Based_Standard_Shader
   {0x33F07D79, 12 * 16},	// Physically_Based_Standard_Shader
   {0x39E5525A, 5 * 16},	// Physically_Based_Standard_Shader
   {0x4F3AA0BA, 12 * 16},	// Physically_Based_Standard_Shader
   {0x785D5A94, 5 * 16},	// Physically_Based_Standard_Shader
   {0x7871F71F, 15 * 16},	// Physically_Based_Standard_Shader
   {0x8F682F27, 4 * 16},	// Physically_Based_Standard_Shader
   {0xAA32484C, 4 * 16},	// Physically_Based_Standard_Shader
   {0xBE91AD09, 5 * 16},	// Physically_Based_Standard_Shader
   {0xBFC86E30, 4 * 16},	// Physically_Based_Standard_Shader
   {0xC0FCD713, 4 * 16},	// Physically_Based_Standard_Shader
   {0xC3ACC4F7, 15 * 16},	// Physically_Based_Standard_Shader
   {0xC413E857, 12 * 16},	// Physically_Based_Standard_Shader
   {0xC4ACB720, 4 * 16},	// Physically_Based_Standard_Shader
   {0xE661B585, 4 * 16},	// Physically_Based_Standard_Shader
   {0xEE5E7066, 4 * 16},	// Physically_Based_Standard_Shader
   {0xEFAB627D, 4 * 16},	// Physically_Based_Standard_Shader
   {0xFBA553E2, 12 * 16},	// Physically_Based_Standard_Shader
   {0xFDC71808, 15 * 16},	// Physically_Based_Standard_Shader
   {0x06C81328, 4 * 16},	// Shadow_Map_Shader
   {0x0EEFF4C1, 5 * 16},	// Shadow_Map_Shader
   {0x1905A21D, 4 * 16},	// Shadow_Map_Shader
   {0x199044BA, 4 * 16},	// Shadow_Map_Shader
   {0x1A6B8DEC, 5 * 16},	// Shadow_Map_Shader
   {0x1F9922CF, 4 * 16},	// Shadow_Map_Shader
   {0x21FEC165, 4 * 16},	// Shadow_Map_Shader
   {0x25FFF2EB, 4 * 16},	// Shadow_Map_Shader
   {0x34C5F2BE, 4 * 16},	// Shadow_Map_Shader
   {0x382270B9, 4 * 16},	// Shadow_Map_Shader
   {0x50C061E5, 4 * 16},	// Shadow_Map_Shader
   {0x5BD96E5A, 4 * 16},	// Shadow_Map_Shader
   {0x687086B0, 5 * 16},	// Shadow_Map_Shader
   {0x69A4B9B7, 4 * 16},	// Shadow_Map_Shader
   {0x6C1BD948, 4 * 16},	// Shadow_Map_Shader
   {0x7E8DE1F0, 4 * 16},	// Shadow_Map_Shader
   {0x813B6FC2, 4 * 16},	// Shadow_Map_Shader
   {0x8148DD0C, 4 * 16},	// Shadow_Map_Shader
   {0x8738331E, 5 * 16},	// Shadow_Map_Shader
   {0x936F42ED, 4 * 16},	// Shadow_Map_Shader
   {0x9B7A6FF1, 4 * 16},	// Shadow_Map_Shader
   {0xA0F8B9A6, 4 * 16},	// Shadow_Map_Shader
   {0xB09163D8, 4 * 16},	// Shadow_Map_Shader
   {0xB894F049, 4 * 16},	// Shadow_Map_Shader
   {0xDB078281, 5 * 16},	// Shadow_Map_Shader
   {0xE1471752, 5 * 16},	// Shadow_Map_Shader
   {0xE5233626, 4 * 16},	// Shadow_Map_Shader
   {0xE7ECA6A0, 4 * 16},	// Shadow_Map_Shader
   {0xEFBE5DD6, 4 * 16},	// Shadow_Map_Shader
   {0xF3A74B7B, 4 * 16},	// Shadow_Map_Shader
   {0xFCABA574, 4 * 16},	// Shadow_Map_Shader
   {0xDD2C4C7C, 9 * 16},	// Standard_Shader
   {0x2B77F22D, 15 * 16},	// Stream_Water_Shader
   {0x033AA3C7, 8 * 16},	// Tree2_ShadowMap_Shader
   {0x2298CA17, 8 * 16},	// Tree2_ShadowMap_Shader
   {0x931FF8A3, 7 * 16},	// Tree2_ShadowMap_Shader
   {0xEAC80764, 7 * 16},	// Tree2_ShadowMap_Shader
   {0x1F24F663, 4 * 16},	// TwinkleEyeTranslucence_Shader
   {0x1FF525BD, 14 * 16},	// TwinkleEyeTranslucence_Shader
   {0x98E64C00, 11 * 16},	// TwinkleEyeTranslucence_Shader
   {0xA46DBCA8, 4 * 16},	// TwinkleEyeTranslucence_Shader
   {0xB57D3A34, 11 * 16},	// TwinkleEyeTranslucence_Shader
   {0xCB72CD80, 7 * 16},	// TwinkleEyeTranslucence_Shader
   {0x7E4C1A2B, 4 * 16},	// Voxelize_Shader
   {0xAD4E28F9, 4 * 16},	// Voxelize_Shader
};

inline std::unordered_map<uint32_t, uint16_t> g_at_color_offset = {
	{0x37F635A2, 0 * 16}, //e3d_scroll
	{0x038CC484, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x1134BB50, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x14785515, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x15B5D1E8, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x19DBB466, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x1A17665E, 5 * 16}, //PBKTF-GbL2wRtt2
	{0x349C3F34, 5 * 16}, //PBKTF-GbL2wRtt2
	{0x3B5FEC10, 5 * 16}, //PBKTF-GbL2wRtt2
	{0x40B28571, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x44E1A687, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x45B12C6C, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x49F910F4, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x4C17517C, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x4D407127, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x671B762C, 5 * 16}, //PBKTF-GbL2wRtt2
	{0x7BA222DF, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x7C7CD49F, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x7EAC39E6, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x81D6F2B8, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x832BEBBA, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x8663DEE7, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x891F3C50, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x8C7AB68B, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x9848CE7A, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x99456151, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xA0C9A336, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xA2B6102A, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xC33ABF26, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xC70C5D37, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xE14A5980, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xE5BDC179, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xE935A929, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xF1D9C307, 6 * 16}, //PBKTF-GbL2wRtt2
	{0xF7C6C2A0, 6 * 16}, //PBKTF-GbL2wRtt2
	{0x1A4EE633, 6 * 16}, //Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
	{0x392C43B2, 7 * 16}, //Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
	{0x3F189B5D, 6 * 16}, //Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
	{0x673D1CB1, 77 * 16}, //Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
	{0xD329C1AA, 7 * 16}, //Physically-Based_Mixed_Metal_Non-Metal_Tree2_Shader
	{0x03BB3534, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x05A7B2CD, 6 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x0E28F4CB, 70 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x182AD830, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x1F4A002D, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x2E2FB9EE, 71 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x472D9BA4, 71 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x854E4429, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x97C553BD, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0xA2A8A194, 7 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0xE040857E, 70 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0xF6E9CE54, 6 * 16}, //Physically-Based_Standard_Tree_Branch_Shader
	{0x0049CB11, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x027EC64A, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x03312596, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0x03C90B38, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x055CE32E, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x05EA3C07, 83 * 16}, //Physically_Based_Standard_Both_Shader
	{0x06621AD9, 93 * 16}, //Physically_Based_Standard_Both_Shader
	{0x06BC2AC8, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x08CD7E15, 130 * 16}, //Physically_Based_Standard_Both_Shader
	{0x09128781, 158 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0B1623FC, 87 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0B44D782, 84 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0BC4955D, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0C504914, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0CDD8AD6, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0DA9384D, 146 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0E62BE43, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0F9DF8EB, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0FEC3963, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x0FF234C1, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x11FF2012, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1257B357, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0x12608E85, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x146AEA7A, 105 * 16}, //Physically_Based_Standard_Both_Shader
	{0x15AB6DB2, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x15D16B08, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x16163BD4, 147 * 16}, //Physically_Based_Standard_Both_Shader
	{0x18AB3312, 95 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1919B30C, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1A056EF2, 95 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1A25D3EA, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1A9B5282, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1B544B6C, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1B5B8804, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1D591BC3, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1F3F2C0D, 91 * 16}, //Physically_Based_Standard_Both_Shader
	{0x1FFD725F, 92 * 16}, //Physically_Based_Standard_Both_Shader
	{0x210FF9CC, 105 * 16}, //Physically_Based_Standard_Both_Shader
	{0x256D11F3, 88 * 16}, //Physically_Based_Standard_Both_Shader
	{0x26361545, 153 * 16}, //Physically_Based_Standard_Both_Shader
	{0x29315B88, 177 * 16}, //Physically_Based_Standard_Both_Shader
	{0x29A747D9, 109 * 16}, //Physically_Based_Standard_Both_Shader
	{0x29D1AF59, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0x2BD26D40, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x2C74D47B, 11 * 16}, //Physically_Based_Standard_Both_Shader
	{0x2E57AE85, 99 * 16}, //Physically_Based_Standard_Both_Shader
	{0x30849054, 88 * 16}, //Physically_Based_Standard_Both_Shader
	{0x31E211B6, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3326AFE8, 92 * 16}, //Physically_Based_Standard_Both_Shader
	{0x33E85CB5, 93 * 16}, //Physically_Based_Standard_Both_Shader
	{0x35694C18, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3586E62D, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0x35B77A92, 79 * 16}, //Physically_Based_Standard_Both_Shader
	{0x35D76CBA, 94 * 16}, //Physically_Based_Standard_Both_Shader
	{0x365DBEBF, 25 * 16}, //Physically_Based_Standard_Both_Shader
	{0x36F1741A, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3869FBD7, 91 * 16}, //Physically_Based_Standard_Both_Shader
	{0x386C82C5, 12 * 16}, //Physically_Based_Standard_Both_Shader
	{0x395B8B4C, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0x396474CE, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0x396DD3BC, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3BBEA0DE, 99 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3BC4CCFA, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3BFAE8F7, 154 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3C5DB389, 87 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3D118AAD, 146 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3EC9CA3E, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x3EE4F252, 10 * 16}, //Physically_Based_Standard_Both_Shader
	{0x408F3CE0, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x4203686F, 10 * 16}, //Physically_Based_Standard_Both_Shader
	{0x4285EE78, 109 * 16}, //Physically_Based_Standard_Both_Shader
	{0x429B97CC, 176 * 16}, //Physically_Based_Standard_Both_Shader
	{0x42FB8B11, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0x439740D9, 69 * 16}, //Physically_Based_Standard_Both_Shader
	{0x440ABC6D, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x44606886, 126 * 16}, //Physically_Based_Standard_Both_Shader
	{0x455C2E0B, 93 * 16}, //Physically_Based_Standard_Both_Shader
	{0x45B57BBC, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x4BBC8327, 94 * 16}, //Physically_Based_Standard_Both_Shader
	{0x4C7DCD42, 176 * 16}, //Physically_Based_Standard_Both_Shader
	{0x4DB3EABB, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x52561613, 12 * 16}, //Physically_Based_Standard_Both_Shader
	{0x53D12512, 146 * 16}, //Physically_Based_Standard_Both_Shader
	{0x540F99B8, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x555CF85A, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x556331C1, 69 * 16}, //Physically_Based_Standard_Both_Shader
	{0x55FD1783, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x567F6526, 68 * 16}, //Physically_Based_Standard_Both_Shader
	{0x56C2C63F, 129 * 16}, //Physically_Based_Standard_Both_Shader
	{0x56F70C0C, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x58F9A430, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5AE729DE, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5CB14A1C, 69 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5CC47D9E, 132 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5D8E6CAF, 68 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5E777D8F, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5EF14863, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x5EFDEDA5, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x610085F9, 80 * 16}, //Physically_Based_Standard_Both_Shader
	{0x6257D3A3, 60 * 16}, //Physically_Based_Standard_Both_Shader
	{0x62B32AFC, 69 * 16}, //Physically_Based_Standard_Both_Shader
	{0x638B5827, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x63BAF75B, 11 * 16}, //Physically_Based_Standard_Both_Shader
	{0x63F480E7, 126 * 16}, //Physically_Based_Standard_Both_Shader
	{0x648323D6, 101 * 16}, //Physically_Based_Standard_Both_Shader
	{0x6625D38E, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x666A8189, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0x67A01779, 83 * 16}, //Physically_Based_Standard_Both_Shader
	{0x6992126D, 145 * 16}, //Physically_Based_Standard_Both_Shader
	{0x6EA451CE, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x6F418C35, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0x708B2A1E, 93 * 16}, //Physically_Based_Standard_Both_Shader
	{0x71216ECF, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x7989C557, 68 * 16}, //Physically_Based_Standard_Both_Shader
	{0x79ED59C5, 60 * 16}, //Physically_Based_Standard_Both_Shader
	{0x7BCA36AD, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x7F5A5E44, 109 * 16}, //Physically_Based_Standard_Both_Shader
	{0x7FEDB1CF, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x801CA4B5, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0x81D6F538, 11 * 16}, //Physically_Based_Standard_Both_Shader
	{0x822C2B53, 84 * 16}, //Physically_Based_Standard_Both_Shader
	{0x82680082, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x83F6C1F4, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x840DD118, 67 * 16}, //Physically_Based_Standard_Both_Shader
	{0x841606FB, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x843888BD, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x844C17BC, 22 * 16}, //Physically_Based_Standard_Both_Shader
	{0x84FF1E64, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8623E831, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x86573AE4, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x87162F30, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x87343783, 92 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8793C894, 146 * 16}, //Physically_Based_Standard_Both_Shader
	{0x88524889, 108 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8A1C1412, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8A566191, 67 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8AC982A1, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8C0B8BC0, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8D3DD909, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8D557B40, 85 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8DB27FE4, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8E672313, 25 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8EE6FF37, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8F057C4F, 125 * 16}, //Physically_Based_Standard_Both_Shader
	{0x8F377EC3, 130 * 16}, //Physically_Based_Standard_Both_Shader
	{0x905933FB, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x90D13CF7, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0x90D4031E, 131 * 16}, //Physically_Based_Standard_Both_Shader
	{0x91334E8C, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0x91F3CA5A, 84 * 16}, //Physically_Based_Standard_Both_Shader
	{0x9495D16B, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x95179560, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0x969BF403, 25 * 16}, //Physically_Based_Standard_Both_Shader
	{0x97A22A93, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0x99ADFF9F, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0x9CB2C1C9, 12 * 16}, //Physically_Based_Standard_Both_Shader
	{0x9F356270, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0x9F70E00A, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA0110FB8, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA1F4D121, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA246E57B, 25 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA24C9EF2, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA355513B, 94 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA3C2459F, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA47CC9A6, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA583B381, 67 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA6E7D993, 89 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA89F9395, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA8FE67FC, 109 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA967D69B, 125 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA98CB32D, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0xA9C66D43, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAA5F1604, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAA95F561, 22 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAAB9EE29, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAC690F6F, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0xACC0AEB2, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAD8835C6, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAE74DEF8, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xAF64D1D8, 68 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB12303DC, 10 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB559B362, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB5797CF9, 89 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB6B234D9, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB823C122, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB8766CBA, 11 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB9100C0D, 90 * 16}, //Physically_Based_Standard_Both_Shader
	{0xB9FE05BC, 99 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBA297925, 84 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBAB37F96, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBBA6859F, 145 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBE37E6F3, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBF5BCBDF, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBFB571F5, 19 * 16}, //Physically_Based_Standard_Both_Shader
	{0xBFF5D79B, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC0DA8743, 10 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC1384C15, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC14D69B4, 153 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC1D50E72, 158 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC453B1BB, 85 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC50C0233, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC586F940, 79 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC66008C5, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC66C815F, 102 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC6ACE153, 102 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC8F06F5A, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC96229FD, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xC9B5536F, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xCD4684E6, 12 * 16}, //Physically_Based_Standard_Both_Shader
	{0xCE6EE696, 83 * 16}, //Physically_Based_Standard_Both_Shader
	{0xCF18AB7A, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xCFA893C5, 92 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD201DDC5, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD239AC05, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD4D03DDC, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD4D096C7, 104 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD78C079C, 99 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD84F21B1, 131 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD9215A80, 85 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD9AC569C, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xD9B57AA5, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0xDADE4B8B, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0xDC4100A8, 89 * 16}, //Physically_Based_Standard_Both_Shader
	{0xDD182C8C, 21 * 16}, //Physically_Based_Standard_Both_Shader
	{0xDD4A1A73, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xDF096096, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE071A7B5, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE0A1265A, 98 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE0D1FF32, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE0E6DD54, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE191EC91, 87 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE1F2EE45, 129 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE2152D17, 114 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE2772ED7, 154 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE2A91D7E, 177 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE2EB4585, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE7620BC8, 101 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE76B0D0D, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE7C6CA76, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE8C531BC, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xE9945C61, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xEC0648BF, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xEE01794A, 86 * 16}, //Physically_Based_Standard_Both_Shader
	{0xEE9C605E, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0xEF8CBCEC, 97 * 16}, //Physically_Based_Standard_Both_Shader
	{0xEFD7287B, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF1102E86, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF3FAA03A, 67 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF4EC1343, 18 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF6393CB3, 6 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF69410F3, 7 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF7F07DD6, 80 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF8C34C0A, 108 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF99F3627, 86 * 16}, //Physically_Based_Standard_Both_Shader
	{0xF9A86D9A, 104 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFB2FCB37, 145 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFC37FE29, 20 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFCF27EAF, 132 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFD5CE34A, 8 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFD6119AD, 115 * 16}, //Physically_Based_Standard_Both_Shader
	{0xFFE9F8DE, 96 * 16}, //Physically_Based_Standard_Both_Shader
	{0x048479C4, 113 * 16}, //Physically_Based_Standard_Shader
	{0x0B838FFB, 8 * 16}, //Physically_Based_Standard_Shader
	{0x10F1444C, 114 * 16}, //Physically_Based_Standard_Shader
	{0x139F0895, 10 * 16}, //Physically_Based_Standard_Shader
	{0x14AABB0F, 111 * 16}, //Physically_Based_Standard_Shader
	{0x18B88D18, 59 * 16}, //Physically_Based_Standard_Shader
	{0x191D541F, 112 * 16}, //Physically_Based_Standard_Shader
	{0x1A747E48, 112 * 16}, //Physically_Based_Standard_Shader
	{0x1B3E114A, 111 * 16}, //Physically_Based_Standard_Shader
	{0x1BAF0239, 59 * 16}, //Physically_Based_Standard_Shader
	{0x1CE5D107, 141 * 16}, //Physically_Based_Standard_Shader
	{0x2CF24D33, 7 * 16}, //Physically_Based_Standard_Shader
	{0x3308C28D, 55 * 16}, //Physically_Based_Standard_Shader
	{0x3748C2CC, 111 * 16}, //Physically_Based_Standard_Shader
	{0x3860AF41, 111 * 16}, //Physically_Based_Standard_Shader
	{0x3B74D458, 58 * 16}, //Physically_Based_Standard_Shader
	{0x3FA657EA, 10 * 16}, //Physically_Based_Standard_Shader
	{0x402860B5, 111 * 16}, //Physically_Based_Standard_Shader
	{0x5D625A76, 56 * 16}, //Physically_Based_Standard_Shader
	{0x62E1EAA7, 112 * 16}, //Physically_Based_Standard_Shader
	{0x668E9188, 10 * 16}, //Physically_Based_Standard_Shader
	{0x6EF87F0A, 6 * 16}, //Physically_Based_Standard_Shader
	{0x7AA6996A, 141 * 16}, //Physically_Based_Standard_Shader
	{0x7BD925C0, 113 * 16}, //Physically_Based_Standard_Shader
	{0x8000B9EE, 113 * 16}, //Physically_Based_Standard_Shader
	{0x81E85C35, 112 * 16}, //Physically_Based_Standard_Shader
	{0x8A2DCD80, 112 * 16}, //Physically_Based_Standard_Shader
	{0x8F77FD13, 111 * 16}, //Physically_Based_Standard_Shader
	{0x9B0C92A1, 140 * 16}, //Physically_Based_Standard_Shader
	{0x9C193278, 113 * 16}, //Physically_Based_Standard_Shader
	{0xA54E6048, 111 * 16}, //Physically_Based_Standard_Shader
	{0xB4EBEBC1, 7 * 16}, //Physically_Based_Standard_Shader
	{0xBE2104F7, 10 * 16}, //Physically_Based_Standard_Shader
	{0xBF77D46B, 58 * 16}, //Physically_Based_Standard_Shader
	{0xC20D03CE, 114 * 16}, //Physically_Based_Standard_Shader
	{0xC390C1DF, 9 * 16}, //Physically_Based_Standard_Shader
	{0xC76B0AA6, 112 * 16}, //Physically_Based_Standard_Shader
	{0xCA5EA7F1, 11 * 16}, //Physically_Based_Standard_Shader
	{0xD46FF13A, 112 * 16}, //Physically_Based_Standard_Shader
	{0xDFEEEF82, 111 * 16}, //Physically_Based_Standard_Shader
	{0xE8FEA881, 11 * 16}, //Physically_Based_Standard_Shader
	{0xEE880AF3, 114 * 16}, //Physically_Based_Standard_Shader
	{0xEEA9659B, 9 * 16}, //Physically_Based_Standard_Shader
	{0xEF956FAB, 114 * 16}, //Physically_Based_Standard_Shader
	{0xF678A62D, 140 * 16}, //Physically_Based_Standard_Shader
	{0xF68EC15C, 112 * 16}, //Physically_Based_Standard_Shader
	{0xA16BB368, 49 * 16}, //TwinkleEyeTranslucence_Shader
	{0xF3E61C16, 6 * 16}, //TwinkleEyeTranslucence_Shader
};