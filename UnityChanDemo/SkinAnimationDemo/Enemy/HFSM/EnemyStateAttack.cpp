/*!
 * @brief	歩き状態。
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateAttack.h"

/*!
* @brief	コンストラクタ。
*/
EnemyStateAttack::EnemyStateAttack( Enemy* enemy ) :
	IEnemyState(enemy)
{

}
/*!
	* @brief	デストラクタ。
	*/
EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	enemy->PlayAnimation(Enemy::enAnimAttack);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateAttack::Enter()
{
	IEnemyState::Enter();
}
void EnemyStateAttack::Leave()
{
}
