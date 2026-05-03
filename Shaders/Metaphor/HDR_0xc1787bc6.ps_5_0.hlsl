cbuffer GFD_PSCONST_TONEMAP : register(b12)
{
	float FilmSlope : packoffset(c0);
	float FilmToe : packoffset(c0.y);
	float FilmShoulder : packoffset(c0.z);
	float FilmBlackClip : packoffset(c0.w);
	float FilmWhiteClip : packoffset(c1);
	float FilmAlpha : packoffset(c1.y);
}

cbuffer GFD_PSCONST_SYSTEM : register(b0)
{
	float2 resolution : packoffset(c0);
	float2 resolutionRev : packoffset(c0.z);
	float4x4 mtxView : packoffset(c1);
	float4x4 mtxInvView : packoffset(c5);
	float4x4 mtxProj : packoffset(c9);
	float4x4 mtxInvProj : packoffset(c13);
	float4 invProjParams : packoffset(c17);
}

cbuffer GFD_PSCONST_HDR : register(b11)
{
	float middleGray : packoffset(c0);
	float adaptedLum : packoffset(c0.y);
	float bloomScale : packoffset(c0.z);
	float starScale : packoffset(c0.w);
	float elapsedTime : packoffset(c1);
	float toonBloomScale : packoffset(c1.y);
	float adaptedLumAdjust : packoffset(c1.z);
	float adaptedLumLimit : packoffset(c1.w);
	float pbrIntensity : packoffset(c2);
}

SamplerState opaueSampler_s : register(s0);
SamplerState bloomSampler_s : register(s1);
SamplerState starSampler_s : register(s2);
SamplerState toneSampler_s : register(s3);
Texture2D<float4> opaueTexture : register(t0);
Texture2D<float4> bloomTexture : register(t1);
Texture2D<float4> starTexture : register(t2);
Texture2D<float4> toneTexture : register(t3);
Texture2D<float4> gbuffer1Texture : register(t4);

// From Shaders\Includes\Bloom.hlsl
// Bicubic upsampling in 4 texture fetches.
//
// f(x) = (4 + 3 * |x|^3 – 6 * |x|^2) / 6 for 0 <= |x| <= 1
// f(x) = (2 – |x|)^3 / 6 for 1 < |x| <= 2
// f(x) = 0 otherwise
//
// Source: https://www.researchgate.net/publication/220494113_Efficient_GPU-Based_Texture_Interpolation_using_Uniform_B-Splines
float4 sample_bicubic(Texture2D tex, SamplerState smp, float2 texcoord) {
	uint2 src_size;
	tex.GetDimensions(src_size.x, src_size.y);
	float2 inv_src_size = rcp(src_size);
		// transform the coordinate from [0,extent] to [-0.5, extent-0.5]
		float2 coord_grid = texcoord * src_size - 0.5;
		float2 index = floor(coord_grid);
		float2 fraction = coord_grid - index;
		float2 one_frac = 1.0 - fraction;
		float2 one_frac2 = one_frac * one_frac;
		float2 fraction2 = fraction * fraction;
		float2 w0 = 1.0 / 6.0 * one_frac2 * one_frac;
		float2 w1 = 2.0 / 3.0 - 0.5 * fraction2 * (2.0 - fraction);
		float2 w2 = 2.0 / 3.0 - 0.5 * one_frac2 * (2.0 - one_frac);
		float2 w3 = 1.0 / 6.0 * fraction2 * fraction;
		float2 g0 = w0 + w1;
		float2 g1 = w2 + w3;

		// h0 = w1/g0 - 1, move from [-0.5, extent-0.5] to [0, extent]
		float2 h0 = (w1 / g0) - 0.5 + index;
		float2 h1 = (w3 / g1) + 1.5 + index;

		// fetch the four linear interpolations
		float4 tex00 = tex.SampleLevel(smp, float2(h0.x, h0.y) * inv_src_size, 0.0);
		float4 tex10 = tex.SampleLevel(smp, float2(h1.x, h0.y) * inv_src_size, 0.0);
		float4 tex01 = tex.SampleLevel(smp, float2(h0.x, h1.y) * inv_src_size, 0.0);
		float4 tex11 = tex.SampleLevel(smp, float2(h1.x, h1.y) * inv_src_size, 0.0);

		// weigh along the y-direction
		tex00 = lerp(tex01, tex00, g0.y);
		tex10 = lerp(tex11, tex10, g0.y);

		// weigh along the x-direction
		return lerp(tex10, tex00, g0.x);
}

void main(
	float4 v0 : SV_POSITION0,
	float2 v1 : TEXCOORD0,
	out float4 o0 : SV_Target0)
{
	float4 r0,r1,r2,r3,r4,r5,r6,r7,r8,r9;
	uint4 bitmask, uiDest;
	float4 fDest;

	r0 = sample_bicubic(bloomTexture, bloomSampler_s, v1.xy);
	r1.xyz = sample_bicubic(starTexture, starSampler_s, v1.xy).xyz;
	r2.xyz = opaueTexture.Sample(opaueSampler_s, v1.xy).xyz;
	r3.xy = resolution.xy * v1.xy;
	r3.xy = (int2)r3.xy;
	r3.zw = float2(0,0);
	r3.xy = gbuffer1Texture.Load(r3.xyz).zw;
	r1.w = 255 * r3.y;
	r1.w = (uint)r1.w;
	r1.w = (int)r1.w & 8;
	if (r1.w == 0) {
		r1.w = 255 * r3.x;
		r1.w = (uint)r1.w;
		r1.w = (uint)r1.w >> 4;
		r1.w = (uint)r1.w;
		r1.w = 0.0666666701 * r1.w;
		r2.w = toneTexture.Sample(toneSampler_s, float2(0.5,0.5)).x;
		r3.x = 1 + -middleGray;
		r1.w = r3.x * r1.w + middleGray;
		r3.xyz = r2.xyz * r1.www;
		r3.xyz = adaptedLum * r3.xyz;
		r1.w = max(adaptedLumLimit, r2.w);
		r1.w = 9.99999975e-05 + r1.w;
		r1.w = -adaptedLum + r1.w;
		r1.w = adaptedLumAdjust * r1.w + adaptedLum;
		r3.xyz = r3.xyz / r1.www;
		r1.w = dot(float3(0.439700812,0.382978052,0.1773348), r3.xyz);
		r4.y = dot(float3(0.0897923037,0.813423157,0.096761629), r3.xyz);
		r4.z = dot(float3(0.0175439864,0.111544058,0.870704114), r3.xyz);
		r2.w = min(r4.y, r1.w);
		r2.w = min(r2.w, r4.z);
		r3.w = max(r4.y, r1.w);
		r3.w = max(r3.w, r4.z);
		r5.xy = max(float2(1.00000001e-10,0.00999999978), r3.ww);
		r2.w = max(1.00000001e-10, r2.w);
		r2.w = r5.x + -r2.w;
		r2.w = r2.w / r5.y;
		r3.w = r1.w == r4.y;
		r4.w = r4.z == r4.y;
		r3.w = r3.w ? r4.w : 0;
		r4.w = r4.y + -r4.z;
		r4.w = 1.73205078 * r4.w;
		r5.x = r1.w * 2 + -r4.y;
		r5.x = r5.x + -r4.z;
		r5.y = min(abs(r5.x), abs(r4.w));
		r5.z = max(abs(r5.x), abs(r4.w));
		r5.z = 1 / r5.z;
		r5.y = r5.y * r5.z;
		r5.z = r5.y * r5.y;
		r5.w = r5.z * 0.0208350997 + -0.0851330012;
		r5.w = r5.z * r5.w + 0.180141002;
		r5.w = r5.z * r5.w + -0.330299497;
		r5.z = r5.z * r5.w + 0.999866009;
		r5.w = r5.y * r5.z;
		r6.x = abs(r5.x) < abs(r4.w);
		r5.w = r5.w * -2 + 1.57079637;
		r5.w = r6.x ? r5.w : 0;
		r5.y = r5.y * r5.z + r5.w;
		r5.z = r5.x < -r5.x;
		r5.z = r5.z ? -3.141593 : 0;
		r5.y = r5.y + r5.z;
		r5.z = min(r5.x, r4.w);
		r4.w = max(r5.x, r4.w);
		r5.x = r5.z < -r5.z;
		r4.w = r4.w >= -r4.w;
		r4.w = r4.w ? r5.x : 0;
		r4.w = r4.w ? -r5.y : r5.y;
		r4.w = 57.2957802 * r4.w;
		r3.w = r3.w ? 0 : r4.w;
		r4.w = r3.w < 0;
		r5.x = 360 + r3.w;
		r3.w = r4.w ? r5.x : r3.w;
		r3.w = max(0, r3.w);
		r3.w = min(360, r3.w);
		r4.w = 180 < r3.w;
		r5.x = -360 + r3.w;
		r3.w = r4.w ? r5.x : r3.w;
		r3.w = 0.0148148146 * r3.w;
		r3.w = 1 + -abs(r3.w);
		r3.w = max(0, r3.w);
		r4.w = r3.w * -2 + 3;
		r3.w = r3.w * r3.w;
		r3.w = r4.w * r3.w;
		r3.w = r3.w * r3.w;
		r2.w = r3.w * r2.w;
		r3.w = 0.0299999993 + -r1.w;
		r2.w = r3.w * r2.w;
		r4.x = r2.w * 0.180000007 + r1.w;
		r5.x = dot(float3(1.45143926,-0.236510754,-0.214928567), r4.xyz);
		r5.y = dot(float3(-0.0765537769,1.17622972,-0.0996759236), r4.xyz);
		r5.z = dot(float3(0.00831614807,-0.00603244966,0.997716308), r4.xyz);
		r4.xyz = max(float3(0,0,0), r5.xyz);
		r1.w = dot(r4.xyz, float3(0.272228718,0.674081743,0.0536895171));
		r4.xyz = r4.xyz + -r1.www;
		r4.xyz = r4.xyz * float3(0.959999979,0.959999979,0.959999979) + r1.www;
		r5.xy = float2(1,0.180000007) + FilmBlackClip;
		r1.w = -FilmToe + r5.x;
		r2.w = 1 + FilmWhiteClip;
		r3.w = -FilmShoulder + r2.w;
		r4.w = 0.800000012 < FilmToe;
		r5.xz = float2(0.819999993,1) + -FilmToe;
		r5.xz = r5.xz / FilmSlope;
		r5.y = r5.y / r1.w;
		r5.xw = float2(-0.744727492,-1) + r5.xy;
		r5.w = 1 + -r5.w;
		r5.y = r5.y / r5.w;
		r5.y = log2(r5.y);
		r5.y = 0.346573591 * r5.y;
		r5.w = r1.w / FilmSlope;
		r5.y = -r5.y * r5.w + -0.744727492;
		r4.w = r4.w ? r5.x : r5.y;
		r5.x = r5.z + -r4.w;
		r5.y = FilmShoulder / FilmSlope;
		r5.y = r5.y + -r5.x;
		r4.xyz = log2(r4.xyz);
		r6.xyz = float3(0.30103001,0.30103001,0.30103001) * r4.xyz;
		r5.xzw = r4.xyz * float3(0.30103001,0.30103001,0.30103001) + r5.xxx;
		r5.xzw = FilmSlope * r5.xzw;
		r6.w = r1.w + r1.w;
		r7.x = -2 * FilmSlope;
		r1.w = r7.x / r1.w;
		r7.xyz = r4.xyz * float3(0.30103001,0.30103001,0.30103001) + -r4.www;
		r8.xyz = r7.xyz * r1.www;
		r8.xyz = float3(1.44269502,1.44269502,1.44269502) * r8.xyz;
		r8.xyz = exp2(r8.xyz);
		r8.xyz = float3(1,1,1) + r8.xyz;
		r8.xyz = r6.www / r8.xyz;
		r8.xyz = -FilmBlackClip + r8.xyz;
		r1.w = r3.w + r3.w;
		r6.w = FilmSlope + FilmSlope;
		r3.w = r6.w / r3.w;
		r4.xyz = r4.xyz * float3(0.30103001,0.30103001,0.30103001) + -r5.yyy;
		r4.xyz = r4.xyz * r3.www;
		r4.xyz = float3(1.44269502,1.44269502,1.44269502) * r4.xyz;
		r4.xyz = exp2(r4.xyz);
		r4.xyz = float3(1,1,1) + r4.xyz;
		r4.xyz = r1.www / r4.xyz;
		r4.xyz = -r4.xyz + r2.www;
		r9.xyz = r6.xyz < r4.www;
		r8.xyz = r9.xyz ? r8.xyz : r5.xzw;
		r6.xyz = r5.yyy < r6.xyz;
		r4.xyz = r6.xyz ? r4.xyz : r5.xzw;
		r1.w = r5.y + -r4.w;
		r5.xzw = saturate(r7.xyz / r1.www);
		r1.w = r5.y < r4.w;
		r6.xyz = float3(1,1,1) + -r5.xzw;
		r5.xyz = r1.www ? r6.xyz : r5.xzw;
		r6.xyz = -r5.xyz * float3(2,2,2) + float3(3,3,3);
		r5.xyz = r5.xyz * r5.xyz;
		r5.xyz = r5.xyz * r6.xyz;
		r4.xyz = r4.xyz + -r8.xyz;
		r4.xyz = r5.xyz * r4.xyz + r8.xyz;
		r1.w = dot(r4.xyz, float3(0.272228718,0.674081743,0.0536895171));
		r4.xyz = r4.xyz + -r1.www;
		r4.xyz = r4.xyz * float3(0.930000007,0.930000007,0.930000007) + r1.www;
		r4.xyz = max(float3(0,0,0), r4.xyz);
		r4.xyz = r4.xyz + -r3.xyz;
		r2.xyz = FilmAlpha * r4.xyz + r3.xyz;
	}
	r1.xyz = starScale * r1.xyz + r2.xyz;
	o0.xyz = r0.xyz * r0.www + r1.xyz;
	o0.w = 1;
	return;
}