#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "BackGround/BackGround.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Enemy\Enemy.h"

CVector3 toPosition = {0.0f, 30.0f, 100.0f};
Game::Game()
{
}


Game::~Game()
{
}
void Game::OnDestroy()
{
	for (auto enemy : m_enemyList) {
		DeleteGO(enemy);
	}
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
	m_directionLig->SetColor({ 1.4f, 1.4f, 1.4f, 1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);
	LightManager().SetAmbientLight({ 0.2f, 0.2f, 0.2f });
	AddGO(0, &m_player, "Player");
	
	CSkeleton enemyLoc;
	enemyLoc.Load(L"loc/enemyLoc.tks");
	for (int i = 1; i < enemyLoc.GetNumBones(); i++) {
		//先頭はダミー。
		auto bone = enemyLoc.GetBone(i);
		auto enemy = NewGO<Enemy>(0, "Enemey");
		const auto& mat = bone->GetBindPoseMatrix();
		auto pos = CVector3::Zero;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2] + 10.0f;
		pos.z = -mat.m[3][1];
		m_enemyList.push_back(enemy);
		enemy->SetPosition(pos);
	}

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