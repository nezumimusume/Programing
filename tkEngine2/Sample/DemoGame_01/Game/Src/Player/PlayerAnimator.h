/*!
 * @brief	プレイヤーのアニメーター
 */

#pragma once

class CPlayer;

/*!
 * @brief	プレイヤーのアニメーター。
 */
class CPlayerAnimator : public IGameObject{
public:
	CPlayerAnimator(CPlayer* player)
	{
		m_player = player;
	}
	~CPlayerAnimator()
	{
	}
	bool Start() override;
	void Update() override;
private:
	enum EnAnimationClip{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enANimationClip_Num,
	};
	CAnimationClip m_animClips[enANimationClip_Num];	//!<アニメーションクリップ；。
	CAnimation m_animation;								//!<アニメーション。
	CPlayer* m_player = nullptr;						//!<プレイヤーレンダラー。
};