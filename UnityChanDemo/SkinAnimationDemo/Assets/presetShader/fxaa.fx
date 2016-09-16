/*!
 *@brief	FXAA
 *@details
 * FXAAを使用したアンチエイリアス。
 */

struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

texture g_scene;
float2 g_sceneTexSize;	//シーンテクスチャのサイズ。
sampler SceneSampler = sampler_state
{
	Texture = <g_scene>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};


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
float4 FxaaPixelShader( 
	float2 pos, 
	float4 fxaaConsolePosPos,
	float2 fxaaQualityRcpFrame,
    float4 fxaaConsoleRcpFrameOpt,
    float4 fxaaConsoleRcpFrameOpt2,
    float4 fxaaConsole360RcpFrameOpt2,
    float fxaaQualitySubpix,
    float fxaaQualityEdgeThreshold,
    float fxaaQualityEdgeThresholdMin,
    float fxaaConsoleEdgeSharpness,
    float fxaaConsoleEdgeThreshold,
    float fxaaConsoleEdgeThresholdMin,
    float4 fxaaConsole360ConstDir
)
{
}
/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	return tex2D( SceneSampler, In.uv );
}

technique FXAA
{
	pass p0
	{
		VertexShader	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}
