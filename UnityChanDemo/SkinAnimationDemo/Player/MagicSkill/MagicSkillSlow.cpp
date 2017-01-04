/*!
 * @brief	時間操作系(周りの速度を遅く)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillSlow.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "tkEngine/Sound/tkSoundSource.h"

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
	g_enemyManager->SetFrameDeltaTimeMul(0.3f);
	MotionBlur().SetEnable(true);
	SepiaFilter().SetEnalbe(true);
	//終了処理が走っているかもしれないので削除。
	DeleteGO(&m_finish);
}
void MagicSkillSlow::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	MotionBlur().SetEnable(false);
	//ここでもマスクを描画しないと１フレームだけマスクがない状態で描画されてしまう。
	SepiaFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	//終了処理をゲームオブジェクトマネージャーに登録。
	AddGO(0, &m_finish);
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

