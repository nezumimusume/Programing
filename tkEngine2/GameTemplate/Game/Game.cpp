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
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(30.0f);
	MainCamera().SetPosition({ 0.0f, 10.0f, 20.0f });
	MainCamera().Update();
	
	//モデルデータをロード。
	skinModelData.Load(L"modelData/unityChan.cmo");
	skinModel.Init(skinModelData);
	
	return true;
}
void Game::Update()
{
	static float angle = 0.0f;
	
	angle += 0.01f;
	/*CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, angle);
	skinModel.Update(CVector3::Zero, qRot, {0.1f, 0.1f, 0.1f});*/
	skinModel.Update(CVector3::Zero, CQuaternion::Identity, { 0.1f, 0.1f, 0.1f });
}
void Game::Render(CRenderContext& rc)
{
	skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}