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
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	//モデルデータをロード。
	skinModelData.Load(L"modelData/Doragon.cmo");
	skinModel.Init(skinModelData);
	m_animClip[0].Load(L"animData/idle.tka");
	m_animClip[0].SetLoopFlag(true);
	m_animation.Init(skinModelData, m_animClip, 1);
	m_animation.Play(0);
	return true;
}
void Game::Update()
{
	m_animation.Update(GameTime().GetFrameDeltaTime());
	skinModel.Update(CVector3::Zero, CQuaternion::Identity, {0.1f, 0.1f, 0.1f});
}
void Game::Render(CRenderContext& rc)
{
	skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}