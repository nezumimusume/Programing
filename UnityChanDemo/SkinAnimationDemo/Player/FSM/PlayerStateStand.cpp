#include "stdafx.h"
#include "Player/Player.h"
#include "PlayerStateStand.h"
#include "tkEngine/Sound/tkSoundSource.h"

PlayerStateStand::PlayerStateStand(Player* player) :
	IPlayerState(player)
{

}
PlayerStateStand::~PlayerStateStand()
{

}
void PlayerStateStand::Update()
{
	if (fabsf(Pad(0).GetLStickXF() )> 0.0001f || fabsf(Pad(0).GetLStickYF()) > 0.0001f) {
		//走り状態に遷移。
		player->ChangeState(player->enStateRun);
	}
	

	bool isOnGround = player->characterController.IsOnGround();
	CVector3 moveSpeed = player->characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	if (Pad(0).IsPress(enButtonA)) {
		//Aボタンが押された。
		//車との距離を調べる。
		if (!player->characterController.IsJump()) {
			//ジャンプ。
			moveSpeed.y = 8.0f;
			player->characterController.Jump();
		}
	}

	player->characterController.SetMoveSpeed(moveSpeed);
	player->characterController.Execute(player->GetLocalFrameDeltaTime());
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
void PlayerStateStand::Enter()
{
}
void PlayerStateStand::Leave()
{

}