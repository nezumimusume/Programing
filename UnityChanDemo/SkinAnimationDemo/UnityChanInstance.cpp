#include "stdafx.h"
#include "UnityChanInstance.h"

extern CCamera*			g_camera;				//カメラ。

namespace {
	const int NUM_INSTANCE = 100;
}
UnityChanInstance::UnityChanInstance() :
	worldMatrixBuffer(nullptr),
	currentAnimSetNo(0)
{
}


UnityChanInstance::~UnityChanInstance()
{
	delete[] worldMatrixBuffer;
}
void UnityChanInstance::Start()
{
	skinModelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	//インスタンス描画用のデータを作成。
	tkEngine::SVertexElement vertexElement[] = {
		{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1行目
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2行目
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3行目
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4行目
		D3DDECL_END()
	};
	skinModelData.CreateInstancingDrawData(NUM_INSTANCE, vertexElement);
	worldMatrixBuffer = new CMatrix[NUM_INSTANCE];
	worldMatrixBuffer[0].MakeTranslation(CVector3(0.0f, 0.0f, 0.0f));	//一匹目。
	int gyou = 1;		//行。
	int retu = 0;		//列。
	int numRetu = 3;	//列数。
	int execRetu = 0;	//配置した列の数。
	for (int i = 1; i < NUM_INSTANCE; i++) {
		if (retu == 0) {
			worldMatrixBuffer[i].MakeTranslation(CVector3(0.0f, 0.0f, -0.5f * gyou));
			retu = 1;
		}
		else {
			
			worldMatrixBuffer[i].MakeTranslation(CVector3(0.5f * retu, 0.0f, -0.5f * gyou));
			retu *= -1.0f;
			if (retu > 0) {
				//正
				retu++;
			}
		}
		execRetu++;
		if (execRetu == numRetu) {
			//この行に配置できる列は全て配置した。
			execRetu = 0;
			retu = 0;
			gyou++;
			numRetu += 2;
		}
	}
	normalMap.Load("Assets/modelData/utc_nomal.tga");
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
	skinModel.SetFresnelFlag(true);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);

	camera.SetPosition(CVector3(0.0f, 2.5f, 3.5f));
	camera.SetTarget(CVector3(0.0f, 1.0f, 0.0f));

	camera.SetFar(10000.0f);
	camera.Update();
	g_camera = &camera;
	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, CVector4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbinetLight(CVector3(0.3f, 0.3f, 0.3f));
	animation.PlayAnimation(0);
}
void UnityChanInstance::Update()
{
	animation.Update(1.0f / 60.0f);
	skinModel.UpdateInstancingDrawData(worldMatrixBuffer);
	skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	static float angle = 0.0f;
	if (KeyInput().IsRightPress()) {
		angle += 0.01f;
	}
	else if (KeyInput().IsLeftPress()) {
		angle -= 0.01f;
	}
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, CMath::DegToRad(-90.0f) * angle);
	worldMatrixBuffer[0].MakeRotationFromQuaternion(qRot);
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
void UnityChanInstance::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
}