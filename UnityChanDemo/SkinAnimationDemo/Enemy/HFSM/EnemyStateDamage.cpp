/*!
 * @brief	ヤラレ状態。
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDamage.h"


/*!
 * @brief	コンストラクタ。
 */
EnemyStateDamage::EnemyStateDamage( Enemy* enemy ) :
	IEnemyState(enemy),
	dmgCollisionGroupID(0)
{
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateDamage::~EnemyStateDamage()
{
}
void EnemyStateDamage::Update() 
{
	//enemy->PlayAnimation(Enemy::enAnimDamage);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateDamage::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
	dmgCollisionGroupID = enterArg.arg[0];
	enemy->PlayAnimationForce(Enemy::enAnimDamage);
}
void EnemyStateDamage::Leave()
{
}
