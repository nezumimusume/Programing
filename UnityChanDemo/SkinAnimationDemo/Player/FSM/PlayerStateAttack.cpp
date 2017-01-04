#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player/Player.h"

PlayerStateAttack::PlayerStateAttack(Player* player):
	IPlayerState(player)
{

}
PlayerStateAttack::~PlayerStateAttack()
{

}
void PlayerStateAttack::Update()
{
	//移動がピタって止まると気持ちわるいので
	CVector3 moveSpeed = player->characterController.GetMoveSpeed();
	moveSpeed.Scale(0.8f);
	player->characterController.SetMoveSpeed(moveSpeed);
	player->characterController.Execute(player->GetLocalFrameDeltaTime());
	int currentAnimNo = player->animation.GetPlayAnimNo();
	if (!player->animation.IsPlay() && player->nextAttackAnimNo == Player::AnimationInvalid) {
		player->ChangeState(Player::enStateStand);
	}
	else if (
		Pad(0).IsTrigger(enButtonX)
		&& currentAnimNo >= Player::AnimationAttack_Start
		&& currentAnimNo < Player::AnimationAttack_End
		&& currentAnimNo == player->reqAttackAnimNo
		) {
		//コンボ発生。
		player->nextAttackAnimNo = (Player::AnimationNo)(player->animation.GetPlayAnimNo() + 1);
	}
}
void PlayerStateAttack::Enter()
{

}
void PlayerStateAttack::Leave()
{

}