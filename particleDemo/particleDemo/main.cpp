#include "stdafx.h"
#include "tkEngine/graphics/tkCamera.h"
#include <time.h>
#include "tkEngine/random/tkRandom.h"
#include "tkEngine/particle/tkParticleEmitter.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"

CRandom random;	//乱数。

class ParticleDemo : public IGameObject{
private:
	CSkinModelData	skinModelData;		//スキンモデルデータ。
	CSkinModel		skinModel;			//スキンモデル。
	CAnimation		animation;			//アニメーション。
	CCamera				camera;			//カメラ。
	CParticleEmitter*	emitter;
	CVector3			cameraPos;
public:
	ParticleDemo()
	{
		skinModelData.LoadModelData("Assets/modelData/PL_Girl_SSword.x", &animation);
		skinModel.SetSkinModelData(&skinModelData);
		cameraPos = CVector3(0.0f, 1.0f, -5.0f);
		camera.SetPosition(cameraPos);
		camera.SetTarget(CVector3::Zero);	
	}
	~ParticleDemo()
	{
	}
	void Start() override
	{
		random.Init((unsigned long)time);
		emitter = GameObjectManager().NewGameObject<CParticleEmitter>(0);
		SParicleEmitParameter param;
		param.Init();
		
		param.initVelocity = CVector3(0.0f, 1.0f, 0.0f);
		param.intervalTime = 0.01f;
		param.life = 1.0f;
		param.w = 0.5f;
		param.h = 0.5f;
		param.uvTable[0].x = 0.0f;
		param.uvTable[0].y = 0.0f;
		param.uvTable[0].z = 0.25f;
		param.uvTable[0].w = 0.5f;

		param.uvTable[1].x = 0.25f;
		param.uvTable[1].y = 0.0f;
		param.uvTable[1].z = 0.5f;
		param.uvTable[1].w = 0.5f;

		param.uvTable[2].x = 0.5f;
		param.uvTable[2].y = 0.0f;
		param.uvTable[2].z = 0.75f;
		param.uvTable[2].w = 0.5f;

		param.uvTable[3].x = 0.75f;
		param.uvTable[3].y = 0.0f;
		param.uvTable[3].z = 1.0f;
		param.uvTable[3].w = 0.5f;

		param.uvTableSize = 4;

		param.initPositionRandomMargin.x = 0.2f;
		param.initPositionRandomMargin.z = 0.2f;
		param.initVelocityVelocityRandomMargin.x = 0.3f;
		param.initVelocityVelocityRandomMargin.y = 0.0f;
		param.initVelocityVelocityRandomMargin.z = 0.3f;
		param.addVelocityRandomMargih.x = 0.5f;
		param.addVelocityRandomMargih.y = 0.5f;
		param.addVelocityRandomMargih.z = 0.5f;
		param.isFade = true;
		param.texturePath = "Assets/Effect/PRT_Fire.png";
		//param.gravity.Set(0.0f, -9.8f, 0.0f);
		emitter->Init(random, camera, param, CVector3::Zero);
		camera.Update();
	}
	void Update() override
	{
		animation.Update(1.0f / 60.0f);
		skinModel.UpdateWorldMatrix(CVector3::Zero, CQuaternion::Identity, CVector3::One);

		//ビルボードのテストのためにカメラを動かす。
		CMatrix mRot = CMatrix::Identity;
		if (KeyInput().IsRightPress()) {
			mRot.MakeRotationY(0.03f);
		}
		else if (KeyInput().IsLeftPress()) {
			mRot.MakeRotationY(-0.03f);
		}
		if (KeyInput().IsUpPress()) {
			mRot.MakeRotationX(0.03f);
		}
		else if (KeyInput().IsDownPress()) {
			mRot.MakeRotationX(-0.03f);
		}
		if (KeyInput().IsPress(CKeyInput::enKeyA)) {
			//パーティクルに力を加える。
			emitter->ApplyForce(CVector3(1.0f, 0.0f, 0.0f));
		}
		else if(KeyInput().IsPress(CKeyInput::enKeyB)) {
			emitter->ApplyForce(CVector3(-1.0f, 0.0f, 1.0f));
		}
		mRot.Mul(cameraPos);
		camera.SetPosition(cameraPos);
		camera.Update();
	}
	void Render(CRenderContext& renderContext) override
	{
		skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}
};
/*!
 * @brief	tkEngineの初期化。
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.graphicsConfig.bloomConfig.isEnable = false;
	//Shadow
	//initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1280;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 720;
	Engine().Init(initParam);	//初期化。
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(10.0f);
	ShadowMap().SetLightPosition(CVector3(0.0f, 3.5f, 0.0f));
	ShadowMap().SetLightDirection(CVector3(0.0f, -1.0f, -0.0f));
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//tkEngineの初期化。
	InitTkEngine( hInst );
	ParticleDemo particleDemo;
	GameObjectManager().AddGameObject(0, &particleDemo);
	Engine().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}