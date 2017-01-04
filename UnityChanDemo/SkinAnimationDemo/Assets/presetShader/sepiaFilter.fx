/*!
 * @brief	セピアフィルター。
 */


struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

float2 g_sceneTexSize;	//シーンテクスチャのサイズ。
texture g_scene;
sampler SceneSampler = sampler_state
{
	Texture = <g_scene>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
    AddressV = CLAMP;
};

float g_blendRate;		//ブレンド率。


/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv + float2( 0.5/g_sceneTexSize.x, 0.5/g_sceneTexSize.y);
	return Out;
}


/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	float4 sceneColor = tex2D(SceneSampler, In.uv);
	float4 color = sceneColor;
	float Y = 0.29900 * color.r + 0.58700 * color.g + 0.11400 * color.b;
	float Cb = -0.2f;
	float Cr = 0.1f;
	color.r = Y + 1.40200 * Cr;
	color.g = Y - 0.34414 * Cb - 0.71414 * Cr;
	color.b = Y + 1.77200 * Cb;
	return lerp(sceneColor, color, g_blendRate);
}

technique Default
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}

