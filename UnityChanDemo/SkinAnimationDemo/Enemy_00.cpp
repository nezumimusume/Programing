/*!
 * @brief	タイプ0の敵。
 */

#include "stdafx.h"
#include "Enemy_00.h"
#include "UnityChan.h"

Enemy_00::Enemy_00()
{
	state = enState_Search;
	initPosition = CVector3::Zero;
	timer = 0.0f;
}
Enemy_00::~Enemy_00()
{
}
void Enemy_00::Init(const char* modelPath, CVector3 pos, CQuaternion rotation)
{
	char filePath[1024];
	sprintf(filePath, "Assets/modelData/%s.x", modelPath);
	SkinModelDataResources().Load(
		skinModelData,
		filePath,
		&animation
	);
	skinModel.Init(skinModelData.GetBody());
	position = pos;
	this->rotation = rotation;

	skinModel.SetLight(&light);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbinetLight(CVector3(0.4f, 0.4f, 0.4f));

	light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));
	animation.PlayAnimation(enAnimWalk);
	initPosition = position;
	moveDirection = CVector3::AxisX;

	characterController.Init(0.4f, position);
}
void Enemy_00::Start()
{
}
void Enemy_00::Update()
{
	switch (state) {
	case enState_Search:
	{
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 1.0f) {
			//1秒間に50%の確率で方向転換。
			if (g_random.GetRandDouble() < 0.5f) {
				float t = (float)g_random.GetRandDouble();
				//最大180度回転
				float turnAngle = t * CMath::PI;
				CMatrix mRot;
				mRot.MakeRotationY(turnAngle);
				mRot.Mul(moveDirection);
			}
			timer = 0.0f;
		}
		CVector3 unityPos = g_unityChan->GetPosition();
		CVector3 diff;
		diff.Subtract(unityPos, position);
		if (diff.LengthSq() < 5.0f * 5.0f) {
			//見つけた。
			state = enState_Find;
		}
	}break;
	case enState_Find:
	{
		moveDirection.Subtract(g_unityChan->GetPosition(), position);
		if (moveDirection.LengthSq() > 0.01f) {
			moveDirection.Normalize();
		}
		else {
			moveDirection = CVector3::AxisZ;
		}
	}break;
	}
	CVector3 speed = characterController.GetMoveSpeed();
	speed.x = moveDirection.x * 3.0f;
	speed.z = moveDirection.z * 3.0f;
	characterController.SetMoveSpeed(speed);
	characterController.Execute();
	position = characterController.GetPosition();
	
	animation.Update(GameTime().GetFrameDeltaTime());
	light.SetPointLightPosition(g_unityChan->GetPointLightPosition());
	light.SetPointLightColor(g_unityChan->GetPointLightColor());
	//回転は適当に。
	float angle = atan2f(moveDirection.x, moveDirection.z);
	rotation.SetRotation(CVector3::AxisY, angle);
	skinModel.Update(position, rotation, CVector3::One);
}
void Enemy_00::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}