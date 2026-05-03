cbuffer GFD_PSCONST_SAMPLE_OFFSETS : register(b12)
{
	float4 sampleOffsets[13] : packoffset(c0);
}

cbuffer GFD_PSCONST_SAMPLE_WEIGHTS : register(b13)
{
	float4 sampleWeights[13] : packoffset(c0);
}

SamplerState sampler0_s : register(s0);
Texture2D<float4> texture0 : register(t0);

float Gaussian (float sigma, float x)
{
    return exp(-(x*x) / (2.0 * sigma*sigma));
}

static const float sigma = 2.0f;
static const uint samples = 7;
static const uint halfSamples = samples / 2;

// for bloom this does a optimized 13 tap gaussian blur with sigma 2.0
// TODO: replace with a separable blur
void main(
	float4 v0 : SV_POSITION0,
	float2 uv : TEXCOORD0,
	out float4 o0 : SV_Target0)
{
	float4 r0,r1;
	uint4 bitmask, uiDest;
	float4 fDest;

	float total = 0.0f;
	float4 ret = 0.0f;
	float2 sourceSize;
	texture0.GetDimensions(sourceSize.x, sourceSize.y);
	float2 pixelSize = 1.0f / sourceSize;
	for (uint iy = 0; iy < samples; ++iy)
	{
		float fy = Gaussian(sigma, float(iy) - float(halfSamples));
		float offsety = (float(iy)-float(halfSamples)) * pixelSize.y;
		for (uint ix = 0; ix < samples; ++ix)
		{
			float fx = Gaussian (sigma, float(ix) - float(halfSamples));
			float offsetx = (float(ix)-float(halfSamples)) * pixelSize.x;
			total += fx * fy;            
			ret += texture0.Sample(sampler0_s, uv + float2(offsetx, offsety)).rgba * fx*fy;
		}
	}
	o0.xyzw = ret / total;
	return;
}