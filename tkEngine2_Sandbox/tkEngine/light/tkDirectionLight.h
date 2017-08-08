/*!
 *@brief	ディレクションライト
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	ディレクションライト。
		 */
		class CDirectionLight : public CLightBase {
		public:
			CDirectionLight();
			~CDirectionLight();
			bool StartSub() override final;
			void Update() override final;
			/*!
			*@brief ライトの方向を設定。
			*@param[in]	direction	ライトの方向。
			*/
			void SetDirection(const CVector3& direction);
			/*!
			*@brief ライトのカラーを設定。
			*@param[in]	color	ライトのカラー。
			*/
			void SetColor(const CVector3& color);
			/*!
			*@brief 生データの取得。
			*/
			SDirectionLight& GetRawData()
			{
				return light;
			}
		private:
			SDirectionLight		light;		//!<ライト。
		};
	}
}