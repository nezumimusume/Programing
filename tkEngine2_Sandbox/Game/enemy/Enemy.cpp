/*!
 * @brief	敵。
 */

#include "stdafx.h"
#include "enemy/enemy.h"


Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}
bool Enemy::Start()
{
	
	m_skinModelData.Load(L"modelData/enemy_00.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	//アニメーションクリップのロード。
	m_animationClip[enAnimationClip_idle].Load(L"animData/enemy_00/idle.tka", L"Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	CAnimationClip* animClip[] = {
		&m_animationClip[enAnimationClip_idle],
	};
	m_animation.Init(m_skinModelData, animClip, 1);
	m_animation.Play(L"Idle");
	m_rotation.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_characterController.Init(10.0f, 50.0f, m_position);
	return true;
}
void Enemy::Update() 
{
	m_animation.Update(GameTime().GetFrameDeltaTime());
	m_skinModel.Update(m_position, m_rotation, {4.0f, 4.0f, 4.0f});
}
void Enemy::Render(CRenderContext& rc) 
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
