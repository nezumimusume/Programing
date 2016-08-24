#include "stdafx.h"
#include "UnityChan.h"


CSkinModelData*	UnityChan::orgSkinModelData = NULL;	//オリジナルスキンモデルデータ。
CAnimation				*orgAnimation;			//アニメーション。

namespace {
	const float MAX_RUN_SPEED = 0.1f;					//ユニティちゃんの走りの最高速度。
	const float RUN_THREADHOLD_SQ = 0.07f * 0.07f;		//走りアニメーションを再生する速度の閾値。
}
/*!
 * @brief	開始
 */
void UnityChan::Start()
{
	if (orgSkinModelData == NULL) {
		orgSkinModelData = new CSkinModelData;
		orgAnimation = new CAnimation;
		orgSkinModelData->LoadModelData("Assets/modelData/car.X", orgAnimation);
	}
	//オリジナルのモデルデータからクローンモデルを作成。
	skinModelData.CloneModelData(*orgSkinModelData, &animation);
	normalMap.Load("Assets/modelData/Scout_Normal.png");

	//skinModelData.LoadModelData("Assets/modelData/unity.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));
	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationInvalid;
	PlayAnimation(currentAnimSetNo);
	rotation = CQuaternion::Identity;

	
	CVector3 lightPos = CVector3(0.0f, 3.5f, 3.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract( lightPos, position );
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	state = enStateStand;
}
/*!
 * @brief	更新。
 */
void UnityChan::Update()  
{
	
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

	moveSpeed = moveDir;
	moveSpeed.Scale(0.1f);
	position.Add(moveSpeed);

	if (moveDir.LengthSq() > 0.0001f) {
		rotation.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
		//走り状態に遷移。
		state = enStateRun;
	}
	else {
		//立ち状態。%
		state = enStateStand;
	}
	skinModel.Update(position, rotation, CVector3::One);
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	//アニメーションコントロール。
	//AnimationControl();
	lastFrameState = state;
}
/*!
* @brief	アニメーション再生。
*/
void UnityChan::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimSetNo != animNo) {
		//別のアニメーション
		//animation.PlayAnimation(animNo, 0.1f);
		currentAnimSetNo = animNo;
	}
}
/*!
* @brief	アニメーションコントロール。
*/
void UnityChan::AnimationControl()
{
	animation.Update(1.0f / 60.0f);
	if (state == enStateRun) {
		if (moveSpeed.LengthSq() > RUN_THREADHOLD_SQ) {
			//走りアニメーションを流す。
			PlayAnimation(AnimationRun);
		}
		else {
			//歩きアニメーション。
			PlayAnimation(AnimationWalk);
		}
	}
	else if(state == enStateStand) {
		//立ちアニメーションを流す。
		PlayAnimation(AnimationStand);
	}
}
/*!
 * @brief	描画。
 */
void UnityChan::Render( CRenderContext& renderContext ) 
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
