#include "Includes/Common.hlsl"

cbuffer _Globals : register(b0)
{
  float2 SimulateHDRParams : packoffset(c0);
}

SamplerState smplScene_s : register(s0);
SamplerState smplDepth_s : register(s1);
Texture2D<float4> smplScene_Tex : register(t0);
Texture2D<float4> smplDepth_Tex : register(t1);


// 3Dmigoto declarations
#define cmp -


void main(
  float4 v0 : SV_Position0,
  float2 v1 : TEXCOORD0,
  out float4 o0 : SV_Target0)
{
  float4 r0,r1,r2,r3;
  uint4 bitmask, uiDest;
  float4 fDest;

  r0.x = smplDepth_Tex.Sample(smplDepth_s, v1.xy).x;
  r0.y = v1.x * 2 + -1;
  r0.z = 1 + -v1.y;
  r0.z = r0.z * 2 + -1;
  
  float4 clip_pos = float4(r0.yzx, 1.0f);
  clip_pos = mul(clip_pos, LumaData.GameData.CurrentProjectionInverseMatrix);
  clip_pos /= clip_pos.w;
  float4 world_pos = mul(clip_pos, LumaData.GameData.CurrentViewInverseMatrix);
  r0 = world_pos;
  
  r1.xyz = LumaData.GameData.PreviousViewProjectionMatrix._m10_m11_m13 * r0.yyy;
  r1.xyz = r0.xxx * LumaData.GameData.PreviousViewProjectionMatrix._m00_m01_m03 + r1.xyz;
  r1.xyz = r0.zzz * LumaData.GameData.PreviousViewProjectionMatrix._m20_m21_m23 + r1.xyz;
  r1.xyz = r0.www * LumaData.GameData.PreviousViewProjectionMatrix._m30_m31_m33 + r1.xyz;
  r1.xy = r1.xy / r1.zz;
  r1.zw = v1.xy * float2(2,-2) + float2(-1,1);
  r1.xy = r1.zw + -r1.xy;
  
  float2 uvVelocity;
  uvVelocity.x =  r1.x * 0.5;
  uvVelocity.y = -r1.y * 0.5;
  
  float4 velocity = smplScene_Tex.Sample(smplScene_s, v1.xy);
  if (velocity.y == -1.f)
  {
	velocity.xy = uvVelocity.xy;
  }
  
  float2 jitter_delta = LumaData.GameData.PrevJitters - LumaData.GameData.CurrJitters;
  velocity.xy -= jitter_delta;
  
  //velocity.xy *= float2(1920, 1080);
  
  o0 = (velocity);
  
  return;
}