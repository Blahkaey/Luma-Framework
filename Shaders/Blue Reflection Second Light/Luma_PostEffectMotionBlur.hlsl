////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VERTEXSHADER
	#define PIXELSHADER
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cbuffer cbMotionBlur : register(b0)
{
	float VelocityScale : packoffset(c0.x);
	float MaxBlurRadius : packoffset(c0.y);
	float RcpMaxBlurRadius : packoffset(c0.z);
	float LoopCount : packoffset(c0.w);
	float2 TileMaxOffs : packoffset(c1.x);
	float TileMaxLoop : packoffset(c1.z);
	float4 MainTex_TexelSize : packoffset(c2);
	float4 CameraMotionVectorsTexture_TexelSize : packoffset(c3);
	float2 VelocityTex_TexelSize : packoffset(c4.x);
	float2 NeighborMaxTex_TexelSize : packoffset(c4.z);
	float4 DepthParams : packoffset(c5);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct VS_OUTPUT
{
    float4 vertex : SV_Position;
    float2 texcoord : TEXCOORD0;
};

SamplerState s_samplLinearClamp : register(s7);
SamplerState s_samplPointClamp  : register(s8);

#ifdef VELOCITY_SETUP
Texture2D<float> t_DepthMap : register(t0);
Texture2D<float4> t_DecodedVelocityMap : register(t1);
#endif

#if defined(TILEMAX_1) || defined(TILEMAX_2) || defined(TILEMAX_V) || defined(NEIGHBOR_MAX)
Texture2D<float4> t_MainMap : register(t0);
#endif

#ifdef RECONSTRUCTION
Texture2D<float4> t_MainMap : register(t0);
Texture2D<float4> t_NeighborTileMap : register(t1);
Texture2D<float4> t_VelocityInfoMap : register(t2);
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VERTEXSHADER
VS_OUTPUT main(uint vertexIdx : SV_VertexID)
{
	VS_OUTPUT output;
	
	const float4 vertex[] = {
		{ -1.0, -1.0, 0.0, 1.0 },
		{  3.0, -1.0, 0.0, 1.0 },
		{ -1.0,  3.0, 0.0, 1.0 }
	};
	
	output.vertex = vertex[vertexIdx];
	output.texcoord = vertex[vertexIdx].xy * float2(0.5, -0.5) + float2(0.5, 0.5);
	
	return output;
}
#endif // VERTEXSHADER

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef PIXELSHADER

#define TWO_PI          6.28318530718

float LinearizeDepth(Texture2D<float> tex, SamplerState samp, float2 uv)
{
	float depth = tex.SampleLevel(samp, uv, 0).x;
	float temp = depth * DepthParams.x + DepthParams.y;
	temp = 1.0 / temp;
	
	return temp / DepthParams.z;
}

float2 MaxV(float2 v1, float2 v2)
{
	return dot(v1, v1) < dot(v2, v2) ? v2 : v1;
}

#ifdef RECONSTRUCTION
// Returns true or false with a given interval.
bool Interval(float phase, float interval)
{
	return frac(phase / interval) > 0.499;
}

float GradientNoise(float2 uv)
{
    uv = floor(uv * MainTex_TexelSize.xy);
    float f = dot(float2(0.06711056, 0.00583715), uv);
    return frac(52.9829189 * frac(f));
}

// Jitter function for tile lookup
float2 JitterTile(float2 uv)
{
	float rx, ry;
	sincos(GradientNoise(uv + float2(2.0, 0.0)) * TWO_PI, ry, rx);
	return float2(rx, ry) * NeighborMaxTex_TexelSize.xy * 0.25;
}

// Velocity sampling function
float3 SampleVelocity(float2 uv)
{
	float3 v = t_VelocityInfoMap.SampleLevel(s_samplLinearClamp, uv, 0).xyz;
	return float3((v.xy * 2.0 - 1.0) * MaxBlurRadius, v.z);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VELOCITY_SETUP
float4 main(VS_OUTPUT input) : SV_Target0
{
	// Sample the motion vector.
	float2 v = t_DecodedVelocityMap.SampleLevel(s_samplLinearClamp, input.texcoord, 0).xy;

	// Apply the exposure time and convert to the pixel space.
	v *= (VelocityScale * 0.5) * CameraMotionVectorsTexture_TexelSize.xy;

	// Clamp the vector with the maximum blur radius.
	v /= max(1.0, length(v) * RcpMaxBlurRadius);

	// Sample the depth of the pixel.
	float d = LinearizeDepth(t_DepthMap, s_samplPointClamp, input.texcoord);

	// Pack into 10/10/10/2 format.
	return float4((v * RcpMaxBlurRadius + 1.0) * 0.5, d, 0.0);
}
#endif

#ifdef TILEMAX_1
float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 d = MainTex_TexelSize.zwzw * float4(-0.5, -0.5, 0.5, 0.5);

	float2 v1 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.xy, 0).xy;
	float2 v2 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.zy, 0).xy;
	float2 v3 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.xw, 0).xy;
	float2 v4 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.zw, 0).xy;

	v1 = (v1 * 2.0 - 1.0) * MaxBlurRadius;
	v2 = (v2 * 2.0 - 1.0) * MaxBlurRadius;
	v3 = (v3 * 2.0 - 1.0) * MaxBlurRadius;
	v4 = (v4 * 2.0 - 1.0) * MaxBlurRadius;

	return float4(MaxV(MaxV(MaxV(v1, v2), v3), v4), 0.0, 0.0);
}
#endif

#ifdef TILEMAX_2
float4 main(VS_OUTPUT input) : SV_Target0
{
	float4 d = MainTex_TexelSize.zwzw * float4(-0.5, -0.5, 0.5, 0.5);

	float2 v1 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.xy, 0).xy;
	float2 v2 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.zy, 0).xy;
	float2 v3 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.xw, 0).xy;
	float2 v4 = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord + d.zw, 0).xy;

	return float4(MaxV(MaxV(MaxV(v1, v2), v3), v4), 0.0, 0.0);
}
#endif

#ifdef TILEMAX_V
float4 main(VS_OUTPUT input) : SV_Target0
{
	float2 uv0 = input.texcoord + MainTex_TexelSize.zw * TileMaxOffs.xy;

	float2 du = float2(MainTex_TexelSize.z, 0.0);
	float2 dv = float2(0.0, MainTex_TexelSize.w);

	float2 vo = 0.0;

	[loop]
	for (int ix = 0; ix < TileMaxLoop; ix++)
	{
		[loop]
		for (int iy = 0; iy < TileMaxLoop; iy++)
		{
			float2 uv = uv0 + du * ix + dv * iy;
			vo = MaxV(vo, t_MainMap.SampleLevel(s_samplPointClamp, uv, 0).xy);
		}
	}

	return float4(vo, 0.0, 0.0);
}
#endif

#ifdef NEIGHBOR_MAX
float4 main(VS_OUTPUT input) : SV_Target0
{
	const float cw = 1.01; // Center weight tweak

	float4 d = MainTex_TexelSize.zwzw * float4(1.0, 1.0, -1.0, 0.0);

	float2 v1 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord - d.xy, 0).xy;
	float2 v2 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord - d.wy, 0).xy;
	float2 v3 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord - d.zy, 0).xy;

	float2 v4 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord - d.xw, 0).xy;
	float2 v5 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord, 0).xy * cw;
	float2 v6 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord + d.xw, 0).xy;

	float2 v7 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord + d.zy, 0).xy;
	float2 v8 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord + d.wy, 0).xy;
	float2 v9 = t_MainMap.SampleLevel(s_samplPointClamp, input.texcoord + d.xy, 0).xy;

	float2 va = MaxV(v1, MaxV(v2, v3));
	float2 vb = MaxV(v4, MaxV(v5, v6));
	float2 vc = MaxV(v7, MaxV(v8, v9));

	return float4(MaxV(va, MaxV(vb, vc)) * (1.0 / cw), 0.0, 0.0);
}
#endif

#ifdef RECONSTRUCTION
float4 main(VS_OUTPUT input) : SV_Target0
{
	// Color sample at the center point
	const float4 c_p = t_MainMap.SampleLevel(s_samplLinearClamp, input.texcoord, 0);

	// Velocity/Depth sample at the center point
	const float3 vd_p = SampleVelocity(input.texcoord);
	const float l_v_p = max(length(vd_p.xy), 0.5);
	const float rcp_d_p = 1.0 / vd_p.z;

	// NeighborMax vector sample at the center point
	const float2 v_max = t_NeighborTileMap.SampleLevel(s_samplPointClamp, input.texcoord + JitterTile(input.texcoord), 0).xy;
	const float l_v_max = length(v_max);
	const float rcp_l_v_max = 1.0 / l_v_max;

	// Escape early if the NeighborMax vector is small enough.
	if (l_v_max < 2.0) return c_p;

	// Use V_p as a secondary sampling direction except when it's too small
	// compared to V_max. This vector is rescaled to be the length of V_max.
	const float2 v_alt = (l_v_p * 2.0 > l_v_max) ? vd_p.xy * (l_v_max / l_v_p) : v_max;

	// Determine the sample count.
	const float sc = floor(min(LoopCount, l_v_max * 0.5));

	// Loop variables (starts from the outermost sample)
	const float dt = 1.0 / sc;
	const float t_offs = (GradientNoise(input.texcoord) - 0.5) * dt;
	float t = 1.0 - dt * 0.5;
	float count = 0.0;

	// Background velocity
	// This is used for tracking the maximum velocity in the background layer.
	float l_v_bg = max(l_v_p, 1.0);

	// Color accumlation
	float4 acc = 0.0;

	[loop]
	while (t > dt * 0.25)
	{
		// Sampling direction (switched per every two samples)
		const float2 v_s = Interval(count, 4.0) ? v_alt : v_max;

		// Sample position (inverted per every sample)
		const float t_s = (Interval(count, 2.0) ? -t : t) + t_offs;

		// Distance to the sample position
		const float l_t = l_v_max * abs(t_s);

		// UVs for the sample position
		const float2 uv0 = input.texcoord + v_s * t_s * MainTex_TexelSize.zw;
		const float2 uv1 = input.texcoord + v_s * t_s * VelocityTex_TexelSize.xy;

		// Color sample
		const float3 c = t_MainMap.SampleLevel(s_samplLinearClamp, uv0, 0).xyz;

		// Velocity/Depth sample
		const float3 vd = SampleVelocity(uv1);

		// Background/Foreground separation
		const float fg = saturate((vd_p.z - vd.z) * 20.0 * rcp_d_p);

		// Length of the velocity vector
		const float l_v = lerp(l_v_bg, length(vd.xy), fg);

		// Sample weight
		// (Distance test) * (Spreading out by motion) * (Triangular window)
		const float w = saturate(l_v - l_t) / l_v * (1.2 - t);

		// Color accumulation
		acc += float4(c, 1.0) * w;

		// Update the background velocity.
		l_v_bg = max(l_v_bg, l_v);

		// Advance to the next sample.
		t = Interval(count, 2.0) ? t - dt : t;
		count += 1.0;
	}

	// Add the center sample.
	acc += float4(c_p.rgb, 1.0) * (1.2 / (l_v_bg * sc * 2.0));

	return float4(acc.rgb / acc.a, c_p.a);
}
#endif

#endif // PIXELSHADER