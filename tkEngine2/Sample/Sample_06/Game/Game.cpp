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
	m_skinModelData.Load(L"modelData/unityChan.cmo");
	m_skinModel.Init(m_skinModelData);
	//テクスチャをロード。
	m_texture.CreateFromDDSTextureFromFile(L"sprite/mikyan.dds");
	m_sprite.Init(m_texture, 400, 300);
	return true;
}
void Game::Update()
{
	//ワールド行列の更新。
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	m_sprite.Update({-200.0f, 200.0f, 1.0f}, CQuaternion::Identity, CVector3::One);
}
void Game::PostRender(CRenderContext& rc)
{
	//スプライトを描画。
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
void Game::Render(CRenderContext& rc)
{
	//モデルを描画。
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}