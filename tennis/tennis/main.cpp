#include "stdafx.h"
#include "lib/system.h"
#include "main.h"
#include "GameCamera.h"

Game* game = NULL;

//コンストラクタ。
Game::Game()
{

}
//デストラクタ。
Game::~Game()
{
	delete gameCamera;
}
//Updateが呼ばれる前に一度だけ呼ばれる処理。
void Game::Start()
{
	gameCamera = new GameCamera;
	court.Init();
	player.Init();
	ball.Init();
}
//描画。
void Game::Render(CRenderContext& renderContext)
{
	court.Render(renderContext);
	player.Render(renderContext);
	ball.Render(renderContext);
}
//更新。
void Game::Update()
{
	//ゲームカメラの更新。
	gameCamera->Update();
	player.Update();
	ball.Update();
}
