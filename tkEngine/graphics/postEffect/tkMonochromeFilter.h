/*!
 * @brief	モノクロフィルター。
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkIPostEffectFilter.h"

namespace tkEngine{
	/*!
	 * @brief	モノクロフィルタ
	 */
	class CMonochromeFilter : public IPostEffectFilter{
	public:
		CMonochromeFilter();
		~CMonochromeFilter();
		void Create(const SGraphicsConfig& config );
	};
}
