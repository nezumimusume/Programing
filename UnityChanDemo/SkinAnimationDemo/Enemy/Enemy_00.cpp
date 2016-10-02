/*!
 * @brief	タイプ0の敵。
 */

#include "stdafx.h"
#include "Enemy/Enemy_00.h"
#include "UnityChan.h"
#include "Enemy/HFSM/EnemyStateSearch.h"
#include "Enemy/HFSM/EnemyStateFind.h"

Enemy_00::Enemy_00()
{
	state = enLocalState_Search;
	initPosition = CVector3::Zero;
	moveSpeed = 0.0f;
}
Enemy_00::~Enemy_00()
{
	for (auto& state : states) {
		delete state;
	}
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
	PlayAnimation(enAnimWalk);
	initPosition = position;

	characterController.Init(0.4f, position);
	InitHFSM();
}
/*!
 * @brief	HFSMを初期化。
 */
void Enemy_00::InitHFSM()
{
	//探索状態を追加。
	states.push_back( new EnemyStateSearch(this) );
	//発見状態を追加。
	states.push_back( new EnemyStateFind(this) );
	state = enLocalState_Search;
	states[state]->Enter();
}
void Enemy_00::Start()
{
}
void Enemy_00::Update()
{
	states[state]->Update();
	switch (state) {
	case enLocalState_Search:
	{
		CVector3 unityPos = g_unityChan->GetPosition();
		CVector3 diff;
		diff.Subtract(unityPos, position);
		if (diff.LengthSq() < 5.0f * 5.0f) {
			//見つけた。
			states[state]->Leave();
			state = enLocalState_Find;
			states[state]->Enter();
		}
	}break;
	case enLocalState_Find:
	{
	
	}break;
	}
	CVector3 speed = characterController.GetMoveSpeed();
	speed.x = moveDirection.x * moveSpeed;
	speed.z = moveDirection.z * moveSpeed;
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