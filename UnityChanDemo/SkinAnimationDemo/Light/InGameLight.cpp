/*!
 * @brief	インゲーム中のライト。
 */

#include "stdafx.h"
#include "Light/InGameLight.h"
#include "Scene/GameScene.h"
#include "Map/Sky.h"

InGameLight::InGameLight()
{
}
InGameLight::~InGameLight()
{
}
bool InGameLight::Start()
{
	defaultLight.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	defaultLight.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	defaultLight.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	defaultLight.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	defaultLight.SetDiffuseLightColor(0, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(1, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(2, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(3, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	
	defaultLight.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));

	defaultLight.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	defaultLight.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));
	return true;
}
void InGameLight::Update() 
{
	const CVector3& sunDir = gameScene->GetSky()->GetSunDir();

	//リムライトを更新。
	CVector3 limLightDir = sunDir;
	limLightDir.Scale(-1.0f);
	defaultLight.SetLimLightDirection(limLightDir);
	//アンビエントライト更新。
	float t = max(0.0f, sunDir.Dot(CVector3::Up));

	//太陽の位置からアンビエントライトを計算。
	const CVector3 dayLight = CVector3(0.3f, 0.3f, 0.3f);//日中のアンビエントライト。
	const CVector3 nightLight = CVector3(0.07f, 0.07f, 0.07f);	//夜間のアンビエントライト。
	CVector3 ambientLight;
	ambientLight.Lerp(t, nightLight, dayLight);
	defaultLight.SetAmbinetLight(ambientLight);
}