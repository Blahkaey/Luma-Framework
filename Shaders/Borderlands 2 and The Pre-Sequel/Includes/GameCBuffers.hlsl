#ifndef LUMA_GAME_CB_STRUCTS
#define LUMA_GAME_CB_STRUCTS

#ifdef __cplusplus
// This include is needed to allow reading shader types from c++.
#include "../../../Source/Core/includes/shader_types.h"
#endif

// Mirrors c++ name spaces.
namespace CB
{
// User-facing grade controls, drawn in DrawImGuiSettings (main.cpp) and read in Tonemap_0xD00AA2A7.ps_5_0.hlsl.
// Exposure/BloomIntensity/VignetteIntensity apply on both SDR and HDR (they live in the shared scene mix /
// vignette block); Saturation/HighlightDechroma/Contrast apply only on the HDR display path. All default to a
// vanilla no-op. SMAA metrics are passed via a dedicated CB at b1, not here.
struct LumaGameSettings
{
   float Exposure;           // 1 = vanilla. Scene exposure multiplier, scene-referred / pre-grade.
   float Saturation;         // 1 = vanilla. Oklab saturation multiplier on the final HDR color.
   float HighlightDechroma;  // 0 = off (only the mandatory DICE/gamut desat applies); higher = bright sources fade to white sooner.
   float BloomIntensity;     // 1 = vanilla. Scales the game's bloom contribution in the scene mix.
   float Contrast;           // 1 = vanilla. Slope contrast around 18% mid-gray on the final HDR color.
   float VignetteIntensity;  // 1 = vanilla. Scales the game's vignette darkening (0 = no vignette).
   float LumaBloomEnable;    // 0/1. 1 = composite Luma HDR pyramidal bloom (t5 BL2 / t8 TPS, additive); 0 = vanilla game bloom (t1).
   float DOFRadius;          // Luma Gaussian DoF strength (half-res blur extent, full-res px @ 4K).
   float DOFType;            // DoF path: 0 = vanilla game DoF, 1 = Luma separable Gaussian (t7 pre-blurred).
   float Dithering;          // 0/1 toggle. Animated triangular dither at output (HDR only) to break gradient banding.
   float VideoAutoHDREnable; // 0/1. 1 = light PumboAutoHDR on Bink videos (HDR only); 0 = flat SDR at paper white.
   float VideoAutoHDRBoost;  // 0..1. Highlight-expansion strength; peak = lerp(sRGB white, 250 nits, boost). 0 = off.

   // RenoDX-feature port (append-only: GameSettings is the LumaSettings cbuffer tail, so new fields must go
   // last to keep every existing offset stable; see cbuffers.h for the alignment rules).
   float ColorGradingIntensity; // 1 = vanilla. HDR only: fades the game's ImageAdjustments+LUT grade (0 = ungraded scene; DoF/bloom/vignette/exposure stay).
   float HDRHighlights;         // 1 = neutral. HDR only: luminance power curve above 18% mid-gray (>1 brightens, <1 compresses), pre-DICE.
   float HDRShadows;            // 1 = neutral. HDR only: luminance power curve below 18% mid-gray (>1 lifts, <1 deepens), pre-DICE.
   float HDRHueRestore;         // 0 = off. HDR only: restores the pre-DICE hue after display mapping (Oklab, hue channel only).
   float FilmGrainStrength;     // 0 = off. Monochrome multiplicative film grain driven by linear luminance (SDR + HDR).
};

#ifdef __cplusplus
// 17 floats, packed. HLSL packs the trailing struct members linearly, so the C++ raw size is the contract;
// the containing LumaGlobalSettingsPadded handles the final 16-byte DX padding (cbuffers.h).
static_assert(sizeof(LumaGameSettings) == 68, "LumaGameSettings layout drifted: append fields at the end only and keep this in sync");
#endif

// Game specific cbuffer (instance/pass) data.
struct LumaGameData
{
   float Dummy; // hlsl doesn't support empty structs
};
} // namespace CB

#endif // LUMA_GAME_CB_STRUCTS
