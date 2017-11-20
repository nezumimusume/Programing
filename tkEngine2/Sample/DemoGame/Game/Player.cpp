
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/sound/tkSoundSource.h"

namespace {
	const CVector3 START_POS = { -1088.16589f, 67.87, -567.0f };
}
class CSoundEmitter : public IGameObject {
private:
	float m_timer = 0.0f;
	float m_emitTime = 0.0f;
	std::string m_filePath;
public:
	void Init(float emitTime, const char* filePath)
	{
		m_emitTime = emitTime;
		m_filePath = filePath;
	}
	void Update()
	{
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > m_emitTime) {
			prefab::CSoundSource* s = NewGO<prefab::CSoundSource>(0);
			s->Init(m_filePath.c_str());
			s->Play(false);
			DeleteGO(this);
		}
	}
};
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
	m_animClip[enAnimationClip_Clear].Load(L"animData/Clear.tka");
	for (auto& animClip : m_animClip) {
		animClip.SetLoopFlag(true);
	}
	m_position = START_POS;
	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_Clear].SetLoopFlag(false);
	m_animation.Init(m_skinModelData, m_animClip, enAnimationClip_num);
	m_animation.Play(enAnimationClip_idle);
	m_charaLight = NewGO<prefab::CDirectionLight>(0);
	m_charaLight->SetDirection({ 1.0f, 0.0f, 0.0f });
	m_charaLight->SetLightingMaterialIDGroup(1 << enMaterialID_Chara);
	m_charaLight->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	m_charaCon.Init(20.0f, 78.0f, -1800.0f, m_position);
	m_game = FindGO<Game>("Game");
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
	if (m_position.y < -1000.0f && !m_game->IsGameOver() ) {
		//初期位置に戻る。
		Game* game = FindGO<Game>("Game");
		game->NotifyGameOver();
	}
	static float JUMP_SPEED = 630.0f;
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
	case enState_GameOver: {
		if (!m_animation.IsPlaying()) {
			m_game->NotifyRestart();
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

	}break;
	case enState_WaitStartGameClear:
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer > 0.5f) {
			m_animation.Play(enAnimationClip_Clear);
			CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
			emitter->Init(0.3f, "sound/uni1518.wav");
			m_state = enState_GameClear;
			m_timer = 0.0f;
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		break;
	case enState_GameClear: {
		
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}break;
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
	//キャラクタを移動させる。
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	
	//キャラライトはカメラの方向にする。
	m_charaLight->SetDirection(MainCamera().GetForward());
	CQuaternion qRot = CQuaternion::Identity;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//寝てるので起こす。
													//ワールド行列を更新。
	CQuaternion q = m_rotation;
	q.Multiply(qRot);
	m_skinModel.Update(m_position, q, CVector3::One);
	m_animation.Update(GameTime().GetFrameDeltaTime());

	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}

void Player::NotifyGameOver()
{
	m_animation.Play(enAnimationClip_KneelDown);
	CSoundEmitter* emitter = NewGO<CSoundEmitter>(0);
	emitter->Init(0.6f, "sound/uni1482.wav");
	m_state = enState_GameOver;
}

void Player::NotifyGameClear()
{
	m_state = enState_WaitStartGameClear;
}
void Player::NotifyRestart()
{
	m_animation.Play(enAnimationClip_idle);
	m_state = enState_Idle;
	m_position = START_POS;
	m_charaCon.SetPosition(m_position);
	m_moveSpeed = CVector3::Zero;
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