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
	skinModelData.Load(L"modelData/unityChan.cmo");
	skinModel.Init(skinModelData);


	return true;
}
void Game::Update()
{
	skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Game::Render(CRenderContext& rc)
{
	skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}