/*!
 * @brief	セピアフィルター。
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine{
	/*!
	 * @brief	セピアフィルタ
	 */
	class CSepiaFilter : public IPostEffectFilter{
	public:
		CSepiaFilter();
		~CSepiaFilter();
		void Create(const SGraphicsConfig& config );
	};
}
