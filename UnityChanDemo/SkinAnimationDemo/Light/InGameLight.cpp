/*!
 * @brief	インゲーム中のライト。
 */

#include "stdafx.h"
#include "Light/InGameLight.h"
#include "Scene/GameScene.h"
#include "tkEngine/nature/tkSky.h"
#include "Player/Player.h"

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
	defaultLight.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, 0.707f));
	defaultLight.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, 0.0f));


	defaultLight.SetDiffuseLightColor(0, CVector4(0.8f, 0.8f, 0.8f, 10.0f));
	defaultLight.SetDiffuseLightColor(1, CVector4(0.1f, 0.1f, 0.1f, 10.0f));
	defaultLight.SetDiffuseLightColor(2, CVector4(0.1f, 0.1f, 0.1f, 10.0f));
	defaultLight.SetDiffuseLightColor(3, CVector4(0.1f, 0.1f, 0.1f, 10.0f));
	
	defaultLight.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));

	defaultLight.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	defaultLight.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));
	Sky().SetSceneLight(defaultLight);
	Sky().SetNightAmbientLight({0.1f, 0.1f, 0.1f});
	return true;
}
void InGameLight::Update() 
{
	const CVector3& sunDir = Sky().GetSunDir();

	//シャドウマップのライトの位置を太陽の位置から計算する。
	CVector3 lightPos = Sky().GetSunPosition();
	lightPos.Normalize();
	lightPos.Scale(30.0f);
	lightPos.Add(g_player->GetPosition());
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(g_player->GetPosition());
}