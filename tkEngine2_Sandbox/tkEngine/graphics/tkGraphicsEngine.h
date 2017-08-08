/*!
 *@brief	描画エンジン
 */

#pragma once


#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"

namespace tkEngine{
	/*!
	 *@brief	描画エンジン。
	 */
	class CGraphicsEngine : Noncopyable{
	public:
		CGraphicsEngine();
		~CGraphicsEngine();
		/*!
		* @brief	初期化。
		*/
		bool Init(HWND hwnd, const SInitParam& initParam);
		/*!
		* @brief	開放。
		*/
		void Release();
		/*!
		* @brief	ZPrepassの取得。
		*/
		CZPrepass& GetZPrepass()
		{
			return m_preRender.GetZPrepass();
		}
		/*!
		*@brief	メインカメラを取得。
		*/
		CCamera& GetMainCamera()
		{
			return m_mainCamera;
		}
		/*!
		*@brief	Direct3DDeviceの取得。
		*/
		ID3D11Device* GetD3DDevice() const
		{
			return m_pd3dDevice;
		}
		/*!
		*@brief	ID3D11DeviceContextの取得。
		*/
		ID3D11DeviceContext* GetD3DDeviceContext() const
		{
			return m_pImmediateContext;
		}
		/*!
		*@brief		フレームバッファの幅を取得。
		*/
		int GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/*!
		*@brief		フレームバッファの高さを取得。
		*/
		int GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/*!
		* @brief	メインレンダリングターゲットを切り替え。
		*/
		void ToggleMainRenderTarget()
		{
			m_currentMainRenderTarget ^= 1;
		}
		/*!
		* @brief	メインレンダリングターゲットの取得。
		*/
		CRenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget[m_currentMainRenderTarget];
		}
		/*!
		* @brief	描画開始。
		*/
		void BeginRender();
		/*!
		* @brief	描画終了。
		*/
		void EndRender();
		CPreRender& GetPreRender()
		{
			return m_preRender;
		}
		CRenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/*!
		*@brief	ライトの管理者を取得。
		*/
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}
	private:
		ID3D11Device*			m_pd3dDevice = nullptr;						//!<D3D11デバイス。
		CRenderContext			m_renderContext;							//!<レンダリングコンテキスト。
		ID3D11DeviceContext*	m_pImmediateContext = nullptr;				//!<D3D11即時デバイスコンテキスト。
		IDXGISwapChain*			m_pSwapChain = nullptr;						//!<SwapChain。
		int						m_currentMainRenderTarget = 0;				//!<現在のメインレンダリングターゲット。
		CRenderTarget			m_mainRenderTarget[2];						//!<メインレンダリングターゲット。
		CPreRender				m_preRender;								//!<プリレンダリング。
		CCamera					m_mainCamera;								//!<メインカメラ。
		int						m_frameBufferWidth = 0;						//!<フレームバッファの幅。これが内部解像度。
		int						m_frameBufferHeight = 0;					//!<フレームバッファの高さ。これが内部解像度。
		D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<ドライバの種類のオプション。
		D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;	//!<Direct3D デバイスのターゲットとなる機能セット。
		CLightManager			m_lightManager;								//!<ライトの管理者。
	};
}