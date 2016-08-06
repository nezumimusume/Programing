/*!
 *@brief	簡単なディフューズライティングのシェーダー。
 */


float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix;			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。
float4x4 g_rotationMatrix;		//回転行列。法線を回転させるために必要になる。ライティングするなら必須。

#define DIFFUSE_LIGHT_NUM	4		//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;								//環境光。

texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3	normal	: NORMAL0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: TEXCOORD1;
};

struct VS_INPUT_INSTANCING{
	VS_INPUT base;
	float4 mWorld1	: TEXCOORD1;		//ワールド行列の1行目
	float4 mWorld2	: TEXCOORD2;		//ワールド行列の2行目
	float4 mWorld3	: TEXCOORD3;		//ワールド行列の3行目
	float4 mWorld4	: TEXCOORD4;		//ワールド行列の4行目
};
/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	float4 pos; 
	pos = mul( In.pos, g_worldMatrix );		//モデルのローカル空間からワールド空間に変換。
	pos = mul( pos, g_viewMatrix );			//ワールド空間からビュー空間に変換。
	pos = mul( pos, g_projectionMatrix );	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.color = In.color;
	Out.uv = In.uv;
	Out.normal = mul( In.normal, g_rotationMatrix );	//法線を回す。
	return Out;
}
/*!
 * @brief	インスタンシング用の頂点シェーダー。
 */
VS_OUTPUT VSMainInstancing( VS_INPUT_INSTANCING In )
{
	VS_OUTPUT Out;
	float4 pos; 
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	
	pos = mul( In.base.pos, worldMat );			//モデルのローカル空間からワールド空間に変換。
	pos = mul( pos, g_viewMatrix );			//ワールド空間からビュー空間に変換。
	pos = mul( pos, g_projectionMatrix );	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	Out.color = In.base.color;
	Out.uv = In.base.uv;
	Out.normal = mul( In.base.normal, g_rotationMatrix );	//法線を回す。
	return Out;
}
/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	//ライトを計算。
	float4 lig = 0.0f;
	lig.xyz = g_ambientLight;
	float4 color = tex2D( g_diffuseTextureSampler, In.uv );
	color.xyz *= lig;
	return color;
}
//普通のスキンモデル描画用のテクニック。
technique SkinModel
{
	
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}
//インスタンシング描画用のテクニック。
technique SkinModelInstancing
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMainInstancing();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}