/*!
 * @brief	モデル用の定数バッファ。
 */
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLVP2;			//@todo 後で変更する。
	float4 screenParam;		// スクリーンパラメータ(near, far, screenWidth, screenHeight)
	int isZPrepass;			//Zプリパス？
	int isDrawShadowMap;	//シャドウマップに描画中？
	int isShadowReceiver;	//シャドウレシーバー？
};

/*!
 * @brief	ライト用の定数バッファ。
 */
cbuffer lightCb : register(b1)
{
	float3 eyePos 			: packoffset(c0);		//カメラの位置。
	int numDirectionLight 	: packoffset(c0.w);		//ディレクションライトの数。
	float3 ambientLight		: packoffset(c1);		//アンビエントライト。
	int numPointLight		: packoffset(c1.w);		//ポイントライトの数。
	
};

cbuffer MaterialParamCb : register(b2){
	int hasNormalMap;	//!<法線マップある？
	int hasSpecularMap;	//!<スペキュラマップある？
	float anisotropic;	//異方性反射
};

#define NUM_SHADOW_MAP 3
/*!
 * @brief	シャドウマップ用の定数バッファ。
 */
cbuffer ShadowCb : register( b3 ){
	float4x4 mLVP[NUM_SHADOW_MAP];		//!<ライトビュープロジェクション行列。
};