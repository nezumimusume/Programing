#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"
#include "tkEngine/light/tkDirectionLight.h"

CVector3 toPosition = {0.0f, 30.0f, 100.0f};
Game::Game()
{
}


Game::~Game()
{
}
void Game::OnDestroy()
{
	DeleteGO(&m_player);
	DeleteGO(&m_bg);
	DeleteGO(m_directionLig);
	DeleteGO(&m_gameCamera);
}
bool Game::Start()
{
	m_directionLig = NewGO<prefab::CDirectionLight>(0, nullptr);
	CVector3 lightDir = { 0.707f, -0.707f, -0.707f };
	lightDir.Normalize();
	m_directionLig->SetDirection(lightDir);
	m_directionLig->SetColor({ 100.0f, 100.0f, 100.0f, 1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);
	AddGO(0, &m_player, "Player");
	AddGO(0, &m_bg, "BackGround");
	AddGO(0, &m_gameCamera, "GameCamera");
	
	return true;
}
void Game::Update()
{
}
void Game::Render(CRenderContext& rc)
{
	(void)rc;
}