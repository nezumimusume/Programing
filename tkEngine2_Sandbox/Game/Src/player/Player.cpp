#include "stdafx.h"
#include "Player.h"
#include "tkEngine/light/tkPointLight.h"
#include "hud/HPBar.h"
#include "hud/MPBar.h"
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
	m_skinModelData.Load(L"Assets/modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	//法線マップをロード。
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_N.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_S.dds");
	m_wnormalMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_wuqi_N.dds");
	m_wspecularMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_wuqi_S.dds");

	//CSkinModelEffectを検索。<-マテリアルの検索と同義。
	m_skinModel.FindModelEffect([&](CModelEffect* effect) {
		if (effect->EqualMaterialName(L"bodyMat")) {
			//体のマテリアル。
			effect->SetNormalMap(m_normalMapSRV.GetBody());
			effect->SetSpecularMap(m_specularMapSRV.GetBody());
		}
		else if (effect->EqualMaterialName(L"weapon")) {
			//武器。
			effect->SetNormalMap(m_wnormalMapSRV.GetBody());
			effect->SetSpecularMap(m_wspecularMapSRV.GetBody());
		}

	});
	//アニメーションクリップのロード。
	m_animationClip[enAnimationClip_idle].Load(L"Assets/animData/player/idle.tka", L"Idle");
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].Load(L"Assets/animData/player/run.tka", L"Run");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].Load(L"Assets/animData/player/walk.tka", L"Walk");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	CAnimationClip* animClip[] = {
		&m_animationClip[enAnimationClip_idle],
		&m_animationClip[enAnimationClip_run],
		&m_animationClip[enAnimationClip_walk],
	};
	m_animation.Init(m_skinModelData, animClip, 3);
	m_animation.Play(L"Idle");

	m_characterCtr.Init(15.0f, 50.0f, m_position);
	m_characterCtr.SetGravity(-980.0f);
	
	m_rotation.SetRotationDeg(CVector3::AxisX, 90.0f);

	m_hpBar = NewGO<HPBar>(0);
	m_mpBar = NewGO<MPBar>(0);
	return true;
}
void Player::Update() 
{
	CVector3 inputPad;
	inputPad.x = Pad(0).GetLStickXF();
	inputPad.y = Pad(0).GetLStickYF();
	inputPad.z = 0.0f;
	if (inputPad.Length() > 0.8f) {
		m_animation.Play(L"Run", 0.2);
	}else if (inputPad.Length() > 0.0f) {
		m_animation.Play(L"Walk", 0.2);
	}else{
		m_animation.Play(L"Idle", 0.2f);
	}
	if (Pad(0).IsTrigger(enButtonA) && m_characterCtr.IsOnGround()) {
		m_moveSpeed.y = 300.0f;
		m_characterCtr.Jump();	//ジャンプしたことを通知する。

	}
	CVector3 camForward = MainCamera().GetForward();
	CVector3 camRight = MainCamera().GetRight();
	camForward.y = 0.0f;
	camForward.Normalize();
	camRight.y = 0.0f;
	camRight.Normalize();
	camForward.Scale(inputPad.y * 200.0f);
	camRight.Scale(inputPad.x * 200.0f);
	m_moveSpeed.x = camForward.x + camRight.x;
	m_moveSpeed.z = camForward.z + camRight.z;
	//カメラ座標系の移動速度をワールド座標系に変換する。
	m_characterCtr.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_position = m_characterCtr.GetPosition();
	
	CVector3 moveSpeed = m_moveSpeed;
	moveSpeed.y = 0.0f;
	if (moveSpeed.LengthSq() > 0.001f) {
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
		CQuaternion q;
		q.SetRotation(CVector3::Up, atan2f(moveSpeed.x, moveSpeed.z));
		q.Multiply(qRot);
		m_rotation = q;
	}
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	
	m_animation.Update(GameTime().GetFrameDeltaTime());
	
	

	
}
void Player::Render(CRenderContext& rc) 
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}