/*!
 * @brief	プレイヤーのステートマシーン。
 */

#include "stdafx.h"
#include "Player/FSM/PlayerStateMachine.h"

void CPlayerStateMachine::ChangeState(CPlayerConst::EnState nextState)
{
	if (nextState == m_state) {
		//同一ステートへの遷移。
		return;
	}
	DeleteGO(m_currentState);
	m_state = nextState;
	switch (nextState) {
	case CPlayerConst::enState_Idle:
		m_currentState = &m_idleState;
		break;
	case CPlayerConst::enState_Run:
		m_currentState = &m_runState;
		break;
	case CPlayerConst::enState_Walk:
		m_currentState = &m_walkState;
		break;
	}
	AddGO(0, m_currentState, nullptr);
}
bool CPlayerStateMachine::Start()
{
	ChangeState(CPlayerConst::enState_Idle);
	return true;
}