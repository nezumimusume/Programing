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
		sunModelData.LoadModelDataAsync("Assets/modelData/sun.x", NULL);
		initStep = InitStep_Wait;
		break;
	case InitStep_Wait:
		if (skinModelData.IsLoadEnd() && sunModelData.IsLoadEnd()) {
			skinModel.Init(skinModelData.GetBody());
			light.SetAmbinetLight(CVector3(1.2f, 1.0f, 1.0f));
			skinModel.SetLight(&light);
			sunModel.Init(sunModelData.GetBody());
			sunLight.SetEmissionLightColor(CVector3(1.5f, 1.5f, 1.5f));
			sunModel.SetLight(&sunLight);
			CSkinModelMaterial* mat = skinModelData.GetBody()->FindMaterial("sky.png");
			if (mat) {
				mat->SetTexture("g_skyCubeMap", TextureResources().Load("Assets/modelData/skyCubeMap.dds", true));
			}
			//高さフォグをかける。
		//	skinModel.SetFogParam(enFogFuncHeight, 100.0f, 0.0f);
			skinModel.SetAtomosphereParam(enAtomosphereFuncSkyFromAtomosphere, gameScene->GetSky()->GetAtomosphereParam());
			sunModel.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere, gameScene->GetSky()->GetAtomosphereParam());
			return true;
		}
		break;
	}
	return false;
}
void Sky::Update()
{
	sunAngle += 0.02f * GameTime().GetFrameDeltaTime();
	
	CVector3 surDir;
	sunPosition.Set(0.0f, sinf(sunAngle), cosf(sunAngle));
	CMatrix mRotZ;
	mRotZ.MakeRotationZ(CMath::PI * 0.15f);
	mRotZ.Mul(sunPosition);

	surDir = sunPosition;
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
	CVector3 sunModelPos = surDir;
	sunModelPos.Scale(250.0f);
	sunModelPos.Add(pos);
	sunModel.Update(sunModelPos, CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
	CLight& sceneLight = gameScene->GetDefaultLight();
	//リムライトを更新。
	sceneLight.SetLimLightDirection(surDir);
	//アンビエントライト更新。
	float t = max( 0.0f, surDir.Dot(CVector3::Up) );
	
	const CVector3 dayLight = CVector3(0.3f, 0.3f, 0.3f);//日中のアンビエントライト。
	const CVector3 nightLight = CVector3(0.07f, 0.07f, 0.07f);	//夜間のアンビエントライト。
	CVector3 ambientLight;
	ambientLight.Lerp(t, nightLight, dayLight);
	sceneLight.SetAmbinetLight(ambientLight);
}

void Sky::Render(CRenderContext& renderContext) 
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	sunModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
