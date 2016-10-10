#include "stdafx.h"
#include "UnityChan.h"
#include "Car.h"
#include "Map/Ground.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"

namespace {
	const float MAX_RUN_SPEED = 0.1f;					//ユニティちゃんの走りの最高速度。
	const float RUN_THREADHOLD_SQ = 4.0f * 4.0f;		//走りアニメーションを再生する速度の閾値。
}
/*!
* @brief	開始
*/
void UnityChan::Start()
{
	SkinModelDataResources().Load(skinModelData, "Assets/modelData/Player.X", &animation);
	normalMap.Load("Assets/modelData/Thethief_N.tga");
	specMap.Load("Assets/modelData/Thethief_S.tga");
	weaponNormalMap.Load("Assets/modelData/Thethief_wuqi_N.tga");
	weaponSpecMap.Load("Assets/modelData/Thethief_wuqi_S.tga");
	//体のマテリアルを取得。
	CSkinModelMaterial* mat = skinModelData.GetBody()->FindMaterial("Thethief_D.tga");
	mat->SetTexture("g_normalTexture", &normalMap );
	mat->SetTexture("g_speculerMap", &specMap);
	//武器のマテリアルを取得。
	mat = skinModelData.GetBody()->FindMaterial("Thethief_wuqi_D.tga");
	mat->SetTexture("g_normalTexture", &weaponNormalMap);
	mat->SetTexture("g_speculerMap", &weaponSpecMap);

	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&light);
	skinModel.SetHasNormalMap(true);
	skinModel.SetHasSpeculerMap(true);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetAmbinetLight(CVector3(0.4f, 0.4f, 0.4f));

	light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

	isPointLightOn = false;
	UpdatePointLightPosition();

	PlayAnimation(AnimationInvalid, 0.0f);
	rotation = CQuaternion::Identity;
	
	CVector3 lightPos = CVector3(0.0f, 25.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	state = enStateStand;

	characterController.Init(0.4f, 0.3f, position);
	toLampLocalPos.Set( 0.0f, 0.5f, 0.2f);
	InitBattleSeats();
	//g_physicsWorld->AddRigidBody(&rigidBody);
	animation.SetAnimationEndTime(AnimationAttack_00, 0.63333f);
	animation.SetAnimationEndTime(AnimationAttack_01, 0.76666f);
	animation.SetAnimationLoopFlag(AnimationJump, false);
	animation.SetAnimationLoopFlag(AnimationAttack_00, false);
	animation.SetAnimationLoopFlag(AnimationAttack_01, false);
	animation.SetAnimationLoopFlag(AnimationAttack_02, false);
	animation.SetAnimationLoopFlag(AnimationDamage, false);
	nextAttackAnimNo = AnimationInvalid;
	reqAttackAnimNo = AnimationInvalid;
}
void UnityChan::Update()
{
	CVector3 nextPosition = position;
	
	const float MOVE_SPEED = 7.0f;
	if (state == enStateRun || state == enStateStand) {
		CVector3 moveSpeed = characterController.GetMoveSpeed();
		if (Pad(0).IsTrigger(enButtonRB3)) {
			isPointLightOn = !isPointLightOn;
		}
		if (Pad(0).IsPress(enButtonA)) {
			//Aボタンが押された。
			//車との距離を調べる。
			CVector3 diff = g_car->GetPosition();
			diff.Subtract(position);
			if (diff.Length() < 2.0f) {
				//車との距離が2m以内。
				state = enState_RideOnCar;
				skinModel.SetShadowReceiverFlag(false);
				skinModel.SetShadowCasterFlag(false);
				g_car->SetRideOnFlag(true);
				g_camera->SetCar(g_car);
				return;
			}
			else if(!characterController.IsJump()){
				//車との距離が離れていたらジャンプ。
				moveSpeed.y = 8.0f;
				characterController.Jump();
			}
		}
		//走りか立ち状態の時。
		CVector3 moveDirLocal;
		moveDirLocal.y = 0.0f;
		moveDirLocal.x = Pad(0).GetLStickXF();
		moveDirLocal.z = Pad(0).GetLStickYF();
		const CMatrix& mViewInv = g_camera->GetCamera().GetViewMatrixInv();
		//カメラ空間から見た奥方向のベクトルを取得。
		CVector3 cameraZ;
		cameraZ.x = mViewInv.m[2][0];
		cameraZ.y = 0.0f;		//Y軸いらない。
		cameraZ.z = mViewInv.m[2][2];
		cameraZ.Normalize();	//Y軸を打ち消しているので正規化する。
								//カメラから見た横方向のベクトルを取得。
		CVector3 cameraX;
		cameraX.x = mViewInv.m[0][0];
		cameraX.y = 0.0f;		//Y軸はいらない。
		cameraX.z = mViewInv.m[0][2];
		cameraX.Normalize();	//Y軸を打ち消しているので正規化する。

		CVector3 moveDir;
		moveDir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
		moveDir.y = 0.0f;	//Y軸はいらない。
		moveDir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;
		
		if (moveDir.LengthSq() > 0.0001f) {
			rotation.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
			//走り状態に遷移。
			state = enStateRun;
		}
		else {
			//立ち状態。
			state = enStateStand;
		}
		characterController.SetMoveSpeed(moveSpeed);
		characterController.Execute();
		
		if (Pad(0).IsTrigger(enButtonX) && !characterController.IsJump()) {
			nextAttackAnimNo = AnimationAttack_00;
			state = enState_Attack;
		}
	}
	else if (state == enState_RideOnCar) {
		ShadowMap().SetLightTarget(g_car->GetPosition());
		CVector3 lightPos;
		lightPos.Add(g_car->GetPosition(), toLightPos);
		ShadowMap().SetLightPosition(lightPos);
		if (g_car->GetMoveSpeed().Length() < 0.1f) {
			//車が停止状態。
			if (Pad(0).IsPress(enButtonB)) {
				//降車。
				g_camera->SetCar(NULL);
				g_car->SetRideOnFlag(false);
				skinModel.SetShadowReceiverFlag(true);
				skinModel.SetShadowCasterFlag(true);
				position = g_car->GetPosition();
				state = enStateStand;
			}
		}
	}
	else if (state == enState_Attack) {
		//移動がピタって止まると気持ちわるいので
		CVector3 moveSpeed = characterController.GetMoveSpeed();
		moveSpeed.Scale(0.8f);
		characterController.SetMoveSpeed(moveSpeed);
		characterController.Execute();
		int currentAnimNo = animation.GetPlayAnimNo();
		if (!animation.IsPlay() && nextAttackAnimNo == AnimationInvalid) {
			state = enStateStand;
		}
		else if (
				Pad(0).IsTrigger(enButtonX) 
				&& currentAnimNo >= AnimationAttack_Start
				&& currentAnimNo < AnimationAttack_End
				&& currentAnimNo == reqAttackAnimNo
			) {
			//コンボ発生。
			nextAttackAnimNo = (AnimationNo)(animation.GetPlayAnimNo() + 1);
		}
	}
	position = characterController.GetPosition();

	//ポイントライトの位置を更新。
	UpdatePointLightPosition();
	//アニメーションコントロール。
	AnimationControl();
	//バトル用のシートの更新。
	UpdateBattleSeats();

	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	skinModel.Update(position, rotation, CVector3::One);
	
	
	lastFrameState = state;
}
/*!
* @brief	ポイントライトの位置を更新。
*/
void UnityChan::UpdatePointLightPosition()
{
	if (isPointLightOn) {
		pointLightColor.Set(0.9f, 0.75f, 0.6f, 1.0f);
	}
	else {
		pointLightColor = CVector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	light.SetPointLightColor(pointLightColor);
	pointLightPosition = toLampLocalPos;
	CMatrix mWorld = skinModel.GetWorldMatrix();
	mWorld.Mul(pointLightPosition);
	light.SetPointLightPosition(pointLightPosition);
}
/*!
* @brief	アニメーション再生。
*/
void UnityChan::PlayAnimation(AnimationNo animNo, float interpolateTime)
{
	if (animation.GetPlayAnimNo() != animNo && animNo != AnimationInvalid) {
		//別のアニメーション
		animation.PlayAnimation(animNo, interpolateTime);
	}
}
/*!
* @brief	アニメーションコントロール。
*/
void UnityChan::AnimationControl()
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
	}
	animation.Update(GameTime().GetFrameDeltaTime());
}
/*!
* @brief	バトルで使用するシートを初期化。
*/
void UnityChan::InitBattleSeats()
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
void UnityChan::UpdateBattleSeats()
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
UnityChan::SBattleSeat* UnityChan::FindUnuseSeat(const CVector3& pos)
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
* @brief	描画。
*/
void UnityChan::Render(CRenderContext& renderContext)
{
#ifdef ENEMY_TEST
	return;
#endif
	if (state != enState_RideOnCar) {
		//車に乗っているときは非表示にする。
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
}
