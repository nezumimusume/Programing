#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	
}
Player::~Player()
{
}

/*!
*@brief	初期化。
*/
bool Player::Start()
{
	m_skinModelData.Load(L"Assets/modelData/Thethief_H");
	m_skinModel.Init(m_skinModelData);

	//アニメーションクリップのロード。
	m_animationClip[enAnimationClip_idle].Load(L"Assets/animData/player/idle.tka", L"Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].Load(L"Assets/animData/player/run.tka", L"Run");
	CAnimationClip* animClip[] = {
		&m_animationClip[enAnimationClip_idle],
		&m_animationClip[enAnimationClip_run],
	};
	m_animation.Init(m_skinModelData, animClip, 2);
	m_animation.Play(L"Idle");

	return true;
}
void Player::Update() 
{
	if (Pad(0).IsTrigger(enButtonRight)) {
		m_animation.Play(0);
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		m_animation.Play(L"Run");
	}
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_skinModel.Update({ 0.0f, 0.0f, 0.0f }, qRot, CVector3::One);
	m_animation.Update(1.0f / 60.0f);
}
void Player::Render(CRenderContext& rc) 
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}