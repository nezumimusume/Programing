/*!
 * @brief	トランスフォーム済みプリミティブを描画。
 */
 

struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

texture g_tex;
sampler TextureSampler = 
sampler_state
{
    Texture = <g_tex>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv 	= In.uv;
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	return tex2D( TextureSampler, In.uv );
}


struct VS_OUTPUT_GAUSSIAN_BLUR{
	float4		pos		: POSITION;
	float2 		tex0	: TEXCOORD0;
	float2 		tex1 	: TEXCOORD1;
	float2 		tex2 	: TEXCOORD2;
	float2 		tex3 	: TEXCOORD3;
	float2 		tex4 	: TEXCOORD4;
	float2 		tex5 	: TEXCOORD5;
	float2 		tex6	: TEXCOORD6;
	float2 		tex7 	: TEXCOORD7;
};


float2 g_offset;			//オフセット
float  g_weight[8];			//ガウスフィルタの重み。
float2 g_texSize;			//テクスチャサイズ。

/*!
 * @brief	ガウシアンXブラーの頂点シェーダー。
 */
VS_OUTPUT_GAUSSIAN_BLUR VSMainGaussianBlurX( VS_INPUT In )
{
	VS_OUTPUT_GAUSSIAN_BLUR Out;
	Out.pos = In.pos;
//	float2 tex = In.uv - float2(0.5/g_texSize.x, 0.5/g_texSize.y);
	float2 tex = In.uv ;
	Out.tex0 = tex + float2( - 1.0f/g_texSize.x, 0.0f );
    Out.tex1 = tex + float2( - 3.0f/g_texSize.x, 0.0f );
    Out.tex2 = tex + float2( - 5.0f/g_texSize.x, 0.0f );
    Out.tex3 = tex + float2( - 7.0f/g_texSize.x, 0.0f );
    Out.tex4 = tex + float2( - 9.0f/g_texSize.x, 0.0f );
    Out.tex5 = tex + float2( -11.0f/g_texSize.x, 0.0f );
    Out.tex6 = tex + float2( -13.0f/g_texSize.x, 0.0f );
    Out.tex7 = tex + float2( -15.0f/g_texSize.x, 0.0f );
	return Out;
}

/*!
 * @brief	ガウシアンYブラーの頂点シェーダー。
 */
VS_OUTPUT_GAUSSIAN_BLUR VSMainGaussianBlurY( VS_INPUT In )
{
	VS_OUTPUT_GAUSSIAN_BLUR Out = (VS_OUTPUT_GAUSSIAN_BLUR)0;
	Out.pos = In.pos;
//	float2 tex = In.uv - float2(0.5/g_texSize.x, 0.5/g_texSize.y);;
	float2 tex = In.uv ;
#if 1
	Out.tex0 = tex + float2( 0.0f,- 1.0f/g_texSize.y  );
    Out.tex1 = tex + float2( 0.0f,- 3.0f/g_texSize.y  );
    Out.tex2 = tex + float2( 0.0f,- 5.0f/g_texSize.y  );
    Out.tex3 = tex + float2( 0.0f,- 7.0f/g_texSize.y  );
    Out.tex4 = tex + float2( 0.0f,- 9.0f/g_texSize.y  );
    Out.tex5 = tex + float2( 0.0f,-11.0f/g_texSize.y  );
    Out.tex6 = tex + float2( 0.0f,-13.0f/g_texSize.y  );
    Out.tex7 = tex + float2( 0.0f,-15.0f/g_texSize.y  );
#else
	Out.tex0 = tex;
#endif
    return Out;
}
/*!
 * @brief	ガウシアンブラーのピクセルシェーダー。
 */
float4 PSMainGaussianBlur( VS_OUTPUT_GAUSSIAN_BLUR In ) : COLOR0
{
	float4 Color;
#if 1
	Color  = g_weight[0] * (tex2D( TextureSampler, In.tex0 )
	                 + tex2D( TextureSampler, In.tex7 + g_offset ));
	Color += g_weight[1] * (tex2D( TextureSampler, In.tex1 )
	                 + tex2D( TextureSampler, In.tex6 + g_offset ));
	Color += g_weight[2] * (tex2D( TextureSampler, In.tex2 )
	            + tex2D( TextureSampler, In.tex5 + g_offset ));
	Color += g_weight[3] * (tex2D( TextureSampler, In.tex3 )
	                 + tex2D( TextureSampler, In.tex4 + g_offset ));
	Color += g_weight[4] * (tex2D( TextureSampler, In.tex4 )
	                 + tex2D( TextureSampler, In.tex3 + g_offset ));
	Color += g_weight[5] * (tex2D( TextureSampler, In.tex5 )
	                 + tex2D( TextureSampler, In.tex2 + g_offset ));
	Color += g_weight[6] * (tex2D( TextureSampler, In.tex6 )
	                 + tex2D( TextureSampler, In.tex1 + g_offset ));
	Color += g_weight[7] * (tex2D( TextureSampler, In.tex7 )
	                 + tex2D( TextureSampler, In.tex0 + g_offset ));
#else
	Color = tex2D( TextureSampler, In.tex0 );
#endif
	return Color;
}

technique TransformedPrim
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader		= compile ps_2_0 PSMain();
	}
}
/*!
 * @brief	横ブラー。
 */
technique TransformedPrimGaussianBlurX
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMainGaussianBlurX();
		PixelShader		= compile ps_2_0 PSMainGaussianBlur();
	}
}

/*!
 * @brief	縦ブラー。
 */
technique TransformedPrimGaussianBlurY
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMainGaussianBlurY();
		PixelShader		= compile ps_2_0 PSMainGaussianBlur();
	}
}