#include "stdafx.h"
#include "PlayerStateRun.h"
#include "Player/Player.h"
#include "tkEngine/Sound/tkSoundSource.h"

PlayerStateRun::PlayerStateRun(Player* player) :
	IPlayerState(player)
{

}
PlayerStateRun::~PlayerStateRun()
{

}
void PlayerStateRun::Update()
{
	const float USE_MP_DASH = 50.0f;		//ダッシュ魔法を使った時のMP使用量。
	const float MOVE_SPEED = 7.0f;
	CVector3 moveSpeed = player->characterController.GetMoveSpeed();
	if (Pad(0).IsTrigger(enButtonRB3)) {
		player->isPointLightOn = !player->isPointLightOn;
	}
	if (Pad(0).IsPress(enButtonA)) {
		//Aボタンが押された。
		//車との距離を調べる。
		if (!player->characterController.IsJump()) {
			//ジャンプ。
			moveSpeed.y = 8.0f;
			player->characterController.Jump();
		}
	}
	//走りか立ち状態の時。
	CVector3 moveDirLocal;
	moveDirLocal.y = 0.0f;
	moveDirLocal.x = Pad(0).GetLStickXF();
	moveDirLocal.z = Pad(0).GetLStickYF();
	const CMatrix& mViewInv = g_camera->GetCamera().GetViewMatrixInv();
	//カメラ空間から見た奥方向のベクトルを取得。
	CVector3 cameraZ;
	cameraZ.x = mViewInv.m[2][0];
	cameraZ.y = 0.0f;		//Y軸いらない。
	cameraZ.z = mViewInv.m[2][2];
	cameraZ.Normalize();	//Y軸を打ち消しているので正規化する。
							//カメラから見た横方向のベクトルを取得。
	CVector3 cameraX;
	cameraX.x = mViewInv.m[0][0];
	cameraX.y = 0.0f;		//Y軸はいらない。
	cameraX.z = mViewInv.m[0][2];
	cameraX.Normalize();	//Y軸を打ち消しているので正規化する。

	CVector3 moveDir;
	moveDir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
	moveDir.y = 0.0f;	//Y軸はいらない。
	moveDir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

	float fMoveSpeed = MOVE_SPEED;
	bool isDash = false;
	if (Pad(0).IsPress(enButtonRB2)) {
		//MPの残量を見てダッシュできるか調べる。
		float useMp = USE_MP_DASH * GameTime().GetFrameDeltaTime();
		if (player->mp - useMp >= 0.0f) {
			//MP使える。
			isDash = true;
		}
		player->UseMagicPoint(useMp);
	}

	if (isDash) {
		//ダッシュ中可能か調べる。
		fMoveSpeed *= 1.7f;
		g_camera->SetViewAngle(CMath::DegToRad(60.0f));
		g_camera->SetDampingRate(0.9f);
		player->animation.SetAnimationSpeedRate(1.4f);
		MotionBlur().SetEnable(true);
	}
	else {
		g_camera->SetViewAngle(CMath::DegToRad(70.0f));
		g_camera->SetDampingRate(0.9f);
		player->animation.SetAnimationSpeedRate(1.0f);
		MotionBlur().SetEnable(false);
	}
	moveSpeed.x = moveDir.x * fMoveSpeed;
	moveSpeed.z = moveDir.z * fMoveSpeed;

	if (moveDir.LengthSq() < 0.0001f) {
		//立ち状態に遷移。
		player->ChangeState(player->enStateStand);
	}
	else {
		player->rotation.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
	}
	bool isOnGround = player->characterController.IsOnGround();
	player->characterController.SetMoveSpeed(moveSpeed);
	player->characterController.Execute();
	if (isOnGround == false
		&& player->characterController.IsOnGround()
		) {
		//着地した。
		//着地音を再生。
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init("Assets/sound/landing.wav");
		se->Play(false);
		se->SetVolume(0.25f);
	}

	if (Pad(0).IsTrigger(enButtonX) && !player->characterController.IsJump()) {
		player->nextAttackAnimNo = player->AnimationAttack_00;
		player->ChangeState(player->enState_Attack);
	}
}
void PlayerStateRun::Enter()
{

}
void PlayerStateRun::Leave()
{

}