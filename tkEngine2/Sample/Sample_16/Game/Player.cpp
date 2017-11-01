#include "stdafx.h"
#include "Player.h"
#include "tkEngine/light/tkDirectionLight.h"

Player::Player()
{
}


Player::~Player()
{
}
bool Player::Start()
{
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,			//���a�B 
		50.0f,			//�����B
		-980.0f,		//�d�́A
		m_position		//�����ʒu�B
	);
	//�A�j���[�V�������������B
	InitAnimation();

	//�@���}�b�v�����[�h�B
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_N.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_S.dds");
	m_wnormalMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_N.dds");
	m_wspecularMapSRV.CreateFromDDSTextureFromFile(L"modelData/Thethief_wuqi_S.dds");

	int materialID = 1;
	//�}�e���A��ID��ݒ�
	m_skinModel.FindMaterial([&](auto material) {
		material->SetMaterialID(materialID);
		if (material->EqualMaterialName(L"bodyMat")) {
			//�̂̃}�e���A���B
			material->SetNormalMap(m_normalMapSRV.GetBody());
			material->SetSpecularMap(m_specularMapSRV.GetBody());
		}
		else if (material->EqualMaterialName(L"weapon")) {
			//����B
			material->SetNormalMap(m_wnormalMapSRV.GetBody());
			material->SetSpecularMap(m_wspecularMapSRV.GetBody());
		}
	});
	//�L�������C�g�𐶐��B
	m_directionLig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̐F��ݒ�B
	m_directionLig->SetColor({ 10.5f, 1.5f, 1.5f, 1.0f });
	m_directionLig->SetLightingMaterialIDGroup(1 << materialID);
	return true;
}
void Player::InitAnimation()
{
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animationClip[enAnimationClip_idle].Load(L"animData/idle.tka");
	m_animationClip[enAnimationClip_run].Load(L"animData/run.tka");
	m_animationClip[enAnimationClip_walk].Load(L"animData/walk.tka");
	//���[�v�t���O��ݒ肷��B
	m_animationClip[enAnimationClip_idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//�A�j���[�V�������������B
	m_animation.Init(m_skinModelData, m_animationClip, enAnimationClip_num);
	//�ҋ@�A�j���[�V�����𗬂��B
	m_animation.Play(enAnimationClip_idle);
}
void Player::AnimationControl()
{
	//�A�j���[�V������i�߂�B
	m_animation.Update(GameTime().GetFrameDeltaTime());
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 200.0f;	//�������ւ̈ړ����x�����B
	m_moveSpeed += cameraRight * lStick_x * 200.0f;		//�E�����ւ̈ړ����x�����Z�B

	if (Pad(0).IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
	) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
		m_charaCon.Jump();		//�L�����N�^�[�R���g���[���[�ɃW�����v�������Ƃ�ʒm����B
	}
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_moveSpeed.x,  m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY, angle);
}
void Player::Update()
{
	//�ړ������B
	Move();
	//���񏈗��B
	Turn();
	//�A�j���[�V�����R���g���[���B
	AnimationControl();
	//���[���h�s����X�V�B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 90.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳�p�̉�]�N�H�[�^�j�I�����v�Z�B
	//qRot��]�ƃL�����̉�]����Z���č�������B
	qRot.Multiply(m_rotation, qRot);
	m_skinModel.Update(m_position, qRot, CVector3::One);
	//�L�����ɂ͏��D���C�g�𓖂Ă�
	if (m_directionLig) {
		m_directionLig->SetDirection(MainCamera().GetForward());
		static CVector3 lightColorSeed = { 1.0f, 0.5f, 0.0f };
		lightColorSeed.x = fmod(lightColorSeed.x + 0.05f, CMath::PI);
		lightColorSeed.y = fmod(lightColorSeed.y + 0.05f, CMath::PI);
		lightColorSeed.z = fmod(lightColorSeed.z + 0.05f, CMath::PI);
		CVector3 lightColor;
		lightColor.x = sin(lightColorSeed.x) * 30.0f;
		lightColor.y = sin(lightColorSeed.y) * 30.0f;
		lightColor.z = sin(lightColorSeed.z) * 30.0f;
		m_directionLig->SetColor(lightColor);
	}
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}