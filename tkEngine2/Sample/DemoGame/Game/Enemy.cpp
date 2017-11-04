#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy() :
	m_pathMoveLoop(this, m_movePath)
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
	m_animation.Play(enAnimationClip_idle);

	m_charaCon.Init(20.0f, 100.0f, -1800.0f, m_position);
	return true;
}
void Enemy::Update()
{
	m_pathMoveLoop.Update();

	m_animation.Update(GameTime().GetFrameDeltaTime());
	const CVector3 scale = { 3.0f, 3.0f, 3.0f };
	m_skinModel.Update(m_position, m_rotation, scale);
	const CMatrix& mWorld = m_skinModel.GetWorldMatrix();
	
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}
void Enemy::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
