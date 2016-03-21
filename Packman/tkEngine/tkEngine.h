/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

#include "tkEngine/graphics/tkRenderContext.h"

namespace tkEngine{
	/*!
	 * @brief	初期化用のパラメータ。
	 */
	struct SInitParam{
		HINSTANCE 	hInstance;
		u8 			gameObjectPrioMax;		//!<ゲームオブジェクトの優先度の最大値(255まで)
		u32 		numRenderContext;		//!<レンダリングコンテキストの数
		u32*		commandBufferSizeTbl;	//!<コマンドバッファのサイズのテーブル。レンダリングコンテキストのサイズ分必要。
	};
	
	/*!
	 * @brief	エンジン。
	 */
	class CEngine : Noncopyable {
		CEngine() : 
			m_hWnd(NULL),
			m_pD3D(NULL),
			m_pD3DDevice(NULL)
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
		static CEngine& GetInstance()
		{
			static CEngine instance;
			return instance;
		}
	private:
		/*!
		* @brief	ウィンドウ初期化。
		* @retval	true	初期化に成功。
		* @retval	false	初期化に失敗。
		*/
		bool InitWindow();
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
		HWND								m_hWnd;					//!<ウィンドウハンドル。
		LPDIRECT3D9							m_pD3D;					//!<D3DDevice
		LPDIRECT3DDEVICE9					m_pD3DDevice;			//!<Rendering device
		std::unique_ptr<CRenderContext[]>	m_renderContextArray;	//!<レンダリングコンテキスト
		u32									m_numRenderContext;		//!<レンダリングコンテキストの数。
	};
	
}

#endif // _TKENGINE_TKENGINE_H_
