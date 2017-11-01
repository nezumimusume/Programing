#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "tkEngine/light/tkPointLight.h"
#include "GameCamera.h"

Game::Game()
{
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	CSkeleton ligLoc;
	ligLoc.Load(L"loc/light.tks");
	for (int i = 1; i < ligLoc.GetNumBones(); i++) {
		CBone* bone = ligLoc.GetBone(i);
		prefab::CPointLight* ptLig = NewGO<prefab::CPointLight>(0);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		ptLig->SetPosition(pos);
		ptLig->SetColor({
			200.0f,
			200.0f,
			100.0f,
			1.0f
		});
		ptLig->SetAttn({
			550.0f,
			3.0f,
			0.1f
		});
		m_pointLight.push_back(ptLig);
	}

}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 50.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 300.0f, 300.0f });
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

	Enemy* enemy = NewGO <Enemy>(0);
	m_enemyList.push_back(enemy);
	return true;
}
void Game::OnDestroy() 
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	for (auto pt : m_pointLight) {
		DeleteGO(pt);
	}
	DeleteGO(m_gameCamera);
}
void Game::Update()
{
}
void Game::Render(CRenderContext& rc)
{
}