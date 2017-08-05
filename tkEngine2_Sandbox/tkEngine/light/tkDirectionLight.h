/*!
 *@brief	ディレクションライト
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	/*!
	 *@brief	ディレクションライト。
	 */
	class CDirectionLight : public CLightBase{
	public:
		CDirectionLight();
		~CDirectionLight();
		bool StartSub() override;
		void Update() override;
	private:
		SDirectionLight		light;		//!<ライト。
	};
}