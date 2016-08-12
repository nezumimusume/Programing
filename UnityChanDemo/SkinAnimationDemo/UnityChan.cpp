#include "stdafx.h"
#include "UnityChan.h"


extern CCamera*			g_camera;				//カメラ。
CSkinModelData*	UnityChan::orgSkinModelData = NULL;	//オリジナルスキンモデルデータ。
CAnimation				*orgAnimation;			//アニメーション。

/*!
 * @brief	開始
 */
void UnityChan::Start()
{
	if (orgSkinModelData == NULL) {
		orgSkinModelData = new CSkinModelData;
		orgAnimation = new CAnimation;
		orgSkinModelData->LoadModelData("Assets/modelData/Unity.X", orgAnimation);
	}
	//オリジナルのモデルデータからクローンモデルを作成。
	skinModelData.CloneModelData(*orgSkinModelData, &animation);
	normalMap.Load("Assets/modelData/utc_nomal.tga");

	//skinModelData.LoadModelData("Assets/modelData/unity.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);
	camera.SetPosition(CVector3(0.0f, 1.0f, 1.5f));
	camera.SetTarget(CVector3(0.0f, 0.5f, 0.0f));

	camera.SetFar(1000.0f);
	camera.Update();
	g_camera = &camera;
	light.SetDiffuseLightDirection(0,  CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));
	animation.SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationStand;
	animation.PlayAnimation(AnimationStand);
}
/*!
 * @brief	更新。
 */
void UnityChan::Update()  
{
	//アニメーション再生のサンプルコード。
	animation.Update(1.0f / 60.0f);
	static float angle = 0.0f;
	if (KeyInput().IsRightPress()) {
		angle += 0.01f;
	}
	else if (KeyInput().IsLeftPress()) {
		angle -= 0.01f;
	}
	camera.Update();

	//Unityちゃんを回す。
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, CMath::DegToRad(-90.0f) * angle);
	
	skinModel.Update(position, qRot, CVector3::One);
	if (this->isUpdateAnim) {
		if (KeyInput().IsTrgger(CKeyInput::enKeyA)) {
			currentAnimSetNo++;
			currentAnimSetNo %= animation.GetNumAnimationSet();
			animation.PlayAnimation(currentAnimSetNo);
		}
		if (KeyInput().IsTrgger(CKeyInput::enKeyB)) {
			currentAnimSetNo++;
			currentAnimSetNo %= animation.GetNumAnimationSet();
			animation.PlayAnimation(currentAnimSetNo, 0.1f);
		}
	}
	
}
/*!
 * @brief	描画。
 */
void UnityChan::Render( CRenderContext& renderContext ) 
{
	skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
}
