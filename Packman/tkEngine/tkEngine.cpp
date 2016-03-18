/*!
 * @brief	tkEngine
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	/*!
	 * @brief	初期化。
	 */
	void Engine::Init(const InitParam& initParam)
	{
		m_initializer.reset( new EngineInitializerDX9 );
		m_finalizer.reset( new EngineFinalizerDX9 );
		m_initializer->Execute( initParam );
	}
	/*!
	* @brief	ゲームループを実行。
	*/
	void Engine::RunGameLoop()
	{

	}
	/*!
	 * @brief	終了処理。
	 */
	void Engine::Final()
	{
		m_finalizer->Execute();
		m_finalizer.reset();
		m_initializer.reset();
	}
}// namespace tkEngine
