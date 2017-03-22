#include "stdafx.h"
#include "Player.h"
#include "Car.h"
#include "Map/Ground.h"
#include "tkEngine/graphics/material/tkSkinModelMaterial.h"
#include "DamageCollisionWorld.h"
#include "ParticleParam.h"
#include "Enemy/EnemyParameter.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "Enemy/EnemyManager.h"
#include "HUD/LockOn2D.h"
#include "Scene/GameScene.h"


namespace {
	const float RECOVER_MP = 20.0f;			//MP自然回復量。

	const float RUN_THREADHOLD_SQ = 4.0f * 4.0f;		//走りアニメーションを再生する速度の閾値。
	//アニメーションのイベントテーブル。
	AnimationEventGroup animationEventGroupTbl[Player::NumAnimation] = {
		//AnimationStand
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationWalk
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationRun
		{
			EMIT_SOUND_EVENT(0.4f, 1.0f, "Assets/sound/Footstep_00.wav"),
			EMIT_SOUND_EVENT(0.9f, 1.0f, "Assets/sound/Footstep_00.wav"),
			END_ANIMATION_EVENT(),
		},
		//AnimationJump
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_00
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.4f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.48f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.56f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			EMIT_SOUND_EVENT(0.3f, 0.5f, "Assets/sound/PlayerAttack_00.wav"),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_01
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.4f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.48f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.56f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			EMIT_SOUND_EVENT(0.3f, 0.5f, "Assets/sound/PlayerAttack_00.wav"),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_02
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.3f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.31f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.32f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.33f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.34f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.35f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.36f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.37f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.38f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.39f, 0.35f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),

			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.3f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.31f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.32f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.33f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.34f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.35f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.36f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.37f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.38f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.39f, 0.35f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_SOUND_EVENT(1.2f, 0.5f, "Assets/sound/PlayerAttack_01.wav"),
			END_ANIMATION_EVENT(),
		},
		//AnimationDamage
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationDeath
		{
			EMIT_SOUND_EVENT(0.0f, 0.75f, "Assets/sound/PlayerDead.wav"),
			END_ANIMATION_EVENT(),
		},
	};
}

Player::Player() :
	position(CVector3::Zero),
	isUpdateAnim(false),
	attackState(this),
	standState(this),
	damageState(this),
	deadState(this),
	runState(this),
	magicSkillDash(this),
	magicSkillSlow(this, SepiaFilter(), 0.3f, 50.0f),
	magicSkillStop(this, MonochromeFilter(), 0.0f, 100.0f),
	magicSkillStealth(this)
{
	pCurrentMagicSkill = &magicSkillDash;
	memset(battleSeats, 0, sizeof(battleSeats));
}
Player::~Player()
{
	DeleteGO(lockOn2D);
}
/*!
* @brief	開始
*/
bool Player::Start()
{
	switch (initStep) {
	case InitStep_LoadModelData:
		skinModelData.LoadModelDataAsync("Assets/modelData/Player.X", &animation);
		initStep = InitStep_WaitModelData;
		break;
	case InitStep_WaitModelData:
		if (skinModelData.IsLoadEnd()) {
			//スキンモデルの読み込み完了。
			lockOn2D = NewGO<LockOn2D>(1);

			//体のマテリアルを取得。
			CSkinModelMaterial* mat = skinModelData.GetBody()->FindMaterial("Thethief_D.tga");
			
			if (mat != NULL) {
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_NormalMap, *TextureResources().Load("Assets/modelData/Thethief_N.tga"));
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_SpecularMap, *TextureResources().Load("Assets/modelData/Thethief_S.tga"));
			}
			//武器のマテリアルを取得。
			mat = skinModelData.GetBody()->FindMaterial("Thethief_wuqi_D.tga");
			if (mat != NULL) {
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_NormalMap, *TextureResources().Load("Assets/modelData/Thethief_wuqi_N.tga"));
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_SpecularMap, *TextureResources().Load("Assets/modelData/Thethief_wuqi_S.tga"));
			}
			skinModel.Init(skinModelData.GetBody());
			skinModel.SetLight(&gameScene->GetDefaultLight());
			skinModel.SetHasNormalMap(true);
			skinModel.SetHasSpeculerMap(true);
			skinModel.SetShadowCasterFlag(true);
			skinModel.SetShadowReceiverFlag(true);
			skinModel.SetFresnelFlag(true);
			skinModel.SetReflectionCasterFlag(true);
			skinModel.SetWriteVelocityMap(false);

			isPointLightOn = false;
			UpdatePointLight();

			PlayAnimation(AnimationInvalid, 0.0f);
			rotation = CQuaternion::Identity;
			
			ChangeState(enStateStand);
			radius = 0.6f;
			height = 0.3f;
			characterController.Init(radius, height, position);
			characterController.SetGravity(-18.8f);
			toLampLocalPos.Set(0.0f, 1.0f, 0.5f);
			InitBattleSeats();
			//g_physicsWorld->AddRigidBody(&rigidBody);
			animation.SetAnimationEndTime(AnimationAttack_00, 0.63333f);
			animation.SetAnimationEndTime(AnimationAttack_01, 0.76666f);
			animation.SetAnimationEndTime(AnimationDamage, 0.733333f);
			animation.SetAnimationLoopFlag(AnimationJump, false);
			animation.SetAnimationLoopFlag(AnimationAttack_00, false);
			animation.SetAnimationLoopFlag(AnimationAttack_01, false);
			animation.SetAnimationLoopFlag(AnimationAttack_02, false);
			animation.SetAnimationLoopFlag(AnimationDamage, false);
			animation.SetAnimationLoopFlag(AnimationDeath, false);
			animation.PlayAnimation(AnimationStand);
			nextAttackAnimNo = AnimationInvalid;
			reqAttackAnimNo = AnimationInvalid;

			//アニメーションイベントコントローラの初期化。
			animationEventController.Init(
				&skinModel,
				&animation,
				animationEventGroupTbl,
				sizeof(animationEventGroupTbl) / sizeof(animationEventGroupTbl[0])
				);
			return true;
		}
		break;
	}
	
	return false;
}
bool Player::LockOnEnemy()
{
	bool result = false;

	CMatrix mToPlayerWorld = skinModel.GetWorldMatrix();
	mToPlayerWorld.Inverse(mToPlayerWorld);
	const std::vector<Enemy*>& enemyList = g_enemyManager->GetEnemyList();
	//ロック可能なZの閾値
	const float lockOnLen = 20.0f;		//適当。
	Enemy* nearEnemy = NULL;
	float nearLen = FLT_MAX;
	for (const auto& enemy : enemyList)
	{
		if (!enemy->IsPossibleLockOn()) {
			continue;
		}
		//敵の座標をカメラ座標系に変換する。
		CVector3 posInPlayer = enemy->GetPosition();
		mToPlayerWorld.Mul(posInPlayer);
		float lenTmp = posInPlayer.Length();
		if (lockOnLen > lenTmp) {
			//ロックオン。
			if (nearEnemy == NULL) {
				nearEnemy = enemy;
				nearLen = lenTmp;
			}
			else {
				if (lenTmp < nearLen) {
					//こいつの方が近い。
					nearEnemy = enemy;
					nearLen = lenTmp;
				}
			}
			result = true;
		}
	}
	lockOnEnemy = nearEnemy;
	return result;
}
void Player::UpdateStateMachine()
{
	if (currentState != NULL) {
		currentState->Update();
		if (currentState->IsPossibleLockOn()) {
			//ロックオン可能？
			if (!isLockOn) {
				if (Pad(0).IsTrigger(enButtonRB3)) {
					//ロックオン。
					if (LockOnEnemy()) {
						//敵をロックオンできた。
						isLockOn = true;
					}
				}
			}
			else {
				
				{
					const std::vector<Enemy*>& enemyList = g_enemyManager->GetEnemyList();
					CVector3 criteriaEnemy = lockOnEnemy->GetPosition();
					criteriaEnemy.Subtract(position);
					criteriaEnemy.Normalize();
					Enemy *nearEnemy = lockOnEnemy;
					float nearEnemyRad = 0.0f;
					//ロックオンする敵を変更
					if (Pad(0).IsTrigger(enButtonLeft))
					{
						for (Enemy *enemy : enemyList)
						{
							CVector3 enemyDirection = enemy->GetPosition();
							enemyDirection.Subtract(position);
							enemyDirection.Normalize();
							float enemyRad;
							enemyRad = criteriaEnemy.Dot(enemyDirection);
							if (0 < enemyRad)
							{
								nearEnemyRad = enemyRad;
								nearEnemy = enemy;
							}
						}
					}
					else if (Pad(0).IsTrigger(enButtonRight))
					{
						for (Enemy *enemy : enemyList)
						{
							CVector3 enemyDirection = enemy->GetPosition();
							enemyDirection.Subtract(position);
							enemyDirection.Normalize();
							float enemyRad;
							enemyRad = criteriaEnemy.Dot(enemyDirection);
							if (enemyRad < 0)
							{
								nearEnemyRad = enemyRad;
								nearEnemy = enemy;
							}
						}
					}
					lockOnEnemy = nearEnemy;
				}
				
				if (Pad(0).IsTrigger(enButtonRB3)
					|| !lockOnEnemy->IsPossibleLockOn()
				) {
					//右スティックの押し込みボタンが押された
					//または、ロックオン中のエネミーがロックオンできなくなったら
					//ロックオンを解除する。
					lockOnEnemy = NULL;
					isLockOn = false;
				}
			}
			lockOn2D->SetLockOnEnemy(lockOnEnemy);
		}
		else {
			//ロックオン不可能。
			lockOnEnemy = NULL;
			isLockOn = false;
		}
	}
	
	position = characterController.GetPosition();
}

/*!
* @brief	ヤラレ処理。
*/
void Player::Damage()
{
	isApplyDamageTrigger = false;
	if(currentState->IsPossibleDamage()){
		CRigidBody* rb = characterController.GetRigidBody();
		const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
			DamageCollisionWorld::enDamageToPlayer,
			rb->GetBody()
		);
		if (dmgColli != NULL) {
			//ダメージを受けた。
			hp -= dmgColli->damage;
			if (hp <= 0.0f) {
				//死亡
				hp = 0;
				ChangeState(enState_Dead);
				isApplyDamageTrigger = true;
			}
			else {
				ChangeState(enState_Damage);
				isApplyDamageTrigger = true;
			}
		}
	}
}
/*!
* @brief	ポイントライトを更新。
*/
void Player::UpdatePointLight()
{
	if (Pad(0).IsTrigger(enButtonLB3)) {
		isPointLightOn = !isPointLightOn;
	}

	if (isPointLightOn) {
		pointLightColor.Set(0.25f, 0.25f, 0.25f, 3.0f);
	}
	else {
		pointLightColor = CVector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	//light.SetPointLightColor(pointLightColor);
	pointLightPosition = toLampLocalPos;
	CMatrix mWorld = skinModel.GetWorldMatrix();
	mWorld.Mul(pointLightPosition);

	gameScene->GetDefaultLight().SetPointLightPosition(pointLightPosition);
	gameScene->GetDefaultLight().SetPointLightColor(pointLightColor);
}
/*!
* @brief	旋回処理。
*/
void Player::Turn()
{
	if (isLockOn) {
		CVector3 toEnemy;
		toEnemy.Subtract(lockOnEnemy->GetPosition(), position);
		rotation.SetRotation(CVector3::Up, atan2f(toEnemy.x, toEnemy.z));
	}
	else {
		CVector3 moveSpeed = characterController.GetMoveSpeed();
		moveSpeed.y = 0.0f;
		if (moveSpeed.LengthSq() > 0.001f) {
			rotation.SetRotation(CVector3::Up, atan2f(moveSpeed.x, moveSpeed.z));
		}
	}
	
}
/*!
* @brief	アニメーション再生。
*/
void Player::PlayAnimation(AnimationNo animNo, float interpolateTime)
{
	if (animation.GetPlayAnimNo() != animNo && animNo != AnimationInvalid) {
		//別のアニメーション
		animation.PlayAnimation(animNo, interpolateTime);
	}
}
/*!
* @brief	アニメーションコントロール。
*/
void Player::AnimationControl()
{
	if (characterController.IsJump()) {
		PlayAnimation(AnimationJump, 0.05f);
	}else{
		if (state == enStateRun) {
			if (characterController.GetMoveSpeed().LengthSq() > RUN_THREADHOLD_SQ) {
				//走りアニメーションを流す。
				PlayAnimation(AnimationRun, 0.1f);
			}
			else {
				//歩きアニメーション。
				PlayAnimation(AnimationWalk, 0.1f);
			}
		}
		else if (state == enStateStand) {
			//立ちアニメーションを流す。
			PlayAnimation(AnimationStand, 0.3f);
		}
		else if (state == enState_Attack) {
			if (nextAttackAnimNo == AnimationAttack_Start) {
				//攻撃開始。
				PlayAnimation(nextAttackAnimNo, 0.1f);
				reqAttackAnimNo = nextAttackAnimNo;
				nextAttackAnimNo = AnimationInvalid;
			}else if( nextAttackAnimNo != AnimationInvalid ){
				//連撃のアニメーションをリクエストキューに積む。
				animation.PlayAnimationQueue(nextAttackAnimNo, 0.05f);
				reqAttackAnimNo = nextAttackAnimNo;
				nextAttackAnimNo = AnimationInvalid;
			}
		}
		else if (state == enState_Damage) {
			if (isApplyDamageTrigger) {
				//別のアニメーション
				animation.PlayAnimation(AnimationDamage, 0.1f);
			}
		}
		else if (state == enState_Dead) {
			PlayAnimation(AnimationDeath, 0.1f);
		}
	}
	animation.Update(localFrameDeltaTime);
}
/*!
* @brief	バトルで使用するシートを初期化。
*/
void Player::InitBattleSeats()
{
	float angleBase = 2.0f * CMath::PI / NUM_BATTLE_SEAT;
	for (int i = 0; i < NUM_BATTLE_SEAT; i++) {
		battleSeats[i].seatNo = i;
		battleSeats[i].isUse = false;
		battleSeats[i].localPosition.x = sinf(angleBase * i) * 1.5f;
		battleSeats[i].localPosition.y = 0.0f;
		battleSeats[i].localPosition.z = cosf(angleBase * i) * 1.5f;
		battleSeats[i].position.Add(battleSeats[i].localPosition, position);
	}
}
/*!
* @brief	バトルで使用するシートを更新。
*/
void Player::UpdateBattleSeats()
{
	for (auto& seat : battleSeats) {
		seat.position.Add(seat.localPosition, position);
	}
}
/*!
* @brief	未使用のシートを検索。
*@param[in]	pos		未使用のシートの中からこの座標に一番近いシートを返します。
*@return		未使用のシートがない場合はNULLが返ってくる。
*/
Player::SBattleSeat* Player::FindUnuseSeat(const CVector3& pos)
{
	float dist = FLT_MAX;
	float distTmp;
	SBattleSeat* result = NULL;
	for (auto& seat : battleSeats) {
		if (!seat.isUse) {
			//未使用。
			CVector3 diff;
			diff.Subtract(seat.position, pos);
			distTmp = diff.LengthSq();
			if (distTmp < dist) {
				dist = distTmp;
				result = &seat;
			}
		}
	}
	return result;
}
/*!
* @brief	血しぶきのパーティクルをエミット。
*/
void Player::EmitBloodParticle()
{
	CMatrix* m = skinModel.FindBoneWorldMatrix("thief_Bip01_Neck");
	for (SParicleEmitParameter& param : bloodEmitterParam) {
		CParticleEmitter* particleEmitter = NewGO<CParticleEmitter>(1);
		CVector3 pos;
		pos.Set(m->m[3][0], m->m[3][1], m->m[3][2]);
		particleEmitter->Init(g_random, g_camera->GetCamera(), param, pos);
		particleEmitterList.push_back(particleEmitter);
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init("Assets/sound/Damage_01.wav");
		se->Play(false);
		se->SetVolume(0.5f);
	}
}
/*!
* @brief	状態切り替え。
*/
void Player::ChangeState(EnState nextState)
{
	if (currentState != NULL) {
		//現在のステートを抜ける。
		currentState->Leave();
	}
	switch (nextState) {
	case enStateStand:
		currentState = &standState;
		break;
	case enStateRun:
		currentState = &runState;
		break;
	case enState_Attack:
		currentState = &attackState;
		break;
	case enState_Damage:
		currentState = &damageState;
		break;
	case enState_Dead:
		currentState = &deadState;
		break;
	default:
		TK_ASSERT(false, "nextState is invalid");
		break;
	}
	state = nextState;
	currentState->Enter();
	
}
/*!
* @brief	スロットに設定されている魔法を更新。
*/
void Player::UpdateCurrentMagicSkill()
{
	bool isChangeMagic = false;
	if (Pad(0).IsTrigger(enButtonRB1)) {
		currentMagicSkill = (EMagicSkill)((currentMagicSkill + 1) % eMagicSkillNum);
		isChangeMagic = true;
	}
	else if (Pad(0).IsTrigger(enButtonLB1)) {
		int t = currentMagicSkill - 1;
		if (t < 0) {
			currentMagicSkill = (EMagicSkill)(eMagicSkillNum - 1);
		}
		else {
			currentMagicSkill = (EMagicSkill)t;
		}
		isChangeMagic = true;
	}
	if (isChangeMagic) {
		switch (currentMagicSkill) {
		case eMagicSkillDash:
			if (pCurrentMagicSkill != NULL) {
				pCurrentMagicSkill->OnEndMagic();
			}
			pCurrentMagicSkill = &magicSkillDash;
			pCurrentMagicSkill->OnChangeMagic();
			break;
		case eMagicSkillSlow:
			if (pCurrentMagicSkill != NULL) {
				pCurrentMagicSkill->OnEndMagic();
			}
			pCurrentMagicSkill = &magicSkillSlow;
			pCurrentMagicSkill->OnChangeMagic();
			break;
		case eMagicSkillStopTheWorld:
			if (pCurrentMagicSkill != NULL) {
				pCurrentMagicSkill->OnEndMagic();
			}
			pCurrentMagicSkill = &magicSkillStop;
			pCurrentMagicSkill->OnChangeMagic();
			break;
		case eMagicSkillStealth:
			if (pCurrentMagicSkill != NULL) {
				pCurrentMagicSkill->OnEndMagic();
			}
			pCurrentMagicSkill = &magicSkillStealth;
			pCurrentMagicSkill->OnChangeMagic();
			break;
		case eMagicSkillHighJump:
			break;
		default:
			TK_LOG("未実装\n");
			break;
		}
	}
	if (pCurrentMagicSkill != NULL) {
		pCurrentMagicSkill->Update();
	}
}
/*!
* @brief	描画。
*/
void Player::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}

void Player::Update()
{
	if (!gameScene->IsStart()) {
		return;
	}
	localFrameDeltaTime = GameTime().GetFrameDeltaTime();
	//スロットに設定されている魔法を更新。
	UpdateCurrentMagicSkill();
	//ステートマシーンの更新。
	UpdateStateMachine();
	//旋回。
	Turn();
	//ダメージ処理。
	Damage();
	//アニメーションコントロール。
	AnimationControl();
	//バトル用のシートの更新。
	UpdateBattleSeats();
	//アニメーションイベントコントローラの実行。
	animationEventController.Update();
	//マジックポイントは少しづつ回復する。
	RecoverMagicPoint(RECOVER_MP * GameTime().GetFrameDeltaTime());
	//ワールド行列の更新。
	skinModel.Update(position, rotation, CVector3::One);
	//ポイントライトを更新。
	UpdatePointLight();
	

	lastFrameState = state;
}