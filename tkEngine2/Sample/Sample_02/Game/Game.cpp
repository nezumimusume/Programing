#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 15.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 15.0f, 40.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	return true;
}
void Game::Update()
{
	//�N�H�[�^�j�I����P�ʃN�H�[�^�j�I���ŏ���������B
	CQuaternion qRot = CQuaternion::Identity;
	//�㉺���E�̃L�[���͂ɂ���]�����B
	if (Pad(0).IsPress(enButtonRight)) {
		//Y�������2�x�񂷁B
		qRot.SetRotationDeg(CVector3::AxisY, 2.0f);
	}
	else if (Pad(0).IsPress(enButtonLeft)) {
		//Y�������-2�x�񂷁B
		qRot.SetRotationDeg(CVector3::AxisY, -2.0f);
	}
	else if (Pad(0).IsPress(enButtonUp)) {
		qRot.SetRotationDeg(CVector3::AxisX, 2.0f);
	}
	else if (Pad(0).IsPress(enButtonDown)) {
		qRot.SetRotationDeg(CVector3::AxisX, -2.0f);
	}
	//��]�����Z����B
	m_rotation.Multiply(qRot);

	//�A�i���O�X�e�B�b�N�ɂ���]�����B
	CVector3 stick;
	stick.x = -Pad(0).GetLStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stick.y = Pad(0).GetLStickYF();		//�A�i���O�X�e�B�b�N��y�̓��͗ʂ��擾�B
	stick.z = 0.0f;
	qRot.SetRotationDeg(CVector3::AxisY, stick.x * 2.0f);
	//��]�����Z����B
	m_rotation.Multiply(qRot);

	qRot.SetRotationDeg(CVector3::AxisX, stick.y * 2.0f);
	//��]�����Z����B
	m_rotation.Multiply(qRot);
	

	//���[���h�s����X�V�B
	m_skinModel.Update(CVector3::Zero, m_rotation, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	//�`��B
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}