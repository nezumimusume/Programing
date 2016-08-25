/*!
 *@brief	車クラス
 */

#include "stdafx.h"
#include "Car.h"

Car* g_car;

Car::Car()
{
	skinModelData.LoadModelData("Assets/modelData/car.X", NULL);
	normalMap.Load("Assets/modelData/Scout_Normal.png");
	speculerMap.Load("Assets/modelData/Scout_MetallicSmoothness.png");
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
	skinModel.SetSpeculerMap(&speculerMap);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 50.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 50.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 50.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 50.0f));
	light.SetAmbinetLight(CVector3(0.5f, 0.5f, 0.5f));
	position.Set(2.0f, 0.0f, 0.0f);
	moveSpeed = CVector3::Zero;
	accele = CVector3::Zero;
	rotation = CQuaternion::Identity;
	moveDirection = CVector3::AxisZ;
	rideOnFlag = false;
}
Car::~Car()
{

}
void Car::Start()
{

}
void Car::Update()
{
	if (rideOnFlag) {
		const CMatrix& mWorld = skinModel.GetWorldMatrix();
		//乗車中。
		if (Pad(0).IsPress(enButtonA)) {
			//車の進行方法に対して加速度をかける。
			accele = moveDirection;
			accele.Scale(2.0f);
		}
		else if (Pad(0).IsPress(enButtonB)) {
			//フットブレーキ(仮)
			accele = CVector3::Zero;
			moveSpeed.Scale(0.9f);
		}
		else {
			//エンジンブレーキ(仮)
			accele = CVector3::Zero;
			moveSpeed.Scale(0.95f);
		}
		float lstickX = Pad(0).GetLStickXF() * moveSpeed.Length();
		CQuaternion addRot;
		addRot.SetRotation(CVector3::AxisY, 0.01f * lstickX);
		rotation.Multiply(addRot);
		CMatrix mRot;
		mRot.MakeRotationFromQuaternion(addRot);
		mRot.Mul(moveSpeed);
		mRot.Mul(moveDirection);
		moveDirection.Normalize();
	}
	CVector3 addSpeed = accele;
	addSpeed.Scale(1.0f / 60.0f);
	moveSpeed.Add(addSpeed);
	CVector3 addPos = moveSpeed;
	addPos.Scale(1.0f / 60.0f);
	position.Add(addPos);
	skinModel.Update(position, rotation, CVector3::One);
}
void Car::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}