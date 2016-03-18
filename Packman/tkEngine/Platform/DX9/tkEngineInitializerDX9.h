/*!
 * @brief	DX9向けのエンジン初期化
 */

#ifndef _TKENGINEINITIALIZERDX9_H_
#define _TKENGINEINITIALIZERDX9_H_

#include "tkEngine\tkEngine.h"

namespace tkEngine{
	/*!
	 * @brief	DX9向けのエンジンの初期化処理
	 */
	class EngineInitializerDX9 : public IEngineInitializer{
	public:
		EngineInitializerDX9()
		{
		}
		~EngineInitializerDX9()
		{
		}
		/*!
		 * @brief	初期化処理の実行
		 */
		void Execute( const InitParam& initParam ) final;
	};
}

#endif // _TKENGINEINITIALIZERDX9_H_

