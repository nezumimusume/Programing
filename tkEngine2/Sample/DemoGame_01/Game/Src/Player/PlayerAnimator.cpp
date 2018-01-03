/*!
 * @brief	プレイヤーのアニメータ。
 */

#include "stdafx.h"
#include "Player/Player.h"
#include "Player/PlayerRenderer.h"
#include "Player/PlayerAnimator.h"

bool CPlayerAnimator::Start()
{
	m_animClips[enAnimationClip_Idle].Load(L"animData/player/idle.tka");
	m_animClips[enAnimationClip_Idle].SetLoopFlag(true);

	m_animClips[enAnimationClip_Walk].Load(L"animData/player/walk.tka");
	m_animClips[enAnimationClip_Walk].SetLoopFlag(true);

	m_animClips[enAnimationClip_Run].Load(L"animData/player/run.tka");
	m_animClips[enAnimationClip_Run].SetLoopFlag(true);

	m_animation.Init(m_player->GetPlayerRenderer().GetSkinModelData(), m_animClips, enANimationClip_Num);
	m_animation.Play(enAnimationClip_Idle);
	return true;
}
void CPlayerAnimator::Update()
{
	CPlayerConst::EnState state = m_player->GetCurrentState();
	if (state == CPlayerConst::enState_Idle) {
		m_animation.Play(enAnimationClip_Idle, 0.2f);
	}
	else if (state == CPlayerConst::enState_Run)
	{
		m_animation.Play(enAnimationClip_Run, 0.2f);
	}
	else if (state == CPlayerConst::enState_Walk) {
		m_animation.Play(enAnimationClip_Walk, 0.2f);
	}
	m_animation.Update(GameTime().GetFrameDeltaTime());
}