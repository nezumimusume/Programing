#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "tkEngine/sound/tkSoundSource.h"

GameScene::GameScene()
{
	bgmSource = NULL;
	bgmSource = NewGO<CSoundSource>(0);
	bgmSource->Init("Assets/sound/bgm.wav");
	bgmSource->Play(true);
}
GameScene::~GameScene()
{
	//ちゃんと削除しないと音が消えないよ。
	DeleteGO(bgmSource);
}
bool GameScene::Start() 
{
	return true;
}
void GameScene::Update()
{
	if (Pad(0).IsPress(enButtonA)) {
		//Aボタンが押されたらタイトルシーンに遷移する。
		NewGO<TitleScene>(0);
		DeleteGO(this);
	}
}
