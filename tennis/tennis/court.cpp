#include "stdafx.h"
#include "GameCamera.h"
#include "court.h"


Court::Court()
{

}
Court::~Court()
{

}
void Court::Init()
{
	//モデルデータのロード。
	modelData.LoadModelData("Assets/modelData/court.x", NULL);
	//モデルにモデルデータをセット。
	model.Init(&modelData);
}

void Court::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}