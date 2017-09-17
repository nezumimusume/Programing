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
#if 0 //PBR
	float4 diffuseColor = float4(Texture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//従ベクトルと接ベクトルを求める。<-多くの場合で事前計算済みのデータとして、頂点データに埋め込まれているから計算しなくてよい。
//	float3 lig = max(0.0f, -dot( In.Normal, diffuseLightDir )) * diffuseLightColor;
	float3 biNormal;
	float3 tangentNormal;
	if(In.Normal.x < 0.001f && In.Normal.z < 0.001f){
		//法線がほぼ真上
		tangentNormal = normalize(cross(In.Normal, float3( 1.0f, 0.0f, 0.0f)));
	}else{
		tangentNormal = normalize(cross(In.Normal, float3( 0.0f, 1.0f, 0.0f)));
	}
	float3 toEye = normalize(eyePos - In.Pos);
	biNormal = normalize(cross(In.Normal, tangentNormal));
	float3 color = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		float3 diffuseLightColor = 0.0f;
		float3 lightDir = directionLight[i].direction;
		diffuseLightColor += BRDF(-lightDir, toEye, In.Normal, tangentNormal, biNormal, diffuseColor.xyz);
		diffuseLightColor *= dot( In.Normal, -lightDir );
		color += diffuseLightColor;
	}
	color += diffuseColor * float3(0.1f, 0.1f, 0.1f);
    return float4( color, 1.0f ); 
#else	//not pbr
	
	
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
	
	//ディレクションライト
	float3 finalColor = CalcDirectionLight(
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
#endif
}

