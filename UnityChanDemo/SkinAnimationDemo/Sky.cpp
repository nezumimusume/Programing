#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	skinModelData.LoadModelData("Assets/modelData/Sky.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	
	light.SetAmbinetLight(CVector3(1.0f, 1.0f, 1.0f));
	//高さフォグをかける。
	skinModel.SetFogParam(enFogFuncHeight, 100.0f, 0.0f);
}

void Sky::Update()
{
	skinModel.Update(CVector3(0.0f, 0.0f, 0.0f), CQuaternion::Identity, CVector3(1.0f, 1.0f, 1.0f));
}
void Sky::Render(CRenderContext& renderContext) 
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
