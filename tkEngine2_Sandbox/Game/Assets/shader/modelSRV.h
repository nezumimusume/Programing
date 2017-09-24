/*!
 * @brief	モデルのSRV。
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//タイルに含まれるポイントライトのリスト。
StructuredBuffer<uint> pointLightListInTile : register(t102);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t103);



Texture2D<float4> albedoTexture : register(t0);	//アルベドテクスチャ。
Texture2D<float4> normalMap : register(t1);		//法線マップ。
Texture2D<float4> specularMap : register(t2);	//スペキュラマップ。

//@todo テクスチャ配列に変更する。
Texture2D<float4> shadowMap_0 : register(t3);	//
Texture2D<float4> shadowMap_1 : register(t4);	//
Texture2D<float4> shadowMap_2 : register(t5);	//

sampler Sampler : register(s0);

