/*!
 * @brief	モデルシェーダー。
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"


/*!
 *@brief	影を計算。
 */
int CalcShadow( float3 worldPos )
{
	int shadow = 0;
	//ちょっと適当。
	if(isShadowReceiver){
		//影を落とす。
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv座標に変換。
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float2 shadow_val = 1.0f;
			if(shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f){
				if(i == 0){
					shadow_val = shadowMap_0.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 1){
					shadow_val = shadowMap_1.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 2){
					shadow_val = shadowMap_2.Sample(Sampler, shadowMapUV ).r;
				}
				if( depth > shadow_val.r + 0.006f ){
					shadow = 1;
					break;
				}
			}
		}
	}
	return shadow;
}
/*!
 *@brief	法線を計算。
 */
float3 CalcNormal( float3 normal, float3 biNormal, float3 tangent, float2 uv )
{
	if(hasNormalMap){
		//法線マップがある。
		float3 binSpaceNormal = normalMap.Sample(Sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z; 
	}
	return normal;
}
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
    return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	//スキン行列を計算。
	float4x4 skinning = CalcSkinMatrix(In);
	//ワールド座標、法線、接ベクトルを計算。
	float4 pos = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}

/*!
 *@brief	Z値を書き込むためだけの描画パスで使用される頂点シェーダー。
 *			スキンなしモデル用
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
PSInput_RenderToDepth VSMain_RenderDepth(VSInputNmTxVcTangent In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}

/*!
 *@brief	Z値を書き込むためだけの描画パスで使用される頂点シェーダー。
 *			スキンありモデル用。
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
PSInput_RenderToDepth VSMainSkin_RenderDepth(VSInputNmTxWeights In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	//スキン行列を計算。
	float4x4 skinning = CalcSkinMatrix(In);
	//ワールド座標、法線、接ベクトルを計算。
	float4 pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
	
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float3 lig = 0.0f;
	//視点までのベクトルを求める。
	float3 toEye = normalize(eyePos - In.Pos);
	//従ベクトルを計算する。
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//アルベド。
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//法線を計算。
	float3 normal = CalcNormal( In.Normal, biNormal, In.Tangent, In.TexCoord);
		
	float specPow = 0.0f;
	float roughness = 1.0f;
	if(hasSpecularMap){
		float4 t = specularMap.Sample(Sampler, In.TexCoord);
		specPow = t.x;
		roughness = 1.0f - t.w;
		roughness *= 0.8f;	//@todo マテリアルパラメータにすべきだな。
	}
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if(toEyeLen > 0.001f){
		toEyeDir = toEye / toEyeLen;
	}

	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//影を計算。
	int shadow = CalcShadow(In.Pos);	
	//ディレクションライト
	float3 finalColor = 0.0f;
	if(shadow == 0){
		//影が落ちている場合はディレクションライトはカットする。
		finalColor = CalcDirectionLight(
			albedo,
			In.Pos, 
			normal, 
			In.Tangent,
			biNormal,
			toEyeDir,
			toEyeReflection, 
			roughness,
			specPow
		);
	}
	
	//ポイントライトを計算。
	finalColor += CalcPointLight(
		albedo,
		In.Pos, 
		In.posInProj, 
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		roughness,
		specPow
	);
    
	//アンビエントライト。
	finalColor += CalcAmbientLight(
		albedo,
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		roughness,
		specPow
	);
	
	// brightness
	float brightness = 1.0f;
    finalColor *= brightness;
/*
    // exposure
    float exposure = 1.0f;
    finalColor *= pow( 2.0, exposure );
  */  
    float gamma = 2.2f;
    finalColor = max( 0.0f, pow( finalColor, 1.0 / gamma ) );
    if(isnan(finalColor.x) || isnan(finalColor.y) || isnan(finalColor.z)){
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
    return float4(finalColor, 1.0f); 

}


/*!
 *@brief	Z値を書き込むためだけの描画パスで使用されるピクセルシェーダー。
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
float4 PSMain_RenderDepth( PSInput_RenderToDepth In ) : SV_Target0
{
	return In.posInProj.z / In.posInProj.w;
}
