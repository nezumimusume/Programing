#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"
#include "GameOverControl.h"
#include "GameClearControl.h"
#include "star.h"
#include "StarRenderer.h"
#include "PlayerSilhouette.h"

Game::Game()
{
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	//ライトを配置。
	CVector3 dir = { 1.0f, -1.0f, -1.0f };
	dir.Normalize();
	m_directionLight = NewGO<prefab::CDirectionLight>(0);
	m_directionLight->SetDirection(dir);
	m_directionLight->SetColor({30.0f, 30.0f, 30.0f, 1.0f});
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
#if 0 //@todo 物理ベースの時のライト。
			400.0f,
			400.0f,
			100.0f,
#else
			100.0f,
			100.0f,
			10.0f,
#endif
			
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
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
	//シーンライトを初期化。
	InitSceneLight();
	//プレイヤーのシルエットを作成。
	m_playerSilhouette = NewGO<PlayerSilhouette>(0);

	//敵を配置
	CSkeleton enemyLoc;
	enemyLoc.Load(L"loc/enemy.tks");
	for (int i = 1; i < enemyLoc.GetNumBones(); i++) {
		CBone* bone = enemyLoc.GetBone(i);
		Enemy* enemy = NewGO <Enemy>(0);
		m_enemyList.push_back(enemy);
		enemy->SetTags(enGameObject_Enemy);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		enemy->SetPosition(pos);
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"pathData/enemy0%d_path.tks", i);
		enemy->Init(moveFilePath);
	}

	//星を配置
	CSkeleton starLoc;
	starLoc.Load(L"loc/star.tks");
	//星のレンダラーを作成。
	m_starRenderer = NewGO<StarRenderer>(0);
	m_starRenderer->Init(starLoc.GetNumBones() - 1);
	for (int i = 1; i < starLoc.GetNumBones(); i++) {
		CBone* bone = starLoc.GetBone(i);
		Star* star = NewGO <Star>(0);
		star->Init(*m_starRenderer);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		star->SetPosition(pos);
		star->SetTags(enGameObject_Star);	//タグを設定。
	}

	GraphicsEngine().GetShadowMap().SetLightDirection(m_directionLight->GetDirection());
	m_bgmSource = NewGO<prefab::CSoundSource>(0);
	m_bgmSource->Init("sound/normalBGM.wav");
	m_bgmSource->Play(true);

	//タイマー用のフォントを初期化。
	m_timerFont = std::make_unique<DirectX::SpriteFont>(
		GraphicsEngine().GetD3DDevice(),
		L"font/hato_pop.spritefont"
	);
	m_fontTest.SetFont(m_timerFont.get());
	m_fontTest.SetShadowParam(true, 2.0f, CVector4::Black);

	m_scoreFontPosition.x = -620.0f ;
	m_scoreFontPosition.y = 280.0f;
	return true;
}
void Game::OnDestroy() 
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	for (auto pt : m_pointLight) {
		DeleteGO(pt);
	}
	for (auto enemy : m_enemyList) {
		DeleteGO(enemy);
	}
	DeleteGO(m_gameCamera);
	DeleteGO(m_bgmSource);
	//Starを削除。
	FindGameObjectsWithTag(enGameObject_Star, [](IGameObject* go) {
		DeleteGO(go);
	});
	DeleteGO(m_gameClearControl);
	//ゲーム再起動。
	NewGO<Game>(0, "Game");
	
}
void Game::NotifyGameOver()
{
	if (m_isGameClear) {
		return;
	}
	m_isGameOver = true;
	
	//ゲームオーバー制御を作成。
	m_gameOverControl = NewGO<GameOverControl>(0);
}
void Game::NotifyRestart()
{
	m_isGameOver = false;
	m_gameCamera->NotifyRestart();
	m_player->NotifyRestart();
	for (auto& enemy : m_enemyList) {
		enemy->NotifyRestart();
	}
	m_waitTimer = 0.0f;
	GraphicsEngine().GetTonemap().Reset();
	DeleteGO(m_gameOverControl);
}
void Game::Update()
{
	m_waitTimer += GameTime().GetFrameDeltaTime();
	if (m_waitTimer < 0.1f) {
		//ゲームが開始して0.1秒経過するまでトーンマップの明暗順応はやらない。
		GraphicsEngine().GetTonemap().Reset();
	}
	m_timer = max( 0.0f, m_timer - GameTime().GetFrameDeltaTime() );
	//クリア判定
	int coinCount = 0;
	FindGameObjectsWithTag(enGameObject_Star, [&](IGameObject* go) {
		coinCount++;
	});
	if ((coinCount == 0 || m_timer <= 0.0f) 
		&& !m_isGameClear 
		&& !m_isGameOver
		&& m_player->IsPossibleClear()
	) {
		//全部のコインを取った。
		m_isGameClear = true;
		//ゲームクリア制御を作成。
		m_gameClearControl = NewGO<GameClearControl>(0);
		m_timer = 0.0f;
	}
	

}
void Game::Render(CRenderContext& rc)
{
}
void Game::PostRender(CRenderContext& rc) 
{
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, L"%02d:%02d", minute, sec);
	m_fontTest.Begin();
	
	//文字を描画。
	m_fontTest.Draw(
		L"TIME ", 
		{ -620.0f, 340.0f }, 
		{ 1.0f, 0.0f, 0.0f, 1.0f }, 
		0.0f, 
		0.8f, 
		{ 0.0f, 1.0f}
	);
	m_fontTest.Draw(
		text,
		{ -465.0f, 340.0f }, 
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		0.8f,
		{ 0.0f, 1.0f }
	);

	//コインの取得枚数を表示。
	swprintf_s(text, L"STAR %04d", m_coinCount);
	m_fontTest.Draw(
		text,
		m_scoreFontPosition,
		{ 1.0f, 1.0f, 0.0f, 1.0f },
		0.0f,
		m_scoreFontScale,
		{ 0.0f, 1.0f }
	);

	m_fontTest.End();
}