/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */
#include "Common.h" 
#include "LightingFunction.h"
#include "ShadowFunction.h"


//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。
float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4	g_rotationMatrix;		//!<回転行列。
float4x4	g_viewMatrixRotInv;		//!<カメラの回転行列の逆行列。
float4x4	g_mViewProjLastFrame;	//!<1フレーム前のビュープロジェクション行列。
float4		g_fogParam;				//フォグのパラメータ。xにフォグが掛かり始める深度。yにフォグが完全にかかる深度。zはフォグを計算するかどうかのフラグ。

float2		g_farNear;	//遠平面と近平面。xに遠平面、yに近平面。

const int AtomosphereFuncNone = 0;						//大気錯乱シミュレーションなし。
const int AtomosphereFuncObjectFromAtomosphere = 1;		//オブジェクトを大気圏から見た場合の大気錯乱シミュレーション。
const int AtomosphereFuncSkyFromAtomosphere = 2;		//空を大気圏から見た場合の大気錯乱シミュレーション。
int4 g_flags;				//xに法線マップ、yはシャドウレシーバー、zはリムライト、wはスペキュラマップ。
int4 g_flags2;				//xに速度マップへの書き込み、yは大気錯乱シミュレーション種類。

texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

//法線マップ
texture g_normalTexture;		//法線マップ。
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

//空用のキューブマップ。
texture g_skyCubeMap;
samplerCUBE g_skyCubeMapSampler = 
sampler_state
{
    Texture = <g_skyCubeMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};


/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3	Tangent			: TANGENT;		//接ベクトル
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	インスタンシング描画用の入力頂点。
 */
struct VS_INPUT_INSTANCING
{
	VS_INPUT	base;
	float4 mWorld1	: TEXCOORD1;		//ワールド行列の1行目
	float4 mWorld2	: TEXCOORD2;		//ワールド行列の2行目
	float4 mWorld3	: TEXCOORD3;		//ワールド行列の3行目
	float4 mWorld4	: TEXCOORD4;		//ワールド行列の4行目
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     		: POSITION;
    float3  Normal			: NORMAL;
    float2  Tex0   			: TEXCOORD0;
    float3	Tangent			: TEXCOORD1;	//接ベクトル
    float4  worldPos_depth	: TEXCOORD2;	//xyzにワールド座標。wには射影空間でのdepthが格納される。
    float4  velocity		: TEXCOORD3;	//速度。
    float4  screenPos		: TEXCOORD4;
    float4	mieColor		: TEXCOORD5;	//ミー錯乱色。
    float4	rayColor		: TEXCOORD6;	//レイリー錯乱色。
    float3  posToCameraDir	: TEXCOORD7;
};

/*!
 * @brief	シャドウマップ描き込み時の出力頂点。
 */
struct VS_OUTPUT_RENDER_SHADOW_MAP
{
	float4  Pos     : POSITION;
	float4	depth	: TEXCOORD;
};

/*!
 * @brief	ピクセルシェーダーからの出力。
 */
struct PSOutput{
	float4	color		: COLOR0;		//レンダリングターゲット0に書き込み。
	float4	depth		: COLOR1;		//レンダリングターゲット1に書き込み。
	float4  velocity 	: COLOR2;		//レンダリングターゲット2に書き込み。
};

/*!
 * @brief	大気錯乱パラメータ。
 */
struct SAtmosphericScatteringParam{
	float3 v3LightPos;
	float3 v3LightDirection;
	float3 v3InvWavelength;	// 1 / pow(wavelength, 4) for the red, green, and blue channels
	float fCameraHeight;		// The camera's current height
	float fCameraHeight2;		// fCameraHeight^2
	float fOuterRadius;		// The outer (atmosphere) radius
	float fOuterRadius2;		// fOuterRadius^2
	float fInnerRadius;		// The inner (planetary) radius
	float fInnerRadius2;		// fInnerRadius^2
	float fKrESun;				// Kr * ESun
	float fKmESun;				// Km * ESun
	float fKr4PI;				// Kr * 4 * PI
	float fKm4PI;				// Km * 4 * PI
	float fScale;				// 1 / (fOuterRadius - fInnerRadius)
	float fScaleOverScaleDepth;// fScale / fScaleDepth
	float g;
	float g2;
};

SAtmosphericScatteringParam g_atmosParam;

// The scale depth (the altitude at which the average atmospheric density is found)
const float fScaleDepth = 0.25;
const float fInvScaleDepth = 4;

const int nSamples = 2;
const float fSamples = 2.0f;



// The scale equation calculated by Vernier's Graphical Analysis
float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}
// Returns the near intersection point of a line and a sphere
float getNearIntersection(float3 v3Pos, float3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}
// Calculates the Mie phase function
float getMiePhase(float fCos, float fCos2, float g, float g2)
{
	return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2)
{
	//return 1.0;
	return 0.75 + 0.75*fCos2;
}

/*!
 * @brief	大気圏内から空を見た時のミー錯乱とレイリー錯乱を計算。
 */
void CalcMieAndRayleighColorsSkyFromAtomosphere( out float4 mieColor, out float4 rayColor, out float3 posToCameraDir, float3 worldPos )
{
//	worldPos.y += g_atmosParam.fInnerRadius;
	float3 cameraPos = g_cameraPos.xyz;
	cameraPos *= 0.001f;
	cameraPos.y += g_atmosParam.fInnerRadius;
	mieColor = 0.0f;
	rayColor = 0.0f;
	worldPos *= 0.001f;
	worldPos.y += g_atmosParam.fInnerRadius;
	// Get the ray from the camera to the vertex and its length (which is the far point of the ray passing through the atmosphere)
	float3 v3Ray = worldPos - cameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	
	// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
//	float fNear = getNearIntersection(g_cameraPos.xyz, v3Ray, g_atmosParam.fCameraHeight2, g_atmosParam.fOuterRadius2);
	
	float3 v3Start = cameraPos;
	float fHeight = length(v3Start);
	float fDepth = exp(g_atmosParam.fScaleOverScaleDepth * (g_atmosParam.fInnerRadius - g_atmosParam.fCameraHeight));
	float fStartAngle = dot(v3Ray, v3Start) / fHeight;
	float fStartOffset = fDepth*scale(fStartAngle);
	
	// Initialize the scattering loop variables
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * g_atmosParam.fScale;
	float3 v3SampleRay = v3Ray * fSampleLength;
	float3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
	
	// Now loop through the sample rays
	float3 v3FrontColor = float3(0.0, 0.0, 0.0);
	for(int i=0; i<nSamples; i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(g_atmosParam.fScaleOverScaleDepth * (g_atmosParam.fInnerRadius - fHeight));
		float fLightAngle = dot(g_atmosParam.v3LightDirection, v3SamplePoint) / fHeight;
		float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
		float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
		float3 v3Attenuate = exp(-fScatter * (g_atmosParam.v3InvWavelength * g_atmosParam.fKr4PI + g_atmosParam.fKm4PI));
		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	
	// Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader

	mieColor.rgb =  v3FrontColor * g_atmosParam.fKmESun;
	rayColor.rgb = v3FrontColor * (g_atmosParam.v3InvWavelength * g_atmosParam.fKrESun);
	posToCameraDir = cameraPos - worldPos;
}
/*!
 * @brief	大気圏内からオブジェクトを見た時のミー錯乱とレイリー錯乱を計算。
 */
void CalcMieAndRayleighColorsObjectFromAtomosphere( out float4 mieColor, out float4 rayColor, out float3 posToCameraDir, float3 worldPos )
{
//	worldPos.y += g_atmosParam.fInnerRadius;
	float3 cameraPos = g_cameraPos.xyz;
	cameraPos *= 0.001f; //単位をmからkmに変更。
	cameraPos.y += g_atmosParam.fInnerRadius;
	mieColor = 0.0f;
	rayColor = 0.0f;
	worldPos *= 0.001f; //単位をmからkmに変更。
	worldPos.y += g_atmosParam.fInnerRadius;
	worldPos.y = min(worldPos.y, cameraPos.y);
	// Get the ray from the camera to the vertex and its length (which is the far point of the ray passing through the atmosphere)
	float3 v3Ray = worldPos - cameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	
	// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
//	float fNear = getNearIntersection(g_cameraPos.xyz, v3Ray, g_atmosParam.fCameraHeight2, g_atmosParam.fOuterRadius2);
	
	float3 v3Start = cameraPos;
	float fDepth = exp((g_atmosParam.fInnerRadius - g_atmosParam.fCameraHeight) / fScaleDepth);
	float fCameraAngle = dot(-v3Ray, worldPos) / length(worldPos);
	float fLightAngle = dot(g_atmosParam.v3LightDirection, worldPos) / length(worldPos);
	float fCameraScale = scale(fCameraAngle);
	float fLightScale = scale(fLightAngle);
	float fCameraOffset = fDepth*fCameraScale;
	float fTemp = (fLightScale + fCameraScale);

	// Initialize the scattering loop variables
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * g_atmosParam.fScale;
	float3 v3SampleRay = v3Ray * fSampleLength;
	float3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
	
	// Now loop through the sample rays
	float3 v3FrontColor = float3(0.0, 0.0, 0.0);
	float3 v3Attenuate;
	for(int i=0; i<nSamples; i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(g_atmosParam.fScaleOverScaleDepth * (g_atmosParam.fInnerRadius - fHeight));
		float fScatter = fDepth*fTemp - fCameraOffset;
		v3Attenuate = exp(-fScatter * (g_atmosParam.v3InvWavelength * g_atmosParam.fKr4PI + g_atmosParam.fKm4PI));
		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	
	// Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader

	mieColor.rgb =  v3Attenuate;
	rayColor.rgb = v3FrontColor * (g_atmosParam.v3InvWavelength * g_atmosParam.fKrESun + g_atmosParam.fKmESun);
	posToCameraDir = cameraPos - worldPos;
}
/*!
 *@brief	大気錯乱シミュレーション。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */

void CalcMieAndRayleighColors(out float4 mieColor, out float4 rayColor, out float3 posToCameraDir, float3 worldPos)
{
	if(g_flags2.y == AtomosphereFuncObjectFromAtomosphere){
		CalcMieAndRayleighColorsObjectFromAtomosphere(mieColor, rayColor, posToCameraDir, worldPos);
	}else if(g_flags2.y == AtomosphereFuncSkyFromAtomosphere){
		CalcMieAndRayleighColorsSkyFromAtomosphere(mieColor, rayColor, posToCameraDir, worldPos);
	}else{
		mieColor = 0.0f;
		rayColor = 0.0f;
	}
}

/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        if(calcNormal){
	        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    	    Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    	}
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
	if(calcNormal){
	    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    	Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    }
}
/*!
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal )
{
	Normal = 0.0f;
	Tangent = 0.0f;
	Pos = mul(In.Pos, g_worldMatrix );
	if(calcNormal){
		Normal = mul(In.Normal, g_worldMatrix );
		Tangent = mul(In.Tangent, g_worldMatrix );
	}
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent, true );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent, true );
	}
	o.worldPos_depth.xyz = Pos.xyz;


    o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
    o.worldPos_depth.w = o.Pos.w;
    o.Normal = normalize(Normal);
    o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;
    o.velocity = mul(float4(Pos.xyz, 1.0f), g_mViewProjLastFrame);
    o.screenPos = o.Pos;
    CalcMieAndRayleighColors( o.mieColor, o.rayColor, o.posToCameraDir, o.worldPos_depth.xyz );
	return o;
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMainInstancing( VS_INPUT_INSTANCING In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In.base, Pos, Normal, Tangent, true );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In.base, Pos, Normal, Tangent, true );
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat );	//ワールド行列をかける。

	o.worldPos_depth.xyz = Pos.xyz;
    o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
    o.worldPos_depth.w = o.Pos.w;
    o.Normal = mul(normalize(Normal), worldMat);
    o.Tex0 = In.base.Tex0;
   	o.velocity = mul(float4(Pos.xyz, 1.0f), g_mViewProjLastFrame);
   	o.screenPos = o.Pos;
   	CalcMieAndRayleighColors( o.mieColor, o.rayColor, o.posToCameraDir, o.worldPos_depth.xyz );
   	
	return o;
}

/*!
 * @brief	ピクセルシェーダー。
 */
PSOutput PSMain( VS_OUTPUT In )
{
	float4 color = 0.0f;
	float4 diffuseColor = tex2D(g_diffuseTextureSampler, In.Tex0);
	color = diffuseColor;
	float3 normal = normalize(In.Normal);
	if(g_flags.x){
		//法線マップあり。
		float3 tangent = normalize(In.Tangent);
		float3 binSpaceNormal = tex2D( g_normalMapSampler, In.Tex0);
		float4x4 tangentSpaceMatrix;
		float3 biNormal = normalize( cross( tangent, normal) );
		tangentSpaceMatrix[0] = float4( tangent, 0.0f);
		tangentSpaceMatrix[1] = float4( biNormal, 0.0f);
		tangentSpaceMatrix[2] = float4( normal, 0.0f);
		tangentSpaceMatrix[3] = float4( 0.0f, 0.0f, 0.0f, 1.0f );
		//-1.0～1.0の範囲にマッピングする。
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = tangentSpaceMatrix[0] * binSpaceNormal.x + tangentSpaceMatrix[1] * binSpaceNormal.y + tangentSpaceMatrix[2] * binSpaceNormal.z; 
		
	}
	
	float4 lig = DiffuseLight(normal);
	if(g_flags.z){
		//リムライト。
		lig.xyz += CalcLimLight(normal, g_light.limLightDir, g_light.limLightColor.xyz);
	}
	if(g_flags.w){
		//スペキュラライト。
		lig.xyz += SpecLight(normal, In.worldPos_depth.xyz, In.Tex0);
	}
	
	if(g_flags.y){
		//影
		lig *= CalcShadow(In.worldPos_depth.xyz);
	
	}
	//自己発光色
	lig.xyz += g_light.emission;
	
	color *= lig;

	//大気錯乱
	if(g_flags2.y == AtomosphereFuncObjectFromAtomosphere)
	{
		color = In.rayColor + color * In.mieColor;
	}
	
	//ポイントライト。
	color.xyz += diffuseColor.xyz * PointLight(normal, In.worldPos_depth.xyz, g_flags.z);
	
	//アンビエントライトを加算。
	color.xyz += diffuseColor.xyz * g_light.ambient.xyz;	
	
	if(g_fogParam.z > 1.9f){
		//高さフォグ
		float h = max(In.worldPos_depth.y - g_fogParam.y, 0.0f);
		float t = min(h / g_fogParam.x, 1.0f);
		color.xyz = lerp(float3(0.75f, 0.75f, 0.95f), color.xyz, t);
	}else if(g_fogParam.z > 0.0f){
		//距離フォグ
		float z = length(In.worldPos_depth.xyz - g_cameraPos);
		z = max(z - g_fogParam.x, 0.0f);
		float t = min( z / g_fogParam.y, 1.0f);
		color.xyz = lerp(color.xyz, float3(0.75f, 0.75f, 0.95f), t);
	}
	
	PSOutput psOut = (PSOutput)0;
	psOut.color = color;
	psOut.depth = In.worldPos_depth.w;
	if(g_flags2.x){
		psOut.velocity.xy = In.velocity.xy / In.velocity.w-In.screenPos.xy / In.screenPos.w;
		psOut.velocity.xy *= 0.5f;
		psOut.velocity.xy += 0.5f;
		psOut.velocity.zw = 0.0f;
	}else{
		//速度なし。
		psOut.velocity = 0.5f;
	}
	return psOut;
}
/*!
 * @brief	空描画用の頂点シェーダー。
 */
VS_OUTPUT VSSkyMain(VS_INPUT In)
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	//空にスキンはない。
	//法線の計算もいらない。
	CalcWorldPosAndNormal( In, Pos, Normal, Tangent, false);
	o.worldPos_depth.xyz = Pos.xyz;
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
    o.worldPos_depth.w = o.Pos.w;
    o.Tex0 = In.Tex0;
    o.Normal = In.Normal;
    o.velocity = mul(float4(Pos.xyz, 1.0f), g_mViewProjLastFrame);
    o.screenPos = o.Pos;
    CalcMieAndRayleighColors( o.mieColor, o.rayColor, o.posToCameraDir, o.worldPos_depth.xyz );
	return o;
}
/*!
 * @brief	空描画用のピクセルシェーダー。
 */
PSOutput PSSkyMain(VS_OUTPUT In){
	float4 diffuseColor = texCUBE(g_skyCubeMapSampler, In.Normal * -1.0f);
	float4 color = 0;

	color = In.rayColor + 0.25f * In.mieColor;
	float t = pow( 1.0f - min(1.0f, length(color)), 10.0f );
	color += diffuseColor * t ;
	
	PSOutput psOut = (PSOutput)0;
	psOut.color = color;
	psOut.depth = In.worldPos_depth.w;
	if(g_flags2.x){
		psOut.velocity.xy = In.velocity.xy / In.velocity.w-In.screenPos.xy / In.screenPos.w;
		psOut.velocity.xy *= 0.5f;
		psOut.velocity.xy += 0.5f;
		psOut.velocity.zw = 0.0f;
	}else{
		//速度なし。
		psOut.velocity = 0.5f;
	}
	return psOut;
}
/*!
 * @brief	シャドウマップ描き込み時の頂点シェーダー。
 */
VS_OUTPUT_RENDER_SHADOW_MAP VSMainRenderShadowMap( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT_RENDER_SHADOW_MAP o = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent, false );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent, false );
	}
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	o.depth = o.Pos;
	return o;
}
/*!
 * @brief	シャドウマップ書き込み時の頂点シェーダー(インスタンシング版)
 */
VS_OUTPUT_RENDER_SHADOW_MAP VSMainInstancingRenderShadowMap(VS_INPUT_INSTANCING In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP o = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In.base, Pos, Normal, Tangent, false );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal( In.base, Pos, Normal, Tangent, false );
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat );	//ワールド行列をかける。
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	o.depth = o.Pos;
	return o;
}
/*!
 * @brief	シャドウマップ描き込み時のピクセルシェーダー。
 */
float4 PSMainRenderShadowMap( VS_OUTPUT_RENDER_SHADOW_MAP In ) : COLOR
{

	float z = In.depth.z/In.depth.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z+0.25f*(dx*dx+dy*dy), 0.0f, 1.0f);
}

/*!
 *@brief	スキンありモデル用のテクニック。
 */
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	スキンなしモデル用のテクニック。
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}
/*!
 *@brief	スキンありモデルのインスタンシング描画用のテクニック。
 */
technique SkinModelInstancing
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMainInstancing(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	スキンなしモデルのインスタンシング描画用のテクニック。
 */
technique NoSkinModelInstancing
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancing(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

/*!
 * @brief	スキンありモデル用のシャドウマップ描き込みテクニック。
 */
technique SkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(true);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

/*!
 * @brief	スキンなしモデル用のシャドウマップ描き込みテクニック。
 */
technique NoSkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(false);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}
technique SkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(true);
        PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}
technique NoSkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(false);
        PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}
/*!
 * @brief	空描画用のテクニック。
 */
technique Sky{
	pass p0
	{
		VertexShader =  compile vs_3_0 VSSkyMain();
		PixelShader = compile ps_3_0 PSSkyMain();
	}
}