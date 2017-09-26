/*!
 *@brief	PBRサンプル。
 */
#include "stdafx.h"


#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/timer/tkStopwatch.h"
#include <time.h>
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/physics/tkMeshCollider.h"
#include "Player.h"
#include "Background.h"
#include "GameCamera.h"

class PBRSample : public IGameObject {
	//マテリアルパラメータの数。
	static const int NUM_MATERIAL_PARAM = 3;
	//頂点。
	struct SSimpleVertex {
		CVector4 pos;
		CVector2 tex;
	};
	
	static const int NUM_POINT_LIGHT = 1024;	
	
	
	prefab::CDirectionLight* m_directionLight[3] = { nullptr };
	prefab::CPointLight* m_pointLight[NUM_POINT_LIGHT] = {nullptr};
	
	std::unique_ptr<DirectX::SpriteFont>	m_font;
	std::unique_ptr<DirectX::SpriteBatch>	m_bach;
	int m_cursorPos = 0;
	Player*		m_player;
public:

	bool Start() override
	{
		CMatrix mRot;
		mRot.MakeRotationY(0.785f);
		CVector3 right = CVector3::Right;
		mRot.Mul(right);
		
		
		//ディレクションライトをシーンに追加。
		m_directionLight[0] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[0]->SetDirection({ 0.707f, -0.707f, 0.0f});
		m_directionLight[0]->SetColor({ 0.2f, 0.2f, 0.2f, 0.0f });

		m_directionLight[1] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[1]->SetDirection({ 0.0f, -0.707f, -0.707f });
		m_directionLight[1]->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		
		m_directionLight[2] = NewGO<prefab::CDirectionLight>(0);
		m_directionLight[2]->SetDirection({ 1.0f, 0.0f, 0.0f });
		m_directionLight[2]->SetColor({ 0.2f, 0.2f, 0.2f, 1.0f });

			
		//フォントを初期化。
		m_font.reset(new DirectX::SpriteFont(GraphicsEngine().GetD3DDevice(), L"Assets/font/myfile.spritefont"));
		m_bach.reset(new DirectX::SpriteBatch(GraphicsEngine().GetD3DDeviceContext()));

		// ポイントライトを初期化。
		static const int QuantizationSize = 1000;	//量子化サイズ。
		
		{
			for (int i = 0; i < 32; i++) {
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
				m_pointLight[i]->SetPosition({ 200.0f * fnx , 100.0f,  200.0f * fnz });

				int ir = rand() % QuantizationSize;
				int ig = rand() % QuantizationSize;
				int ib = rand() % QuantizationSize;

				//0～999までの数字を0.0～1.0の範囲に正規化して、ポイントライトのカラーをランダムに決定。
				m_pointLight[i]->SetColor({ 
					(float)ir / QuantizationSize * 1.0f, 
					(float)ig / QuantizationSize * 1.0f,
					(float)ib / QuantizationSize * 1.0f,
					1.0f
				});
				
				m_pointLight[i]->SetAttn({
					150.0f,
					0.1f,
					0.1f
				});
				
			}
			//m_pointLight[0]->SetPosition({0.0f, 10.0f, 0.0f});
		}
		LightManager().SetAmbientLight({0.05f, 0.05f, 0.05f});
		m_player = NewGO<Player>(0, "Player");
		NewGO<Background>(0);
		NewGO<GameCamera>(0, "GameCamera");
		return true;
	}
	void Update() override
	{
		//マテリアルパラーメータを更新。
		if (Pad(0).IsTrigger(enButtonUp)) {
			m_cursorPos--;
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			m_cursorPos++;
		}
		
		m_cursorPos = min(NUM_MATERIAL_PARAM-1, m_cursorPos);
		m_cursorPos = max(0, m_cursorPos);


		//点光源を回してみる。
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY, 0.6f);
		
		for (auto& ptLight : m_pointLight) {
			if (ptLight) {
				CVector3 pos = ptLight->GetPosition();
				qRot.Multiply(pos);
				ptLight->SetPosition(pos);
			}
		}

	}
	/*!------------------------------------------------------------------
	* @brief	シーンの描画。
	------------------------------------------------------------------*/
	void RenderScene(CRenderContext& rc)
	{	

	}
	
	
	/*!------------------------------------------------------------------
	* @brief	描画。
	------------------------------------------------------------------*/
	void Render(CRenderContext& rc) override
	{
		//シーンの描画。
		RenderScene(rc);
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
	
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.isEnableSoftShadow = true;

	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);
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

