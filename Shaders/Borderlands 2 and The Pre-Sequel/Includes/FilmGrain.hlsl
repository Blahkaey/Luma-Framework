#ifndef LUMA_BL2TPS_FILM_GRAIN
#define LUMA_BL2TPS_FILM_GRAIN

// Perceptual film grain for the BL2/TPS tonemap. Monochrome and multiplicative: one random value per pixel
// scales luminance, so brightness flickers subtly without per-channel color speckle; graininess follows film
// density (Bartleson), so it is strongest in shadows/mid-tones and dies out toward (and above) paper white —
// HDR highlights stay clean and black stays black. This is an artistic control; the tonemap's triangular
// output dithering remains the anti-banding stage.
//
// Density/graininess formula adapted from RenoDX (https://github.com/clshortfuse/renodx),
// src/shaders/effects.hlsl — MIT License, Copyright (c) 2025 Carlos Lopez Jr.
//
// Include after ../Includes/Color.hlsl (uses GetLuminance).

namespace FilmGrain
{
float Random(float2 xy)
{
   return frac(sin(dot(xy, float2(12.9898, 78.233))) * 43758.5453);
}

// Bartleson: film graininess as a function of film density (0-3 maps black..reference white).
// https://www.imaging.org/common/uploaded%20files/pdfs/Papers/2003/PICS-0-287/8583.pdf
float Graininess(float density)
{
   if (density <= 0.0)
      return 0.0; // luminance can be ~0/negative; pow would be unsafe
   return pow(10.0, 0.880 - (0.736 * density) - (0.003 * pow(density, 7.6)));
}

// color: linear BT.709, 1.0 = paper white. pixelPos: unnormalized pixel coordinates (SV_Position.xy) — a
// per-pixel spatial seed, deliberately NOT normalized UV (tiny correlated UV values degrade the sin hash).
// strength: 0-1 user slider.
float3 Apply(float3 color, float2 pixelPos, uint frameIndex, float strength)
{
   // Golden-ratio frame step, wrapped to keep the sin() hash argument in a precision-safe range.
   float seed = float(frameIndex % 1024u) * 0.618034;
   float y = max(0.0, GetLuminance(color));
   float density = y * 3.0; // ideal film density spans 0-3 over black..reference white
   float randomFactor = Random(pixelPos + seed) * 2.0 - 1.0;
   float yChange = randomFactor * Graininess(density) * (strength * 0.03) * 1.667; // 1.667 boost caps the max change at ~0.05
   return color * (1.0 + yChange);
}
} // namespace FilmGrain

#endif // LUMA_BL2TPS_FILM_GRAIN
