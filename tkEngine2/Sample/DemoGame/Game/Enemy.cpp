#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
bool Enemy::Start()
{
	m_skinModelData.Load(L"modelData/enemy.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);

	m_animClip[enAnimationClip_idle].Load(L"animData/enemy/idle.tka");
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animClip[enAnimationClip_run].Load(L"animData/enemy/run.tka");
	m_animClip[enAnimationClip_run].SetLoopFlag(true);

	m_animation.Init(m_skinModelData, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_run);
	return true;
}
void Enemy::Update()
{
	m_animation.Update(GameTime().GetFrameDeltaTime());
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, {3.0f, 3.0f, 3.0f});
}
void Enemy::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
