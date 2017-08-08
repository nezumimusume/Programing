/*!
 *@brief	ポイントライト
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	ポイントライト。
		 */
		class CPointLight : public CLightBase {
		public:
			CPointLight();
			~CPointLight();
			bool StartSub() override final;
			void Update() override final;
			/*!
			*@brief 生データの取得。
			*/
			SPointLight& GetRawData()
			{
				return light;
			}
		private:
			SPointLight	light;
		};
	}
}