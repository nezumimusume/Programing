/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Tiger.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------

const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//ライトの色。
D3DXVECTOR4				g_ambientLight;						//環境光

const int NUM_TIGER = 2;	//トラの数。
Camera camera;				//カメラ。
Tiger tiger[NUM_TIGER];		//虎。



/*!-----------------------------------------------------------------------------
 *@brief	ライトを更新。
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	g_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
	g_diffuseLightDirection[3] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	
	//ディフューズライト。
	g_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	g_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.4f, 0.6f, 1.0f);
	g_diffuseLightColor[3] = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);

	//環境光。
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//ライトを初期化。
	ZeroMemory( g_diffuseLightDirection, sizeof(g_diffuseLightDirection) );
	ZeroMemory( g_diffuseLightColor, sizeof(g_diffuseLightColor) );
	
	//虎を初期化。
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Init(g_pd3dDevice);
		int y = i / 10;
		int x = i % 10;
		tiger[i].SetLocalPosition(D3DXVECTOR3(0.5f * x, 0.5f * y, 0.0f));
	}
	tiger[1].SetParent(&tiger[0]);
	//カメラの初期化。
	camera.Init();

}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	//トラを描画。
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			g_diffuseLightDirection,
			g_diffuseLightColor,
			g_ambientLight,
			LIGHT_NUM
			);
	}
	
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	//ライトの更新。
	UpdateLight();
	//カメラの更新
	camera.Update();
	//虎の更新。
	tiger[0].Update();
	tiger[1].Update();
	if (GetAsyncKeyState(VK_SHIFT)) {
		if (GetAsyncKeyState(VK_LEFT)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.x -= 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.x += 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_UP)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.y += 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			D3DXVECTOR3 pos = tiger[0].GetPosition();
			pos.y -= 0.02f;
			tiger[0].SetLocalPosition(pos);
		}
		if (GetAsyncKeyState('W')) {
			D3DXVECTOR3 pos = tiger[1].GetLocalPosition();
			pos.x -= 0.02f;
			tiger[1].SetLocalPosition(pos);
		}
	}
	else {
		if (GetAsyncKeyState(VK_LEFT)) {
			D3DXQUATERNION rot = tiger[0].GetRotation();
			D3DXQUATERNION addRot;
			D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.01f);
			rot = rot * addRot;
			tiger[0].SetLocalRotation(rot);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			D3DXQUATERNION rot = tiger[1].GetLocalRotation();
			D3DXQUATERNION addRot;
			D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.01f);
			rot = rot * addRot;
			tiger[1].SetLocalRotation(rot);
		}
	}
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	for (int i = 0; i < NUM_TIGER; i++) {
		tiger[i].Release();
	}
}
