#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player.h"
#include "Background.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//�f�B���N�V�������C�g(���z���݂����Ȃ���)���V�[���ɒǉ��B
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection(m_lightDir);
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });


	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 15.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 15.0f, 30.0f });
	MainCamera().Update();
	//�v���C���[�̃C���X�^���X�𐶐�����B
	m_player = NewGO<Player>(0);
	//�w�i�̃C���X�^���X�𐶐�����B
	m_background = NewGO<Background>(0);
	return true;
}
/*!
*@brief	�폜�����Ƃ��ɌĂ΂��B
*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
* �f�X�g���N�^���O�Ɏ��s����܂��B
*/
void Game::OnDestroy()
{
	DeleteGO(m_player);
}
void Game::Update()
{
}