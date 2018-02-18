/*!
 * @brief	エフェクト
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	エフェクト。
		 */
		class CEffect : public IGameObject{
		public:
			CEffect();
			~CEffect();
			/*!
			 *@brief	解放。
			 */
			void Release();
			/*!
			 *@brief	エフェクトをロード。
			 */
			void Init(const wchar_t* filePath);
			/*!
			 *@brief	エフェクトを再生。
			 */
			void Play();
			/*!
			 *@brief	座標を設定。
			 */
			void SetPosition(const CVector3& pos)
			{
				m_position = pos;
			}
			/*!
			 *@brief	回転の設定。
			 */
			void SetRotation(const CQuaternion& rot)
			{
				m_rotation = rot;
			}
			bool IsPlay() const
			{
				return GraphicsEngine().GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
			}
			/*!
			 *@brief	更新。
			 */
			void Update() override;
		private:
			Effekseer::Effect*	m_effect = nullptr;
			Effekseer::Handle	m_handle = -1;
			CVector3 m_position = CVector3::Zero;			//!<座標。
			CQuaternion m_rotation = CQuaternion::Identity;	//!<回転。
		};
	}
}