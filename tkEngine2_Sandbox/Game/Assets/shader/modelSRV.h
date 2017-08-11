/*!
 * @brief	モデルのSRV。
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//タイルに含まれるポイントライトのリスト。
StructuredBuffer<uint> pointLightListInTile : register(t102);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t103);


Texture2D<float4> Texture : register(t0);

sampler Sampler : register(s0);

