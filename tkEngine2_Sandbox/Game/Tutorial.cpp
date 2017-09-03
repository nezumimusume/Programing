/*!
 *@brief	PBRサンプル。
 */
#include "stdafx.h"
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/timer/tkStopwatch.h"
#include <time.h>
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/physics/tkMeshCollider.h"

using namespace tkEngine;



class PBRSample : public IGameObject {
	//マテリアルパラメータの数。
	static const int NUM_MATERIAL_PARAM = 3;
	//頂点。
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};
	/*!
	 * @brief	マテリアルパラメータ。
	 */
	struct MaterialParam{
		float roughness;		//!<粗さ
		float metallic;			//!<メタリック。
		float anisotropic;		//!<異方性反射。
	};
	static const int NUM_POINT_LIGHT = 1024;
	MaterialParam m_materialParam;				//マテリアルパラメータ。
	CConstantBuffer m_materialParamCB;			//マテリアルパラメータ用の定数バッファ。
	
	
	
	CSkinModelData skinModelData;
	CSkinModel skinModel;
	CAnimationClip animClip;
	CAnimation animation;
	prefab::CDirectionLight* m_directionLight[3] = { nullptr };
	prefab::CPointLight* m_pointLight[NUM_POINT_LIGHT] = {nullptr};
	
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::unique_ptr<DirectX::SpriteBatch>	m_bach;
	int m_cursorPos = 0;
public:

	bool Start() override
	{
		
		
		skinModelData.Load(L"Assets/modelData/skinTest");
		skinModel.Init(skinModelData);
		//アニメーションクリップのロード。
		animClip.Load(L"Assets/animData/test.tka", L"Test");
		animClip.SetLoopFlag(true);
		CAnimationClip* animClipList[] = {
			&animClip
		};
		animation.Init(skinModelData, animClipList, 1);

		//カメラを初期化。
		CCamera& mainCamera = MainCamera();
		mainCamera.SetPosition({ 0.0f, 15.0f, -200.0f });
		mainCamera.SetTarget({ 0.0f, 15.0f, 0.0f });
		mainCamera.SetUp({ 0.0f, 1.0f, 0.0f });
		mainCamera.SetNear(0.1f);
		mainCamera.Update();
		
		//ディレクションライトをシーンに追加。
		m_directionLight[0] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[0]->SetDirection({ 1.0f, 0.0f, 0.0f});
		m_directionLight[0]->SetColor({ 1.0f, 1.0f, 1.0f });

		//マテリアルパラメータを初期化。
		m_materialParam.roughness = 0.5f;
		m_materialParam.metallic = 0.5f;
		m_materialParam.anisotropic = 0.5f;
		m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			
		//フォントを初期化。
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// ポイントライトを初期化。
		static const int QuantizationSize = 1000;	//量子化サイズ。
		
		{
			for (int i = 0; i < 256; i++) {
				m_pointLight[i] = NewGO<prefab::CPointLight>(0);
				int ix = rand() % QuantizationSize;
				int iy = rand() % QuantizationSize;
				int iz = rand() % QuantizationSize;

				//0～999までの数字を0.0～1.0の範囲に変換する。
				float fnx = (float)ix / QuantizationSize;
				float fny = (float)iy / QuantizationSize;
				float fnz = (float)iz / QuantizationSize;
				//xとyは-1.0～1.0の範囲に変換する。
				fnx = (fnx - 0.5f) * 2.0f;
				fnz = (fnz - 0.5f) * 2.0f;
				//ポイントライトの位置をランダムに決定。
				m_pointLight[i]->SetPosition({ 50.0f * fnx , 5.0f * fny,  50.0f * fnz });

				int ir = rand() % QuantizationSize;
				int ig = rand() % QuantizationSize;
				int ib = rand() % QuantizationSize;

				//0～999までの数字を0.0～1.0の範囲に正規化して、ポイントライトのカラーをランダムに決定。
				m_pointLight[i]->SetColor({ 
					(float)ir / QuantizationSize , 
					(float)ig / QuantizationSize,
					(float)ib / QuantizationSize
				});
				
				m_pointLight[i]->SetAttn({
					5.0f,
					0.01f,
					0.01f
				});
				
			}
			m_pointLight[0]->SetPosition({0.0f, 10.0f, 0.0f});
		}
		return true;
	}
	void Update() override
	{
		//nonSkinModel.Update({0.0f, 0.0f, 0.0f}, CQuaternion::Identity, CVector3::One);
		CQuaternion qRot;
		qRot.SetRotation(CVector3::AxisX,CMath::PI * -0.5f);
		skinModel.Update({ 0.0f, 0.0f, 0.0f }, qRot, CVector3::One);
		animation.Update(1.0f / 60.0f);
		//マテリアルパラーメータを更新。
		if (Pad(0).IsTrigger(enButtonUp)) {
			m_cursorPos--;
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			m_cursorPos++;
		}
		
		m_cursorPos = min(NUM_MATERIAL_PARAM-1, m_cursorPos);
		m_cursorPos = max(0, m_cursorPos);

		float* params[] = {
			&m_materialParam.roughness,
			&m_materialParam.metallic,
			&m_materialParam.anisotropic
		};
		if (Pad(0).IsPress(enButtonLeft)) {
			*params[m_cursorPos] += 0.001f;
		}
		else if (Pad(0).IsPress(enButtonRight)) {
			*params[m_cursorPos] -= 0.001f;
		}
		*params[m_cursorPos] = max(*params[m_cursorPos], 0.0f);
		*params[m_cursorPos] = min(*params[m_cursorPos], 1.0f);

		//点光源を回してみる。
		qRot.SetRotationDeg(CVector3::AxisY, 0.2f);
		for (auto& ptLight : m_pointLight) {
			if (ptLight == NULL) {
				break;
			}
			CVector3 pointLightPos = ptLight->GetPosition();
			qRot.Multiply(pointLightPos);
			ptLight->SetPosition(pointLightPos);
		}

	}
	/*!------------------------------------------------------------------
	* @brief	シーンの描画。
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	
		rc.UpdateSubresource(m_materialParamCB, &m_materialParam);
		rc.PSSetConstantBuffer(2, m_materialParamCB);
		//nonSkinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
	
	/*!------------------------------------------------------------------
	* @brief	マテリアルパラメータを表示。
	------------------------------------------------------------------*/
	void RenderMaterialParam(CRenderContext& rc)
	{
		wchar_t fps[256];
		wchar_t cursor[NUM_MATERIAL_PARAM] = { L' ', L' ', L' ' };
		cursor[m_cursorPos] = L'>';
		wchar_t* fomat = L"%croughness %f\n"
						  "%cmetallic %f\n"
						  "%canisotropic %f\n";
		swprintf_s(fps, fomat, 
			cursor[0], m_materialParam.roughness, 
			cursor[1], m_materialParam.metallic,
			cursor[2], m_materialParam.anisotropic
		);
		CRenderTarget* rts[] = {
			&GraphicsEngine().GetMainRenderTarget()
		};
		rc.OMSetRenderTargets(1, rts);
		m_bach->Begin();

		m_font->DrawString(
			m_bach.get(),
			fps,
			DirectX::XMFLOAT2(0, 0),
			DirectX::Colors::White,
			0,
			DirectX::XMFLOAT2(0, 0),
			3.0f
		);
		m_bach->End();
	}
	/*!------------------------------------------------------------------
	* @brief	描画。
	------------------------------------------------------------------*/
	void Render(CRenderContext& rc) override
	{
		//シーンの描画。
		RenderScene(rc);
		//マテリアルパラーメータを表示。
		RenderMaterialParam(rc);
	}
};

/*!
 *@brief	メイン関数。
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
	srand((unsigned)time(NULL));
    //tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	
	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		//初期化に成功。
		NewGO<PBRSample>(0);
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();
	
    return 0;
}

