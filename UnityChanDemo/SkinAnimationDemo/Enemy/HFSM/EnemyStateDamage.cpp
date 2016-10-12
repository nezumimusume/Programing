/*!
 * @brief	ヤラレ状態。
 */
#include "stdafx.h"
#include "Enemy/HFSM/EnemyStateDamage.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "GameCamera.h"

namespace {
	SParicleEmitParameter emitterParam =
	{
		"Assets/effect/Eff_water_2.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3(1.5f, 0.0f, 0.0f),		//CVector3	initVelocity;						//!<初速度。
		2.0f,						//float		life;								//!<寿命。単位は秒。
		0.01f,							//float		intervalTime;						//!<発生時間。単位は秒。
		0.5f,							//float		w;									//!<パーティクルの幅。
		0.5f,							//float		h;									//!<パーティクルの高さ。
		CVector3(0.0f, 0.1f, 0.0f),		//CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3(0.0f, 0.2f, 0.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		{											//!<CVector4	uvTable[4];			UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
		CVector4(0.5f,  0.0f, 0.75f, 0.5f),
		CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3(0.0f, 0.0f, 0.0f),	//CVector3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		0.5f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		2.0f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	};
}
/*!
 * @brief	コンストラクタ。
 */
EnemyStateDamage::EnemyStateDamage(Enemy* enemy) :
	IEnemyState(enemy),
	dmgCollisionGroupID(0),
	particleEmitter(NULL)
{
}
/*!
 * @brief	デストラクタ。
 */
EnemyStateDamage::~EnemyStateDamage()
{
}
void EnemyStateDamage::Update() 
{
	//enemy->PlayAnimation(Enemy::enAnimDamage);
	enemy->SetMoveSpeed(0.0f);
}
void EnemyStateDamage::Enter(const SEnterArg& enterArg)
{
	IEnemyState::Enter(enterArg);
	dmgCollisionGroupID = enterArg.arg[0];
	enemy->PlayAnimationForce(Enemy::enAnimDamage);
	//パーティクルエミッターを登録。
	particleEmitter = NewGO<CParticleEmitter>(0);
	particleEmitter->Init(g_random, g_camera->GetCamera(), emitterParam, enemy->GetPosition());
}
void EnemyStateDamage::Leave()
{
}
