/*!
 * @brief	ヤラレ状態。
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDeath.h"
#include "ParticleParam.h"

/*!
 * @brief	コンストラクタ。
 */
EnemyStateDeath::EnemyStateDeath( Enemy* enemy ) :
	IEnemyState(enemy),
	timer(0.0f)
{
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateDeath::~EnemyStateDeath()
{
}
void EnemyStateDeath::Update() 
{
	enemy->PlayAnimation(Enemy::enAnimDeath);
	enemy->SetMoveSpeed(0.0f);
	timer += GameTime().GetFrameDeltaTime();
	if(timer > 1.0f){
		for (auto& p : particleEmitterList) {
			DeleteGO(p);
		}
		particleEmitterList.clear();
	}
}
void EnemyStateDeath::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
	CMatrix* m = enemy->FindBoneWorldMatrix("Bip001_Neck");
	if (m == NULL) {
		//仮カリカリ
		m = enemy->FindBoneWorldMatrix("spine");
	}
	if (m != NULL) {
		//パーティクルエミッターを登録。
		for (SParicleEmitParameter& param : bloodEmitterParam) {
			CParticleEmitter* particleEmitter = NewGO<CParticleEmitter>(0);
			CVector3 pos;
			pos.Set(m->m[3][0], m->m[3][1], m->m[3][2]);
			particleEmitter->Init(g_random, g_camera->GetCamera(), param, pos);
			particleEmitterList.push_back(particleEmitter);
		}
	}
	timer = 0.0f;
}
void EnemyStateDeath::Leave()
{
	for (auto& p : particleEmitterList) {
		DeleteGO(p);
	}
	particleEmitterList.clear();
}
