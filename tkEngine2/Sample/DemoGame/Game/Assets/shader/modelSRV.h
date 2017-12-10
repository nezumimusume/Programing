/*!
 * @brief	モデルのSRV。
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//タイルに含まれるポイントライトのリスト。
StructuredBuffer<uint> pointLightListInTile : register(t102);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t103);
//インスタンシング描画用
StructuredBuffer<float4x4> instanceMatrix : register(t104);


Texture2D<float4> albedoTexture : register(t0);	//アルベドテクスチャ。
Texture2D<float4> normalMap : register(t1);		//法線マップ。
Texture2D<float4> specularMap : register(t2);	//スペキュラマップ。

Texture2D<float4> shadowMap_0 : register(t3);	//シャドウマップ。
Texture2D<float4> shadowMap_1 : register(t4);	//シャドウマップ。
Texture2D<float4> shadowMap_2 : register(t5);	//シャドウマップ。
Texture2D<float4> silhouetteTexture : register(t6);	//シルエットテクスチャ。
Texture2D<float4> vsm_0 : register(t7);	//VSM_0。
Texture2D<float4> vsm_1 : register(t8);	//VSM_1。
Texture2D<float4> vsm_2 : register(t9);	//VSM_2。

sampler Sampler : register(s0);

