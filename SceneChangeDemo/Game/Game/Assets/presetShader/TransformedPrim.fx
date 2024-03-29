/*!
 * @brief	トランスフォーム済みプリミティブを描画。
 */
 
#include "Common.h" 

struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};
float2 g_offset;				//オフセット

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
	Out.uv 	= In.uv + g_offset;
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	return tex2D( TextureSampler, In.uv );
}


struct VS_OUTPUT_BLUR{
	float4		pos		: POSITION;
	float2 		tex0	: TEXCOORD0;
	float2 		tex1 	: TEXCOORD1;
	float2 		tex2 	: TEXCOORD2;
};


float2 g_texSize;			//テクスチャサイズ。
float  g_weight[8];				//ガウスフィルタの重み。

/*!
 * @brief	Xブラーの頂点シェーダー。
 */
VS_OUTPUT_BLUR VSMainBlurX( VS_INPUT In )
{
	VS_OUTPUT_BLUR Out;
	Out.pos = In.pos;

	float2 tex = In.uv ;
	Out.tex0 = tex;
	Out.tex1 = float2( 0.5f/g_texSize.x, 0.0f );
    Out.tex2 = float2( 1.0f/g_texSize.x, 0.0f );
	return Out;
}

/*!
 * @brief	Yブラーの頂点シェーダー。
 */
VS_OUTPUT_BLUR VSMainBlurY( VS_INPUT In )
{
	VS_OUTPUT_BLUR Out = (VS_OUTPUT_BLUR)0;
	Out.pos = In.pos;
	float2 tex = In.uv ;

	Out.tex0 = tex + float2( 0.5/g_texSize.x, 0.5/g_texSize.y);;
	Out.tex1 = float2( 0.0f, 0.5f/g_texSize.y  );
    Out.tex2 = float2( 0.0f, 1.0f/g_texSize.y  );

    return Out;
}
/*!
 * @brief	ブラーのピクセルシェーダー。
 */
float4 PSMainBlur( VS_OUTPUT_BLUR In ) : COLOR0
{
	float4 Color;

	//5点ブラーを試してみる。
	Color = tex2D( TextureSampler, In.tex0 );
	Color += tex2D( TextureSampler, In.tex0 + In.tex1 );
	Color += tex2D( TextureSampler, In.tex0 - In.tex1 );
	Color += tex2D( TextureSampler, In.tex0 + In.tex2 );
	Color += tex2D( TextureSampler, In.tex0 - In.tex2 );
	Color /= 5.0f;

	return Color;
}


/// ガウシアンブラー

struct VS_OUTPUT_GBLUR{
	float4 pos	: POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};

/*!
 * @brief	Xガウシアンブラーの頂点シェーダー。
 */
VS_OUTPUT_GBLUR VSMainGBlurX( VS_INPUT In )
{
	VS_OUTPUT_GBLUR Out = (VS_OUTPUT_GBLUR)0;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	Out.tex0 = tex;
	Out.tex1 = tex + float2( - 2.0f/g_texSize.x, 0.0f  );
    Out.tex2 = tex + float2( - 4.0f/g_texSize.x, 0.0f  );
	Out.tex3 = tex + float2( - 6.0f/g_texSize.x, 0.0f  );
 	Out.tex4 = tex + float2( - 8.0f/g_texSize.x, 0.0f  );
    Out.tex5 = tex + float2( -10.0f/g_texSize.x, 0.0f  );
   	Out.tex6 = tex + float2( -12.0f/g_texSize.x, 0.0f  );
	Out.tex7 = tex + float2( -14.0f/g_texSize.x, 0.0f  );
    
    return Out;
}

/*!
 * @brief	Yガウシアンブラーの頂点シェーダー。
 */
VS_OUTPUT_GBLUR VSMainGBlurY( VS_INPUT In )
{
	VS_OUTPUT_GBLUR Out = (VS_OUTPUT_GBLUR)0;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	Out.tex0 = tex;
	Out.tex1 = tex + float2( 0.0f,- 2.0f/g_texSize.y  );
    Out.tex2 = tex + float2( 0.0f,- 4.0f/g_texSize.y  );
	Out.tex3 = tex + float2( 0.0f,- 6.0f/g_texSize.y  );
 	Out.tex4 = tex + float2( 0.0f,- 8.0f/g_texSize.y  );
    Out.tex5 = tex + float2( 0.0f,-10.0f/g_texSize.y  );
   	Out.tex6 = tex + float2( 0.0f,-12.0f/g_texSize.y  );
	Out.tex7 = tex + float2( 0.0f,-14.0f/g_texSize.y  );
    return Out;

}
/*!
 * @brief	ガウシアンブラーのピクセルシェーダー。
 */
float4 PSMainGBlur( VS_OUTPUT_GBLUR In, uniform int numWeight ) : COLOR0
{
	float4 Color;
	Color  = g_weight[0] * tex2D( TextureSampler, In.tex0 );
	Color += g_weight[1] * (tex2D( TextureSampler, In.tex1 ) + tex2D( TextureSampler, In.tex7 + g_offset ));
	Color += g_weight[2] * (tex2D( TextureSampler, In.tex2 ) + tex2D( TextureSampler, In.tex6 + g_offset ));
	Color += g_weight[3] * (tex2D( TextureSampler, In.tex3 ) + tex2D( TextureSampler, In.tex5 + g_offset ));
	Color += g_weight[4] * (tex2D( TextureSampler, In.tex4 ) + tex2D( TextureSampler, In.tex4 + g_offset ));
	Color += g_weight[5] * (tex2D( TextureSampler, In.tex5 ) + tex2D( TextureSampler, In.tex3 + g_offset ));
	Color += g_weight[6] * (tex2D( TextureSampler, In.tex6 ) + tex2D( TextureSampler, In.tex2 + g_offset ));
	Color += g_weight[7] * (tex2D( TextureSampler, In.tex7 ) + tex2D( TextureSampler, In.tex1 + g_offset ));
	return Color;
}


technique TransformedPrim
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}
/*!
 * @brief	横ブラー。
 */
technique TransformedPrimBlurX
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainBlurX();
		PixelShader		= compile ps_3_0 PSMainBlur();
	}
}

/*!
 * @brief	縦ブラー。
 */
technique TransformedPrimBlurY
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainBlurY();
		PixelShader		= compile ps_3_0 PSMainBlur();
	}
}

/*!
 * @brief	横ガウシアンブラー。ウェイト8
 */
technique TransformedPrimGBlurX_8
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurX();
		PixelShader		= compile ps_3_0 PSMainGBlur(8);
	}
}

/*!
 * @brief	縦ガウシアンブラー。ウェイト8
 */
technique TransformedPrimGBlurY_8
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurY();
		PixelShader		= compile ps_3_0 PSMainGBlur(8);
	}
}

/*!
 * @brief	横ガウシアンブラー。ウェイト6
 */
technique TransformedPrimGBlurX_6
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurX();
		PixelShader		= compile ps_3_0 PSMainGBlur(6);
	}
}

/*!
 * @brief	縦ガウシアンブラー。ウェイト8
 */
technique TransformedPrimGBlurY_6
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurY();
		PixelShader		= compile ps_3_0 PSMainGBlur(6);
	}
}

/*!
 * @brief	横ガウシアンブラー。ウェイト4
 */
technique TransformedPrimGBlurX_4
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurX();
		PixelShader		= compile ps_3_0 PSMainGBlur(4);
	}
}

/*!
 * @brief	縦ガウシアンブラー。ウェイト4
 */
technique TransformedPrimGBlurY_4
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurY();
		PixelShader		= compile ps_3_0 PSMainGBlur(4);
	}
}

/*!
 * @brief	横ガウシアンブラー。ウェイト2
 */
technique TransformedPrimGBlurX_2
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurX();
		PixelShader		= compile ps_3_0 PSMainGBlur(2);
	}
}

/*!
 * @brief	縦ガウシアンブラー。ウェイト2
 */
technique TransformedPrimGBlurY_2
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMainGBlurY();
		PixelShader		= compile ps_3_0 PSMainGBlur(2);
	}
}

