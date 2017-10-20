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
			/*!
			*@brief ライトの影響を与えるオブジェクトを識別するためのマスクを設定。
			*@details
			* 0xFFFFFFFFを指定すると、すべてのオブジェクトにライトを当てます。
			*/
			void SetMask(unsigned int mask)
			{
				m_mask = mask;
			}
			/*!
			*@brief ライトの影響を与えるオブジェクトを識別するためのマスクを取得。
			*/
			unsigned int GetMask() const
			{
				return m_mask;
			}
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestorySub() {}
		private:
			unsigned int m_mask;	//!<ライトの影響を与える相手を識別するためのマスク。0xFFFFFFFFですべてのオブジェクトにライトを当てる。
		};
	}
}