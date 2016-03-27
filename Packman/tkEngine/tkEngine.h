/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

#include "tkEngine/graphics/tkRenderContext.h"
#include "tkEngine/graphics/tkEffectManager.h"

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
		s32					screenWidth;			//!<スクリーンの幅。
		s32					screenHeight;			//!<スクリーンの高さ。
	};
	
	/*!
	 * @brief	エンジン。
	 */
	class CEngine : Noncopyable {
		CEngine() : 
			m_hWnd(nullptr),
			m_pD3D(nullptr),
			m_pD3DDevice(nullptr)
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
		s32 GetScreenWidth() const
		{
			return m_screenWidth;
		}
		/*!
		*@brief		スクリーンの高さを取得
		*/
		s32 GetScreenHeight() const
		{
			return m_screenHeight;
		}
	private:
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
		bool InitDirectX();
		/*!
		* @brief	ウィンドウプロシージャ。
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND									m_hWnd;					//!<ウィンドウハンドル。
		LPDIRECT3D9								m_pD3D;					//!<D3DDevice
		LPDIRECT3DDEVICE9						m_pD3DDevice;			//!<Rendering device
		std::unique_ptr<CRenderContext[]>		m_renderContextArray;	//!<レンダリングコンテキスト
		u32										m_numRenderContext;		//!<レンダリングコンテキストの数。
		std::unique_ptr<SRenderContextMap[]>	m_renderContextMap;		//!<レンダリングコンテキストのマップ。
		CEffectManager							m_effectManager;		//!<エフェクトマネージャ。
		s32										m_screenWidth;			//!<スクリーンの幅。
		s32										m_screenHeight;			//!<スクリーンの高さ。
	};
	
}

#endif // _TKENGINE_TKENGINE_H_
