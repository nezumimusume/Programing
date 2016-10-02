/*!
 * @brief	待機状態。
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateIdle.h"


/*!
 * @brief	コンストラクタ。
 */
EnemyStateIdle::EnemyStateIdle(Enemy* enemy) :
	IEnemyState(enemy)
{
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateIdle::~EnemyStateIdle()
{
}
void EnemyStateIdle::Update()
{
}
void EnemyStateIdle::Enter() 
{
	IEnemyState::Enter();
	enemy->SetMoveSpeed(0.0f);
	enemy->PlayAnimation(Enemy::enAnimStand);
}
void EnemyStateIdle::Leave() 
{
}
