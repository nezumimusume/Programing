#include "stdafx.h"
#include "Sky.h"
#include "Player/Player.h"
#include "Scene/GameScene.h"
#include "map/sky.h"

Sky::Sky() :
	player(nullptr)
{
	skinModelData.LoadModelData("Assets/modelData/Sky.X", NULL);
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
}
bool Sky::Start() 
{
	switch (initStep) {
	case InitStep_Load:
		sunPosition.Set(0.0f, 1000000.0f, 0.0f);
		skinModelData.LoadModelDataAsync("Assets/modelData/Sky.X", NULL);
		initStep = InitStep_Wait;
		break;
	case InitStep_Wait:
		if (skinModelData.IsLoadEnd()) {
			skinModel.Init(skinModelData.GetBody());
			skinModel.SetLight(&light);

			light.SetAmbinetLight(CVector3(1.2f, 1.0f, 1.0f));
			//高さフォグをかける。
		//	skinModel.SetFogParam(enFogFuncHeight, 100.0f, 0.0f);
			skinModel.SetAtomosphereParam(enAtomosphereFuncSkyFromAtomosphere, gameScene->GetSky()->GetAtomosphereParam());
			return true;
		}
		break;
	}
	return false;
}
void Sky::Update()
{
	sunAngle += 0.1f * GameTime().GetFrameDeltaTime();
	sunPosition.Set(0.0f, sinf(sunAngle), cosf(sunAngle));
	sunPosition.Scale(1000000.0f);
	atomosphereParam.Update(g_camera->GetCamera().GetPosition(), sunPosition);
	CVector3 lightPos = sunPosition;
	lightPos.Normalize();
	lightPos.Scale(30.0f);
	lightPos.Add(g_player->GetPosition());
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(g_player->GetPosition());

	CVector3 pos;
	pos.x = player->GetPosition().x;
	pos.y = 0.0f;
	pos.z = player->GetPosition().z;
	skinModel.Update(pos, CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
}
void Sky::Render(CRenderContext& renderContext) 
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
