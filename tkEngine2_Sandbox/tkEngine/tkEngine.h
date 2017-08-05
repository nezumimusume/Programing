/*!
 *@brief	エンジン。
 */
#pragma once

#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/timer/tkStopwatch.h"
#include "tkEngine/Sound/tkSoundEngine.h"
#include "tkEngine/graphics/tkGraphicsEngine.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"

namespace tkEngine{
	/*!
	 *@brief	エンジン。
	 */
	class CEngine : Noncopyable {
	private:
		/*!
		 *@brief	コンストラクタ。
		 */
		CEngine();
		/*!
		 *@brief	デストラクタ。
		 */
		~CEngine();
	public:
		/*!
		 *@brief	初期化。
		 *@param[in]	initParam		初期化パラメータ。
		 */
		bool Init( const SInitParam& initParam );
		/*!
		 *@brief	終了処理。
		 */
		void Final();
		/*!
		 *@brief	ゲームループを実行。
		 */
		void RunGameLoop();
		/*!
		 *@brief	インスタンスを取得。
		 */
		static CEngine& GetInstance()
		{
			static CEngine* instance = nullptr;
			if(instance == nullptr){
				instance = new CEngine;
			}
			return *instance;
		}
		
		/*!
		* @brief	ゲームパッドの取得。
		*@param[in]	padNo	パッド番号
		*/
		CPad& GetPad(int padNo)
		{
			TK_ASSERT(padNo < CPad::CONNECT_PAD_MAX && padNo >= 0, "padNo is invalid");
			return m_pad[padNo];
		}
		/*!
		* @brief	サウンドエンジンの取得。
		*/
		CSoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		/*!
		* @brief	グラフィックスエンジンの取得。
		*/
		CGraphicsEngine& GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/*!
		* @brief	ZPrepassの取得。
		*/
		CZPrepass& GetZPrepass()
		{
			return m_graphicsEngine.GetZPrepass();
		}
		
		/*!
		*@brief	メインカメラを取得。
		*/
		CCamera& GetMainCamera()
		{
			return m_graphicsEngine.GetMainCamera();
		}
		/*!
		*@brief	ライトの管理者を取得。
		*/
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}
	private:
		/*!
		 *@brief	ウィンドウ初期化。
		 */
		bool InitWindow( const SInitParam& initParam );

		/*!
		* @brief	ウィンドウプロシージャ。
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		/*!
		* @brief	更新。
		*/
		void Update();
	private:
		HINSTANCE				m_hInst = nullptr;	//!<アプリケーションのインスタンス。
		HWND					m_hWnd = nullptr;	//!<ウィンドウハンドル。
		CGraphicsEngine			m_graphicsEngine;							//!<グラフィックエンジン。
		CSoundEngine			m_soundEngine;								//!<サウンドエンジン。
		CLightManager			m_lightManager;								//!<ライトの管理者。
		int						m_screenWidth = 0;							//!<スクリーンの幅。
		int						m_screenHeight = 0;							//!<スクリーンの高さ。
		CPad					m_pad[CPad::CONNECT_PAD_MAX];				//!<ゲームパッド。
	public:
		CStopwatch				m_sw;
	};

	/*!
	* @brief	Engineのインスタンスを取得。
	*/
	static inline CEngine& Engine()
	{
		return CEngine::GetInstance();
	}
	/*!
	* @brief	CPadのインスタンスを取得。
	*/
	static inline CPad& Pad(int padNo)
	{
		return Engine().GetPad(padNo);
	}
	/*!
	* @brief	CSoundEngineのインスタンスを取得。
	*/
	static inline CSoundEngine& SoundEngine()
	{
		return Engine().GetSoundEngine();
	}
	/*!
	* @brief	CGraphicsEngineのインスタンスを取得。
	*/
	static inline CGraphicsEngine& GraphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
	/*!
	* @brief	メインカメラのインスタンスを取得。
	*/
	static inline CCamera& MainCamera()
	{
		return GraphicsEngine().GetMainCamera();
	}
	/*!
	* @brief	CLightManagerのインスタンスを取得。
	*/
	static inline CLightManager& LightManager()
	{
		return Engine().GetLightManager();
	}
	
}