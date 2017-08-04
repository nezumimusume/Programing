/*!
 *@brief	ディレクションライト
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	/*!
	 *@brief	ディレクションライト。
	 */
	class CDirectionLight : public IGameObject{
	public:
		CDirectionLight();
		~CDirectionLight();
		bool Start() override;
		void Update() override;
	private:
		SDirectionLight		light;		//!<ライト。
	};
}