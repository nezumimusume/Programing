/*!
 * @brief	モデルのSRV。
 */

/*!
 * @brief	ディレクションライト。
 */
struct SDirectionLight{
	float3	direction;		//!<ライトの方向。
	float3	color;			//!<ライトのカラー。
};
StructuredBuffer<SDirectionLight> directionLight : register(t100);

Texture2D<float4> Texture : register(t0);

sampler Sampler : register(s0);

