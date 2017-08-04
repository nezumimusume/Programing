/*!
 *@brief	ポイントライト
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	/*!
	 *@brief	ポイントライト。
	 */
	class CPointLight : public IGameObject{
	public:
		CPointLight();
		~CPointLight();
		bool Start() override;
		void Update() override;
	private:
		SPointLight	light;		
	};
}