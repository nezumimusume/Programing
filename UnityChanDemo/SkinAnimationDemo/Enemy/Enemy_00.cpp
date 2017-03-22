/*!
 * @brief	タイプ0の敵。
 */

#include "stdafx.h"
#include "Enemy/Enemy_00.h"
#include "Player/Player.h"
#include "Item.h"
#include "Enemy/HFSM/EnemyStateSearch.h"
#include "Enemy/HFSM/EnemyStateFind.h"
#include "Enemy/HFSM/EnemyStateDamage.h"
#include "Enemy/HFSM/EnemyStateDeath.h"
#include "DamageCollisionWorld.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "Scene/GameScene.h"
#include "ItemMaker.h"

Enemy_00::Enemy_00()
{
	state = enLocalState_Search;
	initPosition = CVector3::Zero;
	moveSpeed = 0.0f;
	direction = CVector3::AxisZ;
	moveDirection = CVector3::AxisZ;
	radius = 0.0f;
	height = 0.0f;
	hp = 70;
}
Enemy_00::~Enemy_00()
{
	for (auto& state : states) {
		delete state;
	}
}

void Enemy_00::Init(const char* modelPath, CVector3 pos, CQuaternion rotation)
{
	Enemy::Init(modelPath, pos, rotation);

	
}
void Enemy_00::OnLoadedSkinModelData()
{
	PlayAnimation(enAnimWalk);
	animation.SetAnimationLoopFlag(enAnimAttack, false);
	animation.SetAnimationLoopFlag(enAnimDamage, false);
	animation.SetAnimationLoopFlag(enAnimDeath, false);


	sphereShape.reset(new CSphereCollider);
	sphereShape->Create(radius);
	collisionObject.reset(new btCollisionObject());
	collisionObject->setCollisionShape(sphereShape->GetBody());

	InitHFSM();
}
/*!
 * @brief	HFSMを初期化。
 */
void Enemy_00::InitHFSM()
{
	//探索状態を追加。
	states.push_back( new EnemyStateSearch(this) );
	//発見状態を追加。
	states.push_back( new EnemyStateFind(this) );
	//ダメージ状態を追加。
	states.push_back( new EnemyStateDamage(this));
	//死亡状態を追加。
	states.push_back( new EnemyStateDeath(this));
	state = enLocalState_Search;
	states[state]->Enter(IEnemyState::SEnterArg());
}

void Enemy_00::Update()
{
	if (!gameScene->IsStart()) {
		return;
	}
	Enemy::Update();

	if (GetLocalFrameDeltaTime() < FLT_EPSILON) {
		//停止中はダメージ処理と行列の更新(呼ばないと影が書かれないから)は行う。
		Damage();
		if (!objectCulling.IsCulling()) {
			skinModel.Update(position, rotation, CVector3::One);
		}
		return;
	}
	states[state]->Update();
	switch (state) {
	case enLocalState_Search:
	{
		CVector3 unityPos = g_player->GetPosition();
		CVector3 diff;
		diff.Subtract(unityPos, position);
		if (diff.LengthSq() < 5.0f * 5.0f) {
			//見つけた。
			states[state]->Leave();
			state = enLocalState_Find;
			states[state]->Enter(IEnemyState::SEnterArg());
		}
	}break;
	case enLocalState_Find:
	{
	
	}break;
	case enLocalState_Damage:
		if (!animation.IsPlay()) {
			states[state]->Leave();
			state = enLocalState_Find;
			states[state]->Enter(IEnemyState::SEnterArg());
		}
		break;
	}
	//ダメージ処理
	Damage();
	
	if (state != enLocalState_Death) {
		CVector3 speed = characterController.GetMoveSpeed();
		speed.x = moveDirection.x * moveSpeed;
		speed.z = moveDirection.z * moveSpeed;
		characterController.SetMoveSpeed(speed);
		characterController.Execute(GetLocalFrameDeltaTime());
		position = characterController.GetPosition();

		//回転は適当に。
		if (states[state]->IsPossibleRotate())
		{
			float angle = atan2f(direction.x, direction.z);
			rotation.SetRotation(CVector3::AxisY, angle);
		}
	}
//	light.SetPointLightPosition(g_player->GetPointLightPosition());
//	light.SetPointLightColor(g_player->GetPointLightColor());
	
	if (!objectCulling.IsCulling()) {
		animation.Update(GetLocalFrameDeltaTime());
		skinModel.Update(position, rotation, CVector3::One);
	}

	if (state != enLocalState_Death) {
		timer += GetLocalFrameDeltaTime();
		if (timer > 2.0f) {
			if (g_random.GetRandDouble() < 0.2f) {
				CSoundSource* se = NewGO<CSoundSource>(0);
				se->SetTags(GameScene::enGameObjectTags_EnemySound);
				se->Init("Assets/Sound/enemy_umeki.wav", true);
				se->Play(false);
				se->SetPosition(position);
			}
			timer = 0.0f;
		}
	}
}
void Enemy_00::Damage()
{
	if (state == enLocalState_Death) {
		//死んでる。
		return;
	}
	float offset = radius + height * 0.5f;
	CVector3 centerPos;
	centerPos = position;
	centerPos.y += offset;
	btTransform trans;
	trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
	collisionObject->setWorldTransform(trans);
	const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToEnemy,
		collisionObject.get()
	);
	if (!dmgColli) {
		centerPos.y += offset;
		trans.setOrigin(btVector3(centerPos.x, centerPos.y, centerPos.z));
		collisionObject->setWorldTransform(trans);
		const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
			DamageCollisionWorld::enDamageToEnemy,
			collisionObject.get()
		);
	}
	if (dmgColli != NULL && states[state]->IsPossibleApplyDamage(dmgColli) ) {
		//ダメージを食らっている。
		hp -= dmgColli->damage;
		if (hp <= 0) {
			//死亡。
			states[state]->Leave();
			state = enLocalState_Death;
			states[state]->Enter(IEnemyState::SEnterArg());
			g_itemMaker->NewItem(position);
		}
		else {
			states[state]->Leave();
			state = enLocalState_Damage;
			IEnemyState::SEnterArg enterArg;
			enterArg.arg[0] = dmgColli->groupID;	//ダメージを受けたコリジョンのグループＩＤを渡す。
			states[state]->Enter(enterArg);
		}
	}
}
void Enemy_00::Render(CRenderContext& renderContext)
{
	if (!objectCulling.IsCulling()) {
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
}
/*!
* @brief	ロックオン可能か判定。
*@retval	true	ロックオン可能。
*@retval	false	ロックオン不可能。
*/
bool Enemy_00::IsPossibleLockOn() const 
{
	return states[state]->IsPossibleLockOn();
}