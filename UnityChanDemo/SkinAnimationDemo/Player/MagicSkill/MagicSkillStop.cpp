/*!
 * @brief	時間操作系(時間停止)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillStop.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"

void MagicSkillStop::MagicSkillStopFinish::Update()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = blendRate - 4.0f * GameTime().GetFrameDeltaTime();
	

	if (blendRate < 0.0f) {
		//終わり。
		DeleteGO(this);
		MonochromeFilter().SetEnalbe(false);
	}
	else {
		MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
			//プレイヤーをレンダリングしてマスクを作成する。
			g_player->Render(renderContext);
			for (auto& e : g_enemyManager->GetEnemyList()) {
				e->Render(renderContext);
			}
		});
		MonochromeFilter().SetBlendRate(blendRate);
	}
}
MagicSkillStop::MagicSkillStop(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillStop::~MagicSkillStop()
{
}
void MagicSkillStop::OnChangeMagic()
{
}
void MagicSkillStop::OnStartMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	MotionBlur().SetEnable(true);
	MonochromeFilter().SetEnalbe(true);
	//終了処理が走っているかもしれないので削除。
	DeleteGO(&m_finish);
//	MonochromeFilter().SetBlendRate(0.0f);
}
void MagicSkillStop::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	//終了処理をゲームオブジェクトマネージャーに登録。
	AddGO(0, &m_finish);
	//ここでもマスクを描画しないと１フレームだけマスクがない状態で描画されてしまう。
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	MotionBlur().SetEnable(false);
}
void MagicSkillStop::OnUsingMagicSkill()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = min(1.0f, blendRate + 4.0f * GameTime().GetFrameDeltaTime());
	MonochromeFilter().SetBlendRate(blendRate);
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext){
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
}

