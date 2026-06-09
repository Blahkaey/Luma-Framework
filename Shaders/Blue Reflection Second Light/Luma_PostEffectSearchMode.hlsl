// ---- Created with 3Dmigoto v1.3.16 on Thu May 28 11:38:03 2026

cbuffer _Globals : register(b0)
{
  row_major float4x4 mClipToWorld : packoffset(c0);
  float3 vCenter : packoffset(c4);
  float fDistanceThreshold : packoffset(c4.w) = {0};
}

SamplerState samplerScene_s : register(s0);
SamplerState samplerDepth_s : register(s1);
Texture2D<float4> samplerScene_Tex : register(t0);
Texture2D<float4> samplerDepth_Tex : register(t1);


// 3Dmigoto declarations
#define cmp -


void main(
  float4 v0 : SV_Position0,
  float2 v1 : TEXCOORD0,
  out float4 o0 : SV_Target0)
{
  float4 r0,r1;
  uint4 bitmask, uiDest;
  float4 fDest;

  r0.x = 1 + -v1.y;
  r0.x = r0.x * 2 + -1;
  r0.xyzw = mClipToWorld._m10_m11_m12_m13 * r0.xxxx;
  r1.x = v1.x * 2 + -1;
  r0.xyzw = r1.xxxx * mClipToWorld._m00_m01_m02_m03 + r0.xyzw;
  r1.x = samplerDepth_Tex.Sample(samplerDepth_s, v1.xy).x;
  r0.xyzw = r1.xxxx * mClipToWorld._m20_m21_m22_m23 + r0.xyzw;
  r0.xyzw = mClipToWorld._m30_m31_m32_m33 + r0.xyzw;
  r0.xyz = r0.xyz / r0.www;
  r0.xyz = -vCenter.xyz + r0.xyz;
  r0.x = dot(r0.xyz, r0.xyz);
  r0.x = sqrt(r0.x);
  r0.x = cmp(r0.x < fDistanceThreshold);
  r1.xyzw = samplerScene_Tex.Sample(samplerScene_s, v1.xy).xyzw;
  r0.y = dot(r1.xyz, float3(0.298909992,0.586610019,0.114480004));//saturate(dot(r1.xyz, float3(0.298909992,0.586610019,0.114480004)));
  r0.y = 0.5 * r0.y;
  o0.xyz = r0.xxx ? r0.yyy : r1.xyz;
  o0.w = r1.w;
  return;
}