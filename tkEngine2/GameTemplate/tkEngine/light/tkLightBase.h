/*!
 * @brief	ライトの基底クラス。
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	ライトの基底クラス。
		 */
		class CLightBase : public IGameObject {
		public:
			bool Start() override final;
			void OnDestroy() override final;
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestorySub() {}

		};
	}
}