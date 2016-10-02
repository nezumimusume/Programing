/*!
 * @brief	歩き状態。
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateAttack.h"
#include "UnityChan.h"
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
	CVector3 dir;
	dir.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
	if (dir.LengthSq() > 0.01f) {
		dir.Normalize();
		enemy->SetMoveDirection(dir);
	}
}
void EnemyStateAttack::Enter()
{
	IEnemyState::Enter();
}
void EnemyStateAttack::Leave()
{
}
