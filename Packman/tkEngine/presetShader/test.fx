/*!
 * @brief	テストシェーダー。
 */
float4x4 g_mWVP;		//!<ワールドビューマトリックス。

struct VS_INPUT
{
	float4	pos		:	POSITION;
	float4 	color	:	COLOR0;
};
struct VS_OUTPUT
{
	float4	pos		:	POSITION;
	float4 	color	:	COLOR0;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul( g_mWVP, In.pos );
//	Out.pos = In.pos;
	Out.color = In.color;
	return Out;
}

float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	return In.color;
}

technique Test
{
    pass p0
    {          
        VertexShader = compile vs_2_0 VSMain();
        PixelShader  = compile ps_2_0 PSMain();
    }
}

