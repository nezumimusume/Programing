/*!
 * @brief	プレイヤーのステート
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/FSM/PlayerState.h"


namespace {
	const float WALK_THREDHOLD = 0.01f;							//!<歩き状態に遷移する速度の閾値。
	const float RUN_THREDHOLD = CPlayerConst::RUN_SPEED * 0.8f;	//!<走り状態に遷移する速度の閾値。
}
void CPlayerStateIdle::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD ;
	float moveSpeedScaler = moveSpeed.Length();
	if (moveSpeedScaler > runThreadhold) {
		//走り状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler > WALK_THREDHOLD) {
		//歩き状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
}

void CPlayerStateWalk::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();
	
	if (moveSpeedScaler > runThreadhold) {
		//走り状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Run);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//待機状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}

void CPlayerStateRun::Update()
{
	CVector3 moveSpeed = m_player->GetMoveSpeed();
	float runThreadhold = RUN_THREDHOLD;
	float moveSpeedScaler = moveSpeed.Length();

	if (moveSpeedScaler < runThreadhold) {
		//歩き状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Walk);
	}
	else if (moveSpeedScaler < WALK_THREDHOLD) {
		//待機状態に遷移。
		m_psm->ChangeState(CPlayerConst::enState_Idle);
	}
}