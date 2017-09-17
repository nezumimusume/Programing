/*!
 * @brief	モデル関係の構造体ヘッダ。
 */
 
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float2 TexCoord : TEXCOORD0;
    float4 Color    : COLOR;
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord	: TEXCOORD0;
    float3 Tangent	: TANGENT;
    uint4  Indices  : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 Pos			: TEXCOORD1;		//ワールド座標系での頂点座標。
	float3 posInView	: TEXCOORD2;		//カメラ空間での座標。
	float4 posInProj	: TEXCOORD3;		//正規化座標系での座標。
};

/*!
 * @brief	ディレクションライト。
 */
struct SDirectionLight{
	float3	direction;		//!<ライトの方向。
	float3	color;			//!<ライトのカラー。
};

//ポイントライト。
struct SPointLight {
	float3	position;		//位置。
	float3	positionInView;	//カメラ座標系でのポイントライトの位置。
	float3	color;			//カラー。
	float4  attn;			//減衰定数。(xを小さくするとライトの明るさが増す、yとzが大きくなるとライトが遠くまで届くようになる。)
};
