/*!
 * @brief	ライト計算関係。
 */


#define TILE_WIDTH	16		//タイルの幅。

/*!
 * @brief	ポイントライトを計算。
 *@param[in]	posInWorld		ワールド座標系での座標。
 *@param[in]	posInProj		射影空間での座標。
 *@param[in]	normal			法線。
 *@param[in]	tangent			接ベクトル。
 *@param[in]	biNormal		従ベクトル。
 *@param[in]	toEye			視点までのベクトル。
 */
float3 CalcPointLight(
	float3 posInWorld, 
	float4 posInProj, 
	float3 normal,
	float3 tangent,
	float3 biNormal,
	float3 toEye
)
{
	
	//スクリーンの左上を(0,0)、右下を(1,1)とする座標系に変換する。
	float2 screenPos = (posInProj.xy / posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
	//ビューポート座標系に変換する。
	float2 viewportPos = screenParam.zw * screenPos;
	//スクリーンをタイルで分割したときのセルのX座標を求める。
	uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
	//タイルインデックスを計算する。
	uint tileIndex = floor( viewportPos.x / TILE_WIDTH ) + floor( viewportPos.y / TILE_WIDTH ) * numCellX;
	
	//このピクセルが含まれるタイルのライトインデックスリストの開始位置を計算する。
	uint lightStart = tileIndex * numPointLight;
	//このピクセルが含まれるタイルのライトインデックスリストの終了位置を計算する。
	uint lightEnd = lightStart + numPointLight;
	
	float3 lig = 0.0f;
	for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++){
		uint lightIndex = pointLightListInTile[lightListIndex];
		if(lightIndex == 0xffffffff){
			//このタイルに含まれるポイントライトはもうない。
			break;
		}
		SPointLight light = pointLightList[lightIndex];
		float3 lightDir = posInWorld - light.position;
		float len = length(lightDir);
		lightDir = normalize(lightDir);	//正規化。
//		float3 pointLightColor = BRDF(-lightDir, toEye, normal, tangent, biNormal, light.color.xyz);
		float3 pointLightColor = saturate(-dot(normal, lightDir)) * light.color.xyz;

		//減衰を計算する。
		float	litRate = len / light.attn.x;
		float	attn = max(1.0 - litRate * litRate, 0.0);
		pointLightColor *= attn;

		lig += pointLightColor;
	}
	
	return lig;
}