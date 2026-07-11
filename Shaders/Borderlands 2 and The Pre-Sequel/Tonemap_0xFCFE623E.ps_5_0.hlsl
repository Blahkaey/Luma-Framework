// Borderlands: The Pre-Sequel — tonemap / HDR injection point (dgVoodoo->DX11 hash 0xFCFE623E).
// TPS runs the SAME UE3/Gearbox uber-post tonemap as Borderlands 2, but its native shader
// (tps_tonemap_0xF8997849) inserts a LightShaftTexture at sampler slot 1, which shifts bloom/vignette/LUT/DOF
// DOWN one slot vs BL2 (the DX9 BL2 tonemap_0x54ED86A0 has LUT@s3/DOF@s4; TPS has lightshaft@s1, LUT@s4,
// DOF@s5). dgVoodoo maps DX9 sN 1:1 onto DX11 tN, so the same shift lands in the DX11 register space Luma
// sees, so a dedicated slot map (below) rebinds each named texture to its shifted register.
//
// The grade MATH is identical between the two games, so we set the slot-map + light-shaft macros here and
// pull in the shared grade impl (Luma_BL2TPS_Tonemap.hlsl, one source of truth), then add our own main().
// Injected Luma bloom moves to t8 because TPS's native DOF occupies t5; the Gaussian DoF prefilter (t7)
// stays put — free on TPS. The mod binds Luma bloom at t8 when it detects this tonemap hash.
#define TM_HAS_LIGHTSHAFT 1
#define TM_T_LIGHTSHAFT   t1 // LightShaftTexture (god rays) — TPS-only, inserted at slot 1
#define TM_T_BLOOM        t2 // FilterColor1Texture (screen-blend bloom)
#define TM_T_VIGNETTE     t3 // VignetteTexture
#define TM_T_LUT          t4 // ColorGradingLUT (256x16, 16-slice)
#define TM_T_DOF          t5 // LowResPostProcessBuffer (half-res DOF)
#define TM_T_LUMABLOOM    t8 // injected Luma HDR bloom (t5 is the native DOF on TPS — bind higher to avoid the clash)
#define TM_S_BLOOM        s2
#define TM_S_VIGNETTE     s3
#define TM_S_LUT          s4
#define TM_S_DOF          s5
#include "Luma_BL2TPS_Tonemap.hlsl"

void main(
    float4 v0 : SV_POSITION0,
    float4 v1 : TEXCOORD8,
    float4 v2 : COLOR0,
    float4 v3 : COLOR1,
    float4 v4 : TEXCOORD9,
    float4 v5 : TEXCOORD0,
    float4 v6 : TEXCOORD1,
    float4 v7 : TEXCOORD2,
    float4 v8 : TEXCOORD3,
    float4 v9 : TEXCOORD4,
    float4 v10 : TEXCOORD5,
    float4 v11 : TEXCOORD6,
    float4 v12 : TEXCOORD7,
    out float4 o0 : SV_TARGET0)
{
   o0 = RunTonemap(v0, v5, v6);
}
