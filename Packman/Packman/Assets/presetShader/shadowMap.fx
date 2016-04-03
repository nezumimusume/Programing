/*!
 * @brief	シャドウマップ。
 */




struct VS_INPUT
{
	float4	Position	: POSITION;
};
struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float4 depth	: TEXCOORD;
};

float4x4	g_mWVP;		//ワールドビュープロジェクション行列。

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	Out.Position = mul(In.Position, g_mWVP);
	Out.depth = Out.Position;
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	//深度を書き込む。
	float z = In.depth.z / In.depth.w;
	return float4(z,z,z,z);
}

technique RenderShadowMap
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}
