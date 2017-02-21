#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

bool Item::Start()
{
	skinModelData.LoadModelData("Assets/modelData/Apple.X", NULL);
	skinModel.Init(&skinModelData);
	light.SetAmbinetLight({ 1.0f, 1.0f, 1.0f });
	skinModel.SetLight(&light);
	//rotation.SetRotation();
	return true;
}

void Item::Update()
{

}

void Item::Render(CRenderContext& rendercontext)
{
	//skinModel.Draw();
}