/*!
 *@brief	タイトルシーン。
 */
#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}
bool TitleScene::Start()
{
	texture.Load("Assets/sprite/titleBG.png");	
	sprite.Init(&texture);
	return true;
}
void TitleScene::Update()
{
	if (Pad(0).IsPress(enButtonStart)) {
		//スタートボタンが押されたらゲームシーンに遷移する。
		//GameSceneのインスタンスを生成。
		NewGO<GameScene>(0);
		//TitleSceneのインスタンスを削除。
		DeleteGO(this);
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	sprite.Draw(renderContext);
}