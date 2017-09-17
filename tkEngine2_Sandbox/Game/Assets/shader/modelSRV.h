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
sampler Sampler : register(s0);

