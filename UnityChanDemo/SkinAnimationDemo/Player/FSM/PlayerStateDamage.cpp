#include "stdafx.h"
#include "PlayerStateDamage.h"
#include "Player/Player.h"
#include "ParticleParam.h"

PlayerStateDamage::PlayerStateDamage(Player* player) :
	IPlayerState(player)
{

}
PlayerStateDamage::~PlayerStateDamage()
{

}
void PlayerStateDamage::Update()
{
	if (!player->animation.IsPlay()) {
		player->ChangeState(Player::enStateStand);
	}
}
void PlayerStateDamage::Enter()
{
	player->EmitBloodParticle();
}
void PlayerStateDamage::Leave()
{
	for (auto& p : player->particleEmitterList) {
		DeleteGO(p);
	}
	player->particleEmitterList.clear();
}