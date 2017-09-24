/*!
 * @brief	モデルシェーダー。
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"


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
	float4x4 skinning = 0;
	float4 pos = 0.0f;
	
/*	[unroll]
    for (int i = 0; i < 4; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
    }*/
    skinning += boneMatrix[In.Indices[0]] * In.Weights[0];
    skinning += boneMatrix[In.Indices[1]] * In.Weights[1];
    skinning += boneMatrix[In.Indices[2]] * In.Weights[2];
    skinning += boneMatrix[In.Indices[3]] * In.Weights[3];
    
	pos.xyz = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	pos.w = 1.0f;
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	if(isZPrepass){
		//ZPrepass?
		return In.posInProj.z / In.posInProj.w;
	}
	if(isDrawShadowMap){
		//ShadowMap?
		//たぶんVSMはやらないので、普通にZ値を返しておこう。
		return In.posInProj.z / In.posInProj.w;
	}
	float3 lig = 0.0f;
	//視点までのベクトルを求める。
	float3 toEye = normalize(eyePos - In.Pos);
	//従ベクトルを計算する。
	float3 biNormal = normalize(cross(In.Normal, In.Tangent));
	//アルベド。
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	float3 normal = In.Normal;
	
	if(hasNormalMap){
		//法線マップがある。
		float3 binSpaceNormal = normalMap.Sample(Sampler, In.TexCoord).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = In.Tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + In.Normal * binSpaceNormal.z; 
	}
	
	float specPow = 0.0f;
	float roughness = 1.0f;
	if(hasSpecularMap){
		float4 t = specularMap.Sample(Sampler, In.TexCoord);
		specPow = t.x;
		roughness = 1.0f - t.w;
	}
	
	float3 toEyeDir = normalize( toEye - In.Pos );
	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	int shadow = 0;
	//ちょっと適当。
	if(isShadowReceiver){
		//影を落とす。
		for(int i = 0; i < numShadowMap; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(In.Pos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z, 1.0f);
			
			//uv座標に変換。
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float2 shadow_val = 1.0f;
			if(shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f){
				
				//@todo テクスチャ配列に変更する。
				if(i == 0){
					shadow_val = shadowMap_0.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 1){
					shadow_val = shadowMap_1.Sample(Sampler, shadowMapUV ).r;
				}else if(i == 2){
					shadow_val = shadowMap_2.Sample(Sampler, shadowMapUV ).r;
				}
				if( depth > shadow_val.r + 0.006f ){
					shadow = 1;
				}
			}
		}
	}
	
	//ディレクションライト
	float3 finalColor = 0.0f;
	if(shadow == 0){
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
	finalColor += albedo * ambientLight;
	
    return float4(finalColor, 1.0f); 

}

