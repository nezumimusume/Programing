#include "stdafx.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"


TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}
void TitleScene::OnDestroy()
{
	DeleteGO(&bgmSoundSource);
}
void TitleScene::Update()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		DeleteGO(this);
		NewGO<GameScene>(0);
	}
}
bool TitleScene::Start()
{
	bgmSoundSource.InitStreaming("Assets/sound/titleBgm.wav");
	bgmSoundSource.Play(true);
	AddGO(0, &bgmSoundSource);
	return true;
}