/*!
 * @brief	ライティング関係の関数集
 */

#define NUM_DIFFUSE_LIGHT	4					//ディフューズライトの数。

//スペキュラマップ
texture g_speculerMap;
sampler g_speculerMapSampler = 
sampler_state
{
	Texture = <g_speculerMap>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

struct SLight{
	float3	diffuseLightDir[NUM_DIFFUSE_LIGHT];		//ディフューズライトの向き。
	float4  diffuseLightColor[NUM_DIFFUSE_LIGHT];	//ディフューズライトのカラー。
	float3	limLightDir;							//リムライトの方向。
	float4	limLightColor;							//リムライトの色。
	float4  pointLightPosition;						//ポイントライトの座標。
	float4  pointLightColor;						//ポイントライトのカラー。
	float3  ambient;								//アンビエントライト。
	float3  emission;								//自己発光。
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


SLight	g_light;		//!<ライト
float4	g_cameraPos;	//!<カメラの座標。
float3	g_cameraDir;	//!<カメラ方向。
int4 g_flags2;				//xに速度マップへの書き込み、yは大気錯乱シミュレーション種類

const int AtomosphereFuncNone = 0;						//大気錯乱シミュレーションなし。
const int AtomosphereFuncObjectFromAtomosphere = 1;		//オブジェクトを大気圏から見た場合の大気錯乱シミュレーション。
const int AtomosphereFuncSkyFromAtomosphere = 2;		//空を大気圏から見た場合の大気錯乱シミュレーション。


/*!
 *@brief	ディフューズライトを計算。
 */	
float4 DiffuseLight( float3 normal )
{
	float4 color = 0.0f;
	color += max( 0, -dot(normal, g_light.diffuseLightDir[0])) * g_light.diffuseLightColor[0];
	color += max( 0, -dot(normal, g_light.diffuseLightDir[1])) * g_light.diffuseLightColor[1];
	color += max( 0, -dot(normal, g_light.diffuseLightDir[2])) * g_light.diffuseLightColor[2];
	color += max( 0, -dot(normal, g_light.diffuseLightDir[3])) * g_light.diffuseLightColor[3];
	
	if(g_flags2.y == AtomosphereFuncObjectFromAtomosphere)
	{
		//大気錯乱が設定されている場合は0番目のライトを太陽光とする。
		float t = max( 0.0f, dot(float3(0.0f, -1.0f, 0.0f ), g_light.diffuseLightDir[0]) );
		t *= 2.0f;
		t = min(1.0f, pow(t, 2.0f));
		color *= t;
	}
	color.a = 1.0f;
	return color;
}
/*!
 *@brief	リムライトを計算。
 */
float3 CalcLimLight( float3 normal, float3 lightDir, float3 limColor)
{
	float lim = 0.0f;
	float baselim = 1.0f - abs( dot(normal, g_cameraDir ) );
	lim += baselim * max( 0.0f, -dot(g_cameraDir, lightDir));
	lim = pow(lim, 1.5f);
	return limColor * lim;
}
/*!
 *@brief	スペキュラライトを計算。
 */
float3 SpecLight(float3 normal, float3 worldPos, float2 uv)
{
	float specPow = tex2D(g_speculerMapSampler, uv);
	float3 spec = 0.0f;
	float3 toEyeDir = normalize( g_cameraPos - worldPos );
	float3 R = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	for( int i = 0; i < NUM_DIFFUSE_LIGHT; i++ ){
		//スペキュラ成分を計算する。
		//反射ベクトルを計算。
		float3 L = -g_light.diffuseLightDir[i].xyz;
		spec += g_light.diffuseLightColor[i] * pow(max(0.0f, dot(L,R)), 2 ) * g_light.diffuseLightColor[i].w;	//スペキュラ強度。
	}
	return spec * specPow;
}
/*!
 * @brief	ポイントライトを計算。
 */
float3 PointLight( float3 normal, float3 worldPos, int lim )
{
	float3 lightDir = worldPos - g_light.pointLightPosition.xyz;
	float len = length(lightDir) / g_light.pointLightColor.w;
	lightDir = normalize(lightDir);
	float3 color = max( 0.0f, -dot(normal, lightDir)) * g_light.pointLightColor.xyz;
	//距離に反比例して減衰
	color /= max( 1.0f, (len*len) );

	return color;
}
/*!
 * @brief	アルファに埋め込む輝度を計算。
 */
float CalcLuminance( float3 color )
{
	float luminance = dot( color.xyz, float3(0.2125f, 0.7154f, 0.0721f) );
	if(luminance > 1.0f ){
		luminance = 1.0f / luminance;
	}else{
		luminance = 0.0f;
	}
	return luminance;
}