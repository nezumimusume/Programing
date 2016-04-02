/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

#include "tkEngine/graphics/tkRenderContext.h"
#include "tkEngine/graphics/tkEffectManager.h"
#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/graphics/tkPrimitive.h"
namespace tkEngine{
	/*!
	* @brief	描画優先ごとに対応するレンダリングコンテキストの番号のマップを定義するための構造体。
	*/
	struct SRenderContextMap {
		u8	startPrio;			//!<開始プライオリティ
		u32 renderContextNo;	//!<レンダリングコンテキストNo
	};
	/*!
	 * @brief	初期化用のパラメータ。
	 */
	struct SInitParam{
		SInitParam()
		{
			memset(this, 0, sizeof(SInitParam));
		}
		HINSTANCE 			hInstance;
		u8 					gameObjectPrioMax;		//!<ゲームオブジェクトの優先度の最大値(255まで)
		u32 				numRenderContext;		//!<レンダリングコンテキストの数。この数が2以上の場合、renderContextMapの指定が必ず必要になります。
		u32*				commandBufferSizeTbl;	//!<コマンドバッファのサイズのテーブル。レンダリングコンテキストのサイズ分必要。
		SRenderContextMap*	renderContextMap;		//!<描画優先ごとに対応するレンダリングコンテキストの番号のマップ。numRenderContextが1の場合は無視される。
		u32					screenWidth;			//!<スクリーンの幅。
		u32					screenHeight;			//!<スクリーンの高さ。
		u32					frameBufferWidth;		//!<フレームバッファの幅。これが内部解像度。
		u32					frameBufferHeight;		//!<フレームバッファの高さ。これが内部解像度。
	};
	
	/*!
	 * @brief	エンジン。
	 */
	class CEngine : Noncopyable {
		CEngine() : 
			m_hWnd(nullptr),
			m_pD3D(nullptr),
			m_pD3DDevice(nullptr),
			m_frameBufferHeight(0),
			m_frameBufferWidth(0),
			m_screenHeight(0),
			m_screenWidth(0),
			m_numRenderContext(0),
			m_pTransformedPrimEffect(nullptr)
		{}
		~CEngine() {}
	public:
		/*!
		 * @brief	初期化。
		 *@param[in]	初期化パラメータ
		 *@retval	true	初期化に成功。
		 *@retval	false	初期化に失敗。
		 */
		bool Init( const SInitParam& initParam );
		/*!
		 * @brief	終了処理。
		 */
		void Final();
		/*!
		 * @brief	ゲームループを実行。
		 */
		void RunGameLoop();
		/*!
		 * @brief	インスタンスの取得。
		 */
		static CEngine& Instance()
		{
			static CEngine instance;
			return instance;
		}
		/*!
		* @brief	エフェクトマネージャの取得。
		*/
		static CEffectManager& EffectManager()
		{
			return Instance().m_effectManager;
		}
		/*!
		 *@brief	Direct3DDeviceの取得。
		 */
		LPDIRECT3DDEVICE9 GetD3DDevice() const
		{
			return m_pD3DDevice;
		}
		/*!
		*@brief		スクリーンの幅を取得
		*/
		u32 GetScreenWidth() const
		{
			return m_screenWidth;
		}
		/*!
		*@brief		スクリーンの高さを取得
		*/
		u32 GetScreenHeight() const
		{
			return m_screenHeight;
		}
		/*!
		*@brief		フレームバッファの幅を取得。
		*/
		u32 GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/*!
		*@brief		フレームバッファの高さを取得。
		*/
		u32 GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
	private:
		/*!
		* @brief	メインレンダリングターゲットの内容をバックバッファにコピー。
		*/
		void CopyMainRenderTargetToBackBuffer(CRenderContext& renderContext);
		/*!
		* @brief	ウィンドウ初期化。
		* @retval	true	初期化に成功。
		* @retval	false	初期化に失敗。
		*/
		bool InitWindow(const SInitParam& initParam);
		/*!
		* @brief	DirectXの初期化。
		* @retval	true	初期化に成功。
		* @retval	false	初期化に失敗。
		*/
		bool InitDirectX(const SInitParam& initParam);
		/*!
		* @brief	メインレンダーターゲットをバックバッファにコピーするときに使うプリミティブを初期化。
		*/
		void InitCopyBackBufferPrimitive();
		/*!
		* @brief	ウィンドウプロシージャ。
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND									m_hWnd;						//!<ウィンドウハンドル。
		LPDIRECT3D9								m_pD3D;						//!<D3DDevice
		LPDIRECT3DDEVICE9						m_pD3DDevice;				//!<Rendering device
		std::unique_ptr<CRenderContext[]>		m_renderContextArray;		//!<レンダリングコンテキスト
		u32										m_numRenderContext;			//!<レンダリングコンテキストの数。
		std::unique_ptr<SRenderContextMap[]>	m_renderContextMap;			//!<レンダリングコンテキストのマップ。
		CEffectManager							m_effectManager;			//!<エフェクトマネージャ。
		u32										m_screenWidth;				//!<スクリーンの幅。
		u32										m_screenHeight;				//!<スクリーンの高さ。
		u32										m_frameBufferWidth;			//!<フレームバッファの幅。これが内部解像度。
		u32										m_frameBufferHeight;		//!<フレームバッファの高さ。これが内部解像度。
		CRenderTarget							m_mainRenderTarget;			//!<メインレンダリングターゲット
		CEffect*								m_pTransformedPrimEffect;	//!<トランスフォーム済みプリミティブを描画するためのエフェクト。
		CPrimitive								m_copyBackBufferPrim;		//!<メインレンダーターゲットをバックバッファにコピーするときに使うプリミティブ。
		CRenderTarget							m_backBufferRT;				//!<バックバッファのレンダリングターゲット。
	};
	
}

#endif // _TKENGINE_TKENGINE_H_
