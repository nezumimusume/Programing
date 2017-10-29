#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"

Game::Game()
{
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	//ディレクションライトをシーンに追加。
	m_directionLight = NewGO<prefab::CDirectionLight>(0);
	m_directionLight->SetDirection({ 0.707f, -0.707f, 0.0f });
	m_directionLight->SetColor({ 100.5f, 100.5f, 100.5f, 1.0f });

}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 50.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 250.0f, 350.0f });
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().Update();

	m_player = NewGO<Player>(0, "Player");
	m_background = NewGO<Background>(0);
	m_gameCamera = NewGO<GameCamera>(0);
	//シーンライトを初期化。
	InitSceneLight();
	CVector3 dir = { 1.0f, -1.0f, -1.0f };
	dir.Normalize();
	GraphicsEngine().GetShadowMap().SetLightDirection(dir);
	return true;
}
void Game::OnDestroy() 
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_directionLight);
	DeleteGO(m_gameCamera);
}
void Game::Update()
{
}
void Game::Render(CRenderContext& rc)
{
}