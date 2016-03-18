/*!
 * @brief	tkEngine
 */
 

#ifndef _TKENGINE_H_
#define _TKENGINE_H_

namespace tkEngine{
	/*!
	 * @brief	初期化用のパラメータ。
	 */
	struct InitParam{
#if defined(TK_PLATFORM_DX9)
		HINSTANCE hInstance;
#else //#if defined(TK_PLATFORM_DX9)
 #error "サポートされていないプラットフォームです。"
#endif //
	};
	/*!
	 * @brief	エンジン初期化のインターフェース。
	 */
	class IEngineInitializer : Noncopyable{
	public:
		IEngineInitializer(){}
		virtual ~IEngineInitializer(){}
		/*!
		 * @brief	初期化処理の実行。
		 */
		virtual void Execute( const InitParam& initParam ) = 0;
	};
	
	/*!
	 * @brief	エンジンの終了処理のインターフェース。
	 */
	class IEngineFinalizer : Noncopyable{
	public:
		IEngineFinalizer() {}
		virtual ~IEngineFinalizer() {}
		/*!
		 * @brief	終了処理の実行。
		 */
		virtual void Execute() = 0;
	};
	/*!
	 * @brief	エンジン。
	 */
	class Engine : Noncopyable {
		Engine() {}
		~Engine() {}
	public:
		/*!
		 * @brief	初期化。
		 *@param[in]	初期化パラメータ
		 */
		void Init( const InitParam& initParam );
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
		static Engine* GetInstance()
		{
			static Engine instance;
			return &instance;
		}
	private:
		std::unique_ptr<IEngineInitializer>	m_initializer;	//!<初期化処理。
		std::unique_ptr<IEngineFinalizer>	m_finalizer;	//!<終了処理。
	};
	
}

#if defined(TK_PLATFORM_DX9)
	#include "tkEngine/Platform/DX9/tkEngineInitializerDX9.h"
	#include "tkEngine/Platform/DX9/tkEngineFinalizerDX9.h"
#else // #if defined(TK_PLATFORM_DX9)

#error "対応されていないプラットフォームです。"
#endif //#if defined(TK_PLATFORM_DX9)
#endif // _TKENGINE_TKENGINE_H_
