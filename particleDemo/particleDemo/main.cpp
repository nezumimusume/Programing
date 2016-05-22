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

SParicleEmitParameter particleParameterTbl[] =
{
	//燃え上がる炎
	{
		"Assets/Effect/PRT_Fire.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3(0.0f, 1.0f, 0.0f),		//CVector3	initVelocity;						//!<初速度。
		1.0f,							//float		life;								//!<寿命。単位は秒。
		0.01f,							//float		intervalTime;						//!<発生時間。単位は秒。
		0.5f,							//float		w;									//!<パーティクルの幅。
		0.5f,							//float		h;									//!<パーティクルの高さ。
		CVector3(0.2f, 0.0f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3(0.3f, 0.0f, 0.3f),		//CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3(0.005f, 0.0f, 0.005f),	//CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		{											//!<CVector4	uvTable[4];			UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		1.0f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		2.0f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
	//マグマの噴出っぽい炎
	{
		"Assets/Effect/PRT_Fire.png",	//const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3(0.0f, 5.0f, 0.0f),		//CVector3	initVelocity;						//!<初速度。
		1.0f,							//float		life;								//!<寿命。単位は秒。
		0.01f,							//float		intervalTime;						//!<発生時間。単位は秒。
		0.5f,							//float		w;									//!<パーティクルの幅。
		0.5f,							//float		h;									//!<パーティクルの高さ。
		CVector3(0.2f, 0.0f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3(0.3f, 0.0f, 0.3f),		//CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		{											//!<CVector4	uvTable[4];			UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			CVector4(0.0f,  0.0f, 0.25f, 0.5f),
			CVector4(0.25f, 0.0f, 0.5f,  0.5f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		4,								//int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3(0.0f, -9.8f, 0.0f ),	//CVector3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		0.1f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		2.0f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
	//はじけ飛ぶ星エフェクト
	{
		"Assets/Effect/star.png",		//const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3(0.0f, 5.0f, 0.0f),		//CVector3	initVelocity;						//!<初速度。
		0.5f,							//float		life;								//!<寿命。単位は秒。
		0.02f,							//float		intervalTime;						//!<発生時間。単位は秒。
		0.5f,							//float		w;									//!<パーティクルの幅。
		0.5f,							//float		h;									//!<パーティクルの高さz。
		CVector3(0.2f, 0.2f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3(3.0f, 0.0f, 3.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		{											//!<CVector4	uvTable[4];			UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			CVector4(0.0f,  0.0f, 1.0f, 1.0f),
			CVector4(0.0f, 0.0f,  0.0f, 0.0f),
			CVector4(0.5f,  0.0f, 0.75f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		1,								//int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3(0.0f, -9.8f, 0.0f),		//CVector3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		0.3f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		0.1f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		0,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
	//風
	{
		"Assets/Effect/leaf.png",		//const char* texturePath;						//!<テクスチャのファイルパス。
		CVector3(4.0f, 0.0f, 0.0f),		//CVector3	initVelocity;						//!<初速度。
		3.0f,							//float		life;								//!<寿命。単位は秒。
		0.2f,							//float		intervalTime;						//!<発生時間。単位は秒。
		0.4f,							//float		w;									//!<パーティクルの幅。
		0.4f,							//float		h;									//!<パーティクルの高さ。
		CVector3(0.2f, 0.4f, 0.2f),		//CVector3	initPositionRandomMargin;			//!<初期位置のランダム幅。
		CVector3(0.0f, 0.0f, 0.0f),		//CVector3	initVelocityVelocityRandomMargin;	//!<初速度のランダム幅。
		CVector3(0.0f, 2.0f, 2.0f),		//CVector3	addVelocityRandomMargih;			//!<速度の積分のときのランダム幅。
		{											//!<CVector4	uvTable[4];			UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			CVector4(0.0f,  0.0f, 1.0f, 1.0f),
			CVector4(0.0833333f, 0.0f,  0.1666666f, 0.0f),
			CVector4(0.1666666f,  0.0f, 0.2499999f, 0.5f),
			CVector4(0.75f, 0.0f, 1.0f,  0.5f),
		},
		1,								//int			uvTableSize;						//!<UVテーブルのサイズ。
		CVector3(0.0f, -0.0f, 0.0f),		//CVector3	gravity;							//!<重力。
		true,							//bool		isFade;								//!<死ぬときにフェードアウトする？
		0.3f,							//float		fadeTime;							//!<フェードする時間。
		1.0f,							//float		initAlpha;							//!<初期アルファ値。
		true,							//bool		isBillboard;						//!<ビルボード？
		0.1f,							//float		brightness;							//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		0,								//int		alphaBlendMode;						//!<0半透明合成、1加算合成。
	},
};
class ParticleDemo : public IGameObject{
private:
	CCamera				camera;			//カメラ。
	CParticleEmitter*	emitter;
	CVector3			cameraPos;
	int					currentEmitterNo;
public:
	ParticleDemo()
	{
		cameraPos = CVector3(0.0f, 1.0f, -5.0f);
		camera.SetPosition(cameraPos);
		camera.SetTarget(CVector3::Zero);
		currentEmitterNo = 0;	
	}
	~ParticleDemo()
	{
	}
	void Start() override
	{
		random.Init((unsigned long)time);
		emitter = GameObjectManager().NewGameObject<CParticleEmitter>(0);
	
		emitter->Init(random, camera, particleParameterTbl[currentEmitterNo], CVector3::Zero);
		camera.Update();
	}
	void Update() override
	{

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
			emitter->ApplyForce(CVector3(-5.0f, 0.0f, 1.0f));
		}
		if(KeyInput().IsTrgger(CKeyInput::enKeyA)){
			GameObjectManager().DeleteGameObject(emitter);
			emitter = GameObjectManager().NewGameObject<CParticleEmitter>(0);
			currentEmitterNo = (currentEmitterNo + 1) % ARRAYSIZE(particleParameterTbl);
			emitter->Init(random, camera, particleParameterTbl[currentEmitterNo], CVector3::Zero);
		}
		mRot.Mul(cameraPos);
		camera.SetPosition(cameraPos);
		camera.Update();
	}
	void Render(CRenderContext& renderContext) override
	{
	//	skinModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
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
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
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