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
	m_skinModelData.Load(L"Assets/modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	//法線マップをロード。
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_N.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_S.dds");
	m_wnormalMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_wuqi_N.dds");
	m_wspecularMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/Thethief_wuqi_S.dds");

	m_skinModel.FindMesh([&](auto& mesh) {
		CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
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

	m_characterCtr.Init(20.0f, 100.0f, m_position);
	m_characterCtr.SetGravity(-980.0f);
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
	m_moveSpeed.x = inputPad.x * -100.0f;
	m_moveSpeed.z = inputPad.y * -100.0f;

	m_characterCtr.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_position = m_characterCtr.GetPosition();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_skinModel.Update(m_position, qRot, CVector3::One);
	
	m_animation.Update(GameTime().GetFrameDeltaTime());
	CVector3 lightPos = m_position;
	lightPos.Add({ 0.0f, 100.0f, 100.0f });
	GraphicsEngine().GetShadowMap().SetLightPosition(lightPos);
	GraphicsEngine().GetShadowMap().SetLightTarget(m_position);

}
void Player::Render(CRenderContext& rc) 
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}