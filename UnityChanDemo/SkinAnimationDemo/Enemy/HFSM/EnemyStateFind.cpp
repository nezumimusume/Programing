/*!
 * @brief	発見状態。
 */

#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateFind.h"
#include "Enemy/HFSM/EnemyStateRun.h"
#include "Enemy/HFSM/EnemyStateAttack.h"
#include "Enemy/HFSM/EnemyStateIdle.h"
#include "UnityChan.h"

namespace {
	const float ENEMY_ATTACK_READY_RANGE_SQ = 5.0f * 5.0f;
	const float ENEMY_ATTACK_RANGE_SQ = 0.3f * 0.3f;
}
/*!
 * @brief	コンストラクタ。
 */
EnemyStateFind::EnemyStateFind(Enemy* enemy) :
	IEnemyState(enemy),
	timer(0.0f),
	battleSeat(nullptr)
{
	m_localStates.push_back( new EnemyStateRun(enemy) );
	m_localStates.push_back( new EnemyStateAttack(enemy) );
	m_localStates.push_back(new EnemyStateIdle(enemy));
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateFind::~EnemyStateFind()
{
}
void EnemyStateFind::Update()
{
	m_localStates[m_localState]->Update();
	if (m_localState == enLocalState_Run) {
		CVector3 moveDirTmp;
		if (battleSeat == nullptr) {
			moveDirTmp.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
			moveDirTmp.y = 0.0f;
			if (moveDirTmp.LengthSq() < ENEMY_ATTACK_READY_RANGE_SQ) {
				//アタックReady
				//シートを探す。
				battleSeat = g_unityChan->FindUnuseSeat(enemy->GetPosition());
				if (battleSeat != nullptr) {
					//シートが見つかった。
					battleSeat->isUse = true;
				}
				if (battleSeat == nullptr) {
					//待機状態に。
					ChangeLocalState(enLocalState_Idle);
				}
			}
		}
		if (battleSeat != nullptr) {
			//バトルシートが見つかった。攻撃準備おｋ。
			moveDirTmp.Subtract(battleSeat->position, enemy->GetPosition());
			moveDirTmp.y = 0.0f;
			if (moveDirTmp.LengthSq() < ENEMY_ATTACK_RANGE_SQ) {
				//攻撃レンジに入った。
				ChangeLocalState(enLocalState_Attack);
			}
			else {
				CVector3 dist;
				dist.Subtract(g_unityChan->GetPosition(), enemy->GetPosition());
				if (dist.LengthSq() > ENEMY_ATTACK_READY_RANGE_SQ) {
					//攻撃レンジから出た。
					battleSeat->isUse = false;
					battleSeat = nullptr;
				}
			}
		}
		if (moveDirTmp.LengthSq() > 0.01f) {
			moveDirTmp.Normalize();
			enemy->SetMoveDirection(moveDirTmp);
		}
	}else if(m_localState == enLocalState_Attack){
		CVector3 dist;
		dist.Subtract(battleSeat->position, enemy->GetPosition());
		dist.y = 0.0f;
		if (!enemy->IsPlayAnimation()) {
			ChangeLocalState(enLocalState_Idle);
		}
		if (dist.LengthSq() > ENEMY_ATTACK_RANGE_SQ) {
			ChangeLocalState(enLocalState_Run);
			battleSeat->isUse = false;
			battleSeat = nullptr;
		}
	}
	else if (m_localState == enLocalState_Idle) {
		timer += GameTime().GetFrameDeltaTime();
		if (timer > 0.2f) {
			CVector3 dist;
			if (battleSeat != nullptr) {
				//バトルシートを持っている。
				dist.Subtract(battleSeat->position, enemy->GetPosition());
				dist.y = 0.0f;
				if (dist.LengthSq() > ENEMY_ATTACK_RANGE_SQ) {
					ChangeLocalState(enLocalState_Run);
					battleSeat->isUse = false;
					battleSeat = nullptr;
				}
				else {
					//攻撃。
					ChangeLocalState(enLocalState_Attack);
				}
			}
			else {
				//バトルシートを持っていない。
				ChangeLocalState(enLocalState_Run);
			}
			timer = 0.0f;
		}
	}
}
void EnemyStateFind::Enter() 
{
	IEnemyState::Enter();
	timer = 0.0f;
	battleSeat = NULL;
	ChangeLocalState(enLocalState_Run);
}
void EnemyStateFind::Leave() 
{
	IEnemyState::Leave();
}
