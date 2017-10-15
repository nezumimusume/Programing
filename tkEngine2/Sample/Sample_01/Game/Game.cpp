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
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	//���f���f�[�^�����[�h�B
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	return true;
}
void Game::Update()
{
	//�㉺���E�̃L�[���͂ɂ��ړ������B
	if (Pad(0).IsPress(enButtonRight)) {
		m_position.x -= 5.0f;
	}
	else if (Pad(0).IsPress(enButtonLeft)) {
		m_position.x += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonUp)) {
		m_position.y += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonDown)) {
		m_position.y -= 5.0f;
	}
	//�A�i���O�X�e�B�b�N�ɂ��ړ������B
	CVector3 stick;
	
	stick.x = -Pad(0).GetLStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stick.y = Pad(0).GetLStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stick.z = 0.0f;
	m_position += stick * 5.0f;

	//���[���h�s����X�V�B
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	//�`��B
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}