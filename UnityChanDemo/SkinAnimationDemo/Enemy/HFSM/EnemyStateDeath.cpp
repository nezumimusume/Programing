/*!
 * @brief	ヤラレ状態。
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDeath.h"


/*!
 * @brief	コンストラクタ。
 */
EnemyStateDeath::EnemyStateDeath( Enemy* enemy ) :
	IEnemyState(enemy)
{
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateDeath::~EnemyStateDeath()
{
}
void EnemyStateDeath::Update() 
{
	enemy->PlayAnimation(Enemy::enAnimDeath);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateDeath::Enter() 
{
}
void EnemyStateDeath::Leave()
{
}
