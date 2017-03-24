#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/nature/tkSky.h"
#include "tkEngine/graphics/material/tkSKinModelMaterial.h"

namespace tkEngine{
	CSky::CSky() 
	{
	}
	void CSky::Init()
	{
		sunPosition.Set(0.0f, 1000000.0f, 0.0f);
		skinModelData.LoadModelData("Assets/modelData/Sky.X", NULL);
		sunModelData.LoadModelData("Assets/modelData/sun.x", NULL);
		skinModel.Init(skinModelData.GetBody());
		light.SetAmbinetLight(CVector3(1.2f, 1.0f, 1.0f));
		skinModel.SetLight(&light);
		sunModel.Init(sunModelData.GetBody());
		sunLight.SetEmissionLightColor(CVector3(1.5f, 1.5f, 1.5f));
		sunModel.SetLight(&sunLight);
		CSkinModelMaterial* mat = skinModelData.GetBody()->FindMaterial("sky.png");
		if (mat) {
			mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_SkyCubeMap, *TextureResources().Load("Assets/modelData/skyCubeMap.dds", true));
			mat->Build(CSkinModelMaterial::enTypeSky);
		}		
		skinModel.SetAtomosphereParam(enAtomosphereFuncSkyFromAtomosphere);
	}
	bool CSky::Start() 
	{
		return true;
	}
	void CSky::Update()
	{
		if (camera != nullptr) {
			sunAngle += 0.02f * GameTime().GetFrameDeltaTime() * deltaTimeMul;
			
			//X軸回転。
			sunPosition.Set(0.0f, sinf(sunAngle), cosf(sunAngle));
			//Z軸回転。
			const float angleZ = CMath::PI * -0.15f;
			sunPosition.x = sunPosition.y * sinf(angleZ);
			sunPosition.y *= cosf(angleZ);

			sunDir = sunPosition;
			sunPosition.Scale(1000000.0f);
			atomosphereParam.Update(camera->GetPosition(), sunPosition);
			CVector3 lightPos = sunPosition;
			lightPos.Normalize();
			lightPos.Scale(30.0f);
			/*		lightPos.Add(g_player->GetPosition());
					ShadowMap().SetLightPosition(lightPos);
					ShadowMap().SetLightTarget(g_player->GetPosition());*/

			skinModel.Update(camera->GetTarget(), CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
			CVector3 sunModelPos = sunDir;
			sunModelPos.Scale(250.0f);
			sunModelPos.Add(camera->GetTarget());
			sunModel.Update(sunModelPos, CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
			//シーンライトが設定されている。
			if(sceneLight){
				//一本目のディフューズライトは太陽光として計算する。
				//リムライトを更新。
				CVector3 limLightDir = sunDir;
				limLightDir.Scale(-1.0f);
				sceneLight->SetDiffuseLightDirection(0, limLightDir);
				sceneLight->SetLimLightDirection(limLightDir);
				//アンビエントライト更新。
				float t = max(0.0f, sunDir.Dot(CVector3::Up));

				//太陽の位置からアンビエントライトを計算。
				CVector3 ambientLight;
				ambientLight.Lerp(t, nightAmbinetLight, dayAmbinetLight);
				sceneLight->SetAmbinetLight(ambientLight);

			}
		}
		
	}

	void CSky::Render(CRenderContext& renderContext) 
	{
		if (camera != nullptr) {
			//Zは書き込まない。
			renderContext.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			skinModel.Draw(renderContext, camera->GetViewMatrix(), camera->GetProjectionMatrix());
			sunModel.Draw(renderContext, camera->GetViewMatrix(), camera->GetProjectionMatrix());
			renderContext.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}