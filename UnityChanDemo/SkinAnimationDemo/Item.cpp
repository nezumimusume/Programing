#include "stdafx.h"
#include "Item.h"
#include "Player/Player.h"
#include "Scene/GameScene.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::OnDestroy()
{
}

void Item::Init(CVector3 initPosition)
{
	position = initPosition;
	position.y += 1.1f;
}

bool Item::Start()
{
	skinModelData.CloneModelData(gameScene->GetItemModelData(), NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&gameScene->GetDefaultLight());
	rotation.SetRotation(CVector3::AxisY, CMath::DegToRad(0));
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	return true;
}

void Item::Update()
{
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, CMath::DegToRad(5));
	rotation.Multiply(multi);

	CVector3 distance;
	distance.Subtract(position, g_player->GetPosition());
	distance.y = 0.0f;
	if (distance.Length() < 0.4f)
	{
		g_player->Heel();
		DeleteGO(this);
	}
	skinModel.Update(position, rotation, CVector3::One);
}

void Item::Render(CRenderContext& rendercontext)
{
	skinModel.Draw(rendercontext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}

