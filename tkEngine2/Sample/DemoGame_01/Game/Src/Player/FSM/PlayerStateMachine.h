/*!
 * @brief	プレイヤーのステートマシーン。
 */

#pragma once

#include "Player/FSM/PlayerState.h"
#include "Player/PlayerConst.h"

class CPlayerStateMachine : public IGameObject{
public:
	
	CPlayerStateMachine(CPlayer* pl) :
		m_idleState(pl, this),
		m_runState(pl, this),
		m_walkState(pl, this)
	{
	}
	bool Start() override final;
	void Update() override final
	{
	}
	/*!
	* @brief	ステートの切り替え。
	*@param[in]	nextState	次のステート。
	*/
	void ChangeState(CPlayerConst::EnState nextState);
	/*!
	 *@brief	移動できるか判定。
	 */
	bool IsMove() const
	{
		if (m_currentState == nullptr) {
			return false;
		}
		return m_currentState->IsMove();
	}
	/*!
	 *@brief	現在の状態を取得。
	 */
	CPlayerConst::EnState GetCurrentState() const
	{
		return m_state;
	}
private:
	
	CPlayerConst::EnState m_state = CPlayerConst::enState_Invalid;
	IPlayerState* m_currentState = nullptr;
	CPlayerStateIdle m_idleState;
	CPlayerStateWalk m_walkState;
	CPlayerStateRun m_runState;
};