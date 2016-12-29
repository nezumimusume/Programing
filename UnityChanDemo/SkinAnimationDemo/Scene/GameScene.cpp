/*!
 *@brief	ゲームシーン。
 */

#include "stdafx.h"
#include "Scene/GameScene.h"

#include "Player/Player.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map/Map.h"
#include "Map/Sky.h"
#include "Map/Ground.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "EnemyTest.h"
#include "Enemy/EnemyManager.h"
#include <time.h>
#include "DamageCollisionWorld.h"
#include "tkEngine/graphics/sprite/tkSprite.h"
#include "HUD/PlayerHPBar.h"
#include "HUD/PlayerMPBar.h"
#include "HUD/NowLoading.h"
#include "HUD/GameOver2D.h"
#include "tkEngine/graphics/tkAtmosphericScatteringParam.h"

CPhysicsWorld* g_physicsWorld = NULL;
Player* g_player = NULL;
CRandom g_random;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;
extern SAtmosphericScatteringParam g_testAtmos;

namespace {
	const float fScaleDepth = 0.25;
	const float fInvScaleDepth = 4;

	const int nSamples = 2;
	const float fSamples = 2.0f;
	float scale(float fCos)
	{
		float x = 1.0f - fCos;
		return fScaleDepth * exp(-0.00287f + x*(0.459f + x*(3.83f + x*(-6.80f + x*5.25f))));
	}
	// Returns the near intersection point of a line and a sphere
	float getNearIntersection(CVector3 v3Pos, CVector3 v3Ray, float fDistance2, float fRadius2)
	{
		float B = 2.0f * v3Pos.Dot(v3Ray);
		float C = fDistance2 - fRadius2;
		float fDet = max(0.0f, B*B - 4.0f * C);
		return 0.5f * (-B - sqrt(fDet));
	}
	//ミー錯乱とレイリー錯乱を計算。
	//CPUでデバッグするために実装。
	void CalcMieAndRayleighColors(CVector4& mieColor, CVector4& rayColor, CVector3& posToCameraDir, CVector3 worldPos)
	{
		mieColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
		rayColor.Set(0.0f, 0.0f, 0.0f, 0.0f);
		worldPos.Scale(0.001f);
		worldPos.y += g_testAtmos.fInnerRadius;
		CVector3 cameraPos = g_camera->GetCamera().GetPosition();
		cameraPos.Scale(0.001f);
		cameraPos.y += g_testAtmos.fInnerRadius;
		// Get the ray from the camera to the vertex and its length (which is the far point of the ray passing through the atmosphere)
		CVector3 v3Ray;
		v3Ray.Subtract(worldPos, cameraPos);
		float fFar = v3Ray.Length();
		v3Ray.Normalize();

		// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
		//float fNear = getNearIntersection(g_camera->GetCamera().GetPosition(), v3Ray, g_testAtmos.fCameraHeight2, g_testAtmos.fOuterRadius2);

		CVector3  v3Start = cameraPos;
		float fHeight = v3Start.Length();
		float fDepth = exp(g_testAtmos.fScaleOverScaleDepth * (g_testAtmos.fInnerRadius - g_testAtmos.fCameraHeight));
		float fStartAngle = v3Ray.Dot(v3Start) / fHeight;
		float fStartOffset = fDepth*scale(fStartAngle);

		// Initialize the scattering loop variables
		float fSampleLength = fFar / fSamples;
		float fScaledLength = fSampleLength * g_testAtmos.fScale;
		CVector3 v3SampleRay = v3Ray;
		v3SampleRay.Scale(fSampleLength);
		//float3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
		CVector3 v3SamplePoint = v3SampleRay;
		v3SamplePoint.Scale(0.5f);
		v3SamplePoint.Add(v3Start);

		// Now loop through the sample rays
		CVector3 v3FrontColor = CVector3::Zero;
		for (int i = 0; i < nSamples; i++) {
			float fHeight = v3SamplePoint.Length();
			float fDepth = exp(g_testAtmos.fScaleOverScaleDepth * (g_testAtmos.fInnerRadius - fHeight));
			float fLightAngle = g_testAtmos.v3LightDirection.Dot( v3SamplePoint ) / fHeight;
			float fCameraAngle = v3Ray.Dot(v3SamplePoint) / fHeight;
			float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
			CVector3 v3Attenuate;
			v3Attenuate.x = exp(-fScatter * (g_testAtmos.v3InvWavelength.x * g_testAtmos.fKr4PI + g_testAtmos.fKm4PI));
			v3Attenuate.y = exp(-fScatter * (g_testAtmos.v3InvWavelength.y * g_testAtmos.fKr4PI + g_testAtmos.fKm4PI));
			v3Attenuate.z = exp(-fScatter * (g_testAtmos.v3InvWavelength.z * g_testAtmos.fKr4PI + g_testAtmos.fKm4PI));

			v3Attenuate.Scale(fDepth * fScaledLength);
			v3FrontColor.Add(v3Attenuate);
			v3SamplePoint.Add(v3SampleRay);
		}
		mieColor = v3FrontColor;
		mieColor.Scale(g_testAtmos.fKmESun);
		rayColor = v3FrontColor;
		CVector3 vWk;
		vWk = g_testAtmos.v3InvWavelength;
		vWk.Scale(g_testAtmos.fKrESun);
		rayColor.x = v3FrontColor.x * vWk.x;
		rayColor.y = v3FrontColor.y * vWk.y;
		rayColor.z = v3FrontColor.z * vWk.z;
	}
}
GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}
void GameScene::OnDestroy()
{
	DeleteGO(map);
	DeleteGO(ground);
	DeleteGO(playerHPBar);
	DeleteGO(playerMPBar);
	DeleteGO(sky);
	//DeleteGO(g_car);
	DeleteGO(g_player);
	DeleteGO(g_enemyManager);
	//DeleteGO(unityChanInstance);
	DeleteGO(g_damageCollisionWorld);
	DeleteGO(g_camera);
	DeleteGO(&bgmSoundSource);
	DeleteGO(gameOver2D);
}
bool GameScene::Start()
{
	switch (initStep) {
	case InitStep_Load:	
		//unityChanInstance = NewGO<UnityChanInstance>(0);
		map = NewGO<Map>(0);
		ground = NewGO<Ground>(0);
		g_enemyManager = NewGO<EnemyManager>(0);
		playerHPBar = NewGO<PlayerHPBar>(0);
		playerMPBar = NewGO<PlayerMPBar>(0);
		g_damageCollisionWorld = NewGO<DamageCollisionWorld>(0);
		g_player = NewGO<Player>(0);
		sky = NewGO<Sky>(0);
		sky->SetPlayer(g_player);
		//g_car = NewGO<Car>(0);
		g_camera = NewGO<GameCamera>(0);
		g_player->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
		g_camera->SetPlayer(g_player);
		MotionBlur().SetCamera(&g_camera->GetCamera());

		bgmSoundSource.InitStreaming("Assets/sound/wind.wav");
		bgmSoundSource.Play(true);
		bgmSoundSource.SetVolume(0.5f);
		AddGO(0, &bgmSoundSource);
		
		initStep = InitStep_WaitLoad;
		break;
	case InitStep_WaitLoad:
		if (g_player->IsStart()
			&& g_enemyManager->IsStart()
			&& map->IsStart()
			&& ground->IsStart()
			&& playerHPBar->IsStart()
			&& playerMPBar->IsStart()
			&& playerMPBar->IsStart()
			&& sky->IsStart()
		) {
			//全て初期化完了。
			g_nowLoading->SetActiveFlag(false);
			return true;
		}
		break;
	}
	
	return false;
}
void GameScene::Update() 
{
	const float km = 0.0010f;
	const float ESun = 30.0f;
	const float kr = 0.0025f;
	switch (state) {
	case State_Play: {
		if (g_player->GetState() == Player::enState_Dead) {
			//プレイヤーが死んだ。
			gameOver2D = NewGO<GameOver2D>(0);
			state = State_Over;
		}
		//待機錯乱のテスト

		//惑星の半径。

		g_testAtmos.fKm4PI = km * 4.0f * CMath::PI;
		g_testAtmos.fKmESun = km * ESun;

		g_testAtmos.fKr4PI = kr * 4.0f * CMath::PI;
		g_testAtmos.fKrESun = kr * ESun;
		g_testAtmos.fInnerRadius = 8.0f; //単位km
		g_testAtmos.fInnerRadius2 = g_testAtmos.fInnerRadius * g_testAtmos.fInnerRadius;
		g_testAtmos.fOuterRadius = g_testAtmos.fInnerRadius + (g_testAtmos.fInnerRadius * fScaleDepth*0.1f);
		g_testAtmos.fOuterRadius2 = g_testAtmos.fOuterRadius * g_testAtmos.fOuterRadius;

		g_testAtmos.fScale = 1.0f / (g_testAtmos.fOuterRadius - g_testAtmos.fInnerRadius);
		g_testAtmos.fScaleDepth = 0.25f;
		g_testAtmos.fScaleOverScaleDepth = (1.0f / (g_testAtmos.fOuterRadius - g_testAtmos.fInnerRadius)) / g_testAtmos.fScaleDepth;
		g_testAtmos.g = -0.990f;
		g_testAtmos.g2 = g_testAtmos.g * g_testAtmos.g;

		float fWavelength[3], fWavelength4[3];
		fWavelength[0] = 0.650f;		// 650 nm for red
		fWavelength[1] = 0.570f;		// 570 nm for green
		fWavelength[2] = 0.475f;		// 475 nm for blue
		fWavelength4[0] = powf(fWavelength[0], 4.0f);
		fWavelength4[1] = powf(fWavelength[1], 4.0f);
		fWavelength4[2] = powf(fWavelength[2], 4.0f);
		g_testAtmos.v3InvWavelength.Set(1 / fWavelength4[0], 1 / fWavelength4[1], 1 / fWavelength4[2]);
		g_testAtmos.v3LightPos.Set(0.0f, 50.0f, -1000.0f);
		g_testAtmos.v3LightDirection = g_testAtmos.v3LightPos;
		g_testAtmos.v3LightDirection.Normalize();
		CVector3 cameraPos = g_camera->GetCamera().GetPosition();
		cameraPos.Scale(0.001f);
		cameraPos.y += g_testAtmos.fInnerRadius;
		g_testAtmos.fCameraHeight = cameraPos.Length();
		g_testAtmos.fCameraHeight2 = g_testAtmos.fCameraHeight * g_testAtmos.fCameraHeight;
		CVector4 mieColor, rayColor;
		CVector3 posToCameraDir;
		CalcMieAndRayleighColors(mieColor, rayColor, posToCameraDir, {0.0f, 0.0f, 0.0f});
	}break;
	case State_Over:
		gameOverTimer += GameTime().GetFrameDeltaTime();
		if (gameOverTimer > 6.0f) {
			//死亡して2秒以上経過した。
			DeleteGO(this);
			g_nowLoading->SetActiveFlag(true);
			gameScene = NewGO<GameScene>(0);
		}
		break;
	}
}