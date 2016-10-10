/*!
 * @brief	ヤラレ状態。
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDamage.h"


/*!
 * @brief	コンストラクタ。
 */
EnemyStateDamage::EnemyStateDamage( Enemy* enemy ) :
	IEnemyState(enemy)
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
	enemy->PlayAnimation(Enemy::enAnimDamage);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateDamage::Enter() 
{
}
void EnemyStateDamage::Leave()
{
}
