/*!
 * @brief	ライト計算関係。
 */


#define TILE_WIDTH	16		//タイルの幅。

float3 CalcSpecular(float3 lightDir, float4 lightColor, float3 toEyeReflection, float specPow)
{
	return lightColor.xyz * pow(max(0.0f, dot(-lightDir,toEyeReflection)), 2 ) * lightColor.w * specPow;
}
/*!
 * @brief	ディレクションライトの影響を計算。
 *@param[in]	albedo			アルベド。
 *@param[in]	posInWorld		ワールド空間での座標。
 *@param[in]	normal			法線。
 *@param[in]	toEye			視点までのベクトル。
 *@param[in]	specPow			スペキュラ強度。
 */
float3 CalcDirectionLight(
	float4 albedo,
	float3 posInWorld, 
	float3 normal,
	 float3 tangent,
	float3 biNormal, 
	float3 toEyeDir, 
	float3 toEyeReflection, 
	float roughness,
	float specPow
)
{
	float3 spec = 0.0f;
	
	float3 lig = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		
		float3 lightDir = directionLight[i].direction;
		//拡散反射光を計算する。
		lig += albedo * max( 0.0f, dot( normal, -lightDir ) ) * directionLight[i].color;
		//スペキュラ。
		lig += BRDF(-lightDir, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow) * directionLight[i].color;
	}
	
	return lig;
}
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
	float4 albedo,
	float3 posInWorld, 
	float4 posInProj, 
	float3 normal,
	float3 tangent,
	float3 biNormal,
	float3 toEyeDir,
	float3 toEyeReflection, 
	float roughness,
	float specPow
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
		float3 pointLightColor = albedo * saturate(-dot(normal, lightDir)) * light.color.xyz;
		pointLightColor += BRDF(-lightDir, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow) * light.color.xyz;
		//減衰を計算する。
		float	litRate = len / light.attn.x;
		float	attn = max(1.0 - litRate * litRate, 0.0);
		pointLightColor *= attn;
		lig += pointLightColor;
	}
	
	return lig;
}