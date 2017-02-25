#include "stdafx.h"
#include "Item.h"
#include "Player/Player.h"
#include "Scene/GameScene.h"


Item::Item()
{
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	deleteFlg = false;
}


Item::~Item()
{
}

void Item::OnDestroy()
{
}

bool Item::Start()
{
	return true;
}

void Item::Init(CVector3 initPosition)
{
	position = initPosition;
	position.y += 1.1f;
	//GameSceneでロードしたデータのクローンを作る
	skinModelData.CloneModelData(*gameScene->GetItemModelData(), NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&gameScene->GetDefaultLight());
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
}


void Item::Update()
{
	if (deleteFlg)
	{
		true;
	}
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, CMath::DegToRad(5));
	rotation.Multiply(multi);

	CVector3 distance;
	distance.Subtract(position, g_player->GetPosition());
	distance.y = 0.0f;
	if (distance.Length() < 0.5f)
	{
		g_player->Heel();
		deleteFlg = true;
	}
	skinModel.Update(position, rotation, CVector3::One);
}

void Item::Render(CRenderContext& rendercontext)
{
	skinModel.Draw(rendercontext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
