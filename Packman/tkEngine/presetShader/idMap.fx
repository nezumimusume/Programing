/*!
 * @brief	IDMap
 */
 

struct VS_INPUT
{
	float4	Position	: POSITION;
};
struct VS_OUTPUT
{
	float4 Position	: POSITION;
};

float4x4 g_mWVP;    // World * View * Projection matrix


/*!
 * @brief	IDマップ描画の頂点シェーダー
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	Out.Position = mul(g_mWVP, In.Position);
	
	return Out;
}
/*!
 * @brief	IDマップ描画のピクセルシェーダー
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

technique RenderIDMap
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader		= compile ps_2_0 PSMain();
	}
}