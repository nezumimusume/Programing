
#include "stdafx.h"
#include "Player.h"
#include "tkEngine/light/tkDirectionLight.h"

bool Player::Start()
{
	//モデルデータをロード。
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	m_normalMap.CreateFromDDSTextureFromFile(L"sprite/utc_nomal.dds");
	m_specMap.CreateFromDDSTextureFromFile(L"sprite/utc_spec.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		//マテリアルＩＤを設定する。
		material->SetMaterialID(enMaterialID_Chara);
		//法線マップとスペキュラマップを設定。
		material->SetNormalMap(m_normalMap.GetBody());
		material->SetSpecularMap(m_specMap.GetBody());
	});
	m_animClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/KneelDown.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animation.Init(m_skinModelData, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_idle);
	m_charaLight = NewGO<prefab::CDirectionLight>(0);
	m_charaLight->SetDirection({ 1.0f, 0.0f, 0.0f });
	m_charaLight->SetLightingMaterialIDGroup(1 << enMaterialID_Chara);
	m_charaLight->SetColor({ 300.0f, 300.0f, 300.0f, 1.0f });
	m_charaCon.Init(20.0f, 100.0f, -1800.0f, m_position);
	return true;
}
void Player::Turn()
{
	if (m_moveSpeed.LengthSq() < 0.01f) {
		return;
	}
	m_rotation.SetRotation(CVector3::Up, atan2f(m_moveSpeed.x, m_moveSpeed.z));
}
void Player::UpdateFSM()
{
	Turn();
	static float JUMP_SPEED = 530.0f;
	switch (m_state) {
	case enState_Idle:
		Move();
		if (Pad(0).IsTrigger(enButtonA)) {
			m_charaCon.Jump();
			m_moveSpeed.y = JUMP_SPEED;
			m_animation.Play(enAnimationClip_jump, 0.2f);
			m_state = enState_Jump;
		}else if (m_moveSpeed.LengthSq() > 0.0f) {
			//入力がある。
			m_animation.Play(enAnimationClip_run, 0.2f);
			m_state = enState_Run;
		}
		break;
	case enState_Run:
		Move();
		
		if (m_moveSpeed.LengthSq() < 0.01f) {
			//入力がなくなった。
			m_animation.Play(enAnimationClip_idle, 0.2f);
			m_state = enState_Idle;
		}else if (Pad(0).IsTrigger(enButtonA)) {
			m_charaCon.Jump();
			m_moveSpeed.y = JUMP_SPEED;
			m_animation.Play(enAnimationClip_jump, 0.2f);
			m_state = enState_Jump;
		}
		break;
	case enState_Jump:
		if (!m_charaCon.IsJump()) {
			m_animation.Play(enAnimationClip_idle, 0.2f);
			m_state = enState_Idle;
		}
		break;
	case enState_GameOver:
		break;
	}
}
void Player::Move()
{
	static float MOVE_SPEED = 600.0f;
	float x = Pad(0).GetLStickXF();
	float y = Pad(0).GetLStickYF();

	CVector3 moveForwardXZ = MainCamera().GetForward();
	CVector3 moveRightXZ = MainCamera().GetRight();
	moveForwardXZ.y = 0.0f;
	moveForwardXZ.Normalize();
	moveRightXZ.y = 0.0f;
	moveRightXZ.Normalize();
	moveForwardXZ *= y * MOVE_SPEED;
	moveRightXZ *= x * MOVE_SPEED;

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += moveForwardXZ;
	m_moveSpeed += moveRightXZ;
}
void Player::Update()
{
	
	UpdateFSM();
	//キャラライトはカメラの方向にする。
	m_charaLight->SetDirection(MainCamera().GetForward());
	m_animation.Update(GameTime().GetFrameDeltaTime());
	CQuaternion qRot = CQuaternion::Identity;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//寝てるので起こす。
													//ワールド行列を更新。

	//キャラクタを移動させる。
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	CQuaternion q = m_rotation;
	q.Multiply(qRot);
	m_skinModel.Update(m_position, q, CVector3::One);
}
void Player::OnDestroy()
{
	DeleteGO(m_charaLight);
}

void Player::Render(CRenderContext& rc)
{
	//描画。
	m_skinModel.Draw(
		rc, 
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix()
	);

}