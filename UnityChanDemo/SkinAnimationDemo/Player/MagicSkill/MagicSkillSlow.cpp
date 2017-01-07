/*!
 * @brief	時間操作系(周りの速度を遅く)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillSlow.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "Scene/gameScene.h"
#include "Map/Sky.h"

void MagicSkillSlow::MagicSkillStopFinish::Update()
{
	float blendRate = SepiaFilter().GetBlendRate();
	blendRate = blendRate - 4.0f * GameTime().GetFrameDeltaTime();
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	if (blendRate < 0.0f) {
		//終わり。
		DeleteGO(this);
		SepiaFilter().SetEnalbe(false);
	}
	else {
		SepiaFilter().SetBlendRate(blendRate);
	}
}

MagicSkillSlow::MagicSkillSlow(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillSlow::~MagicSkillSlow()
{
}
void MagicSkillSlow::OnChangeMagic()
{
}
void MagicSkillSlow::OnStartMagic()
{
	//鼓動音を再生
	CSoundSource* s = NewGO<CSoundSource>(0);
	s->Init("Assets/Sound/heartbeat.wav");
	s->Play(false);
	const float deltaTimeMul = 0.3f;
	g_enemyManager->SetFrameDeltaTimeMul(deltaTimeMul);
	gameScene->GetSky()->SetFrameDeltaTimeMul(deltaTimeMul);
	SepiaFilter().SetEnalbe(true);
	
	auto pauseSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Pause();
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		pauseSound
	);
	
	//終了処理が走っているかもしれないので削除。
	DeleteGO(&m_finish);
}
void MagicSkillSlow::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	gameScene->GetSky()->SetFrameDeltaTimeMul(1.0f);
	//終了処理をゲームオブジェクトマネージャーに登録。
	AddGO(0, &m_finish);
	//ここでもマスクを描画しないと１フレームだけマスクがない状態で描画されてしまう。
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	
	auto resumeSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Play(s->GetLoopFlag());
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		resumeSound
	);
}
void MagicSkillSlow::OnUsingMagicSkill()
{
	float blendRate = SepiaFilter().GetBlendRate();
	blendRate = min(1.0f, blendRate + 4.0f * GameTime().GetFrameDeltaTime());
	SepiaFilter().SetBlendRate(blendRate);
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
}

