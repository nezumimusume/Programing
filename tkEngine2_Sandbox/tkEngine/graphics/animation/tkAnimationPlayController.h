/*!
 * @brief	�A�j���[�V�����Đ��R���g���[���B
 */

#pragma once


namespace tkEngine{
	/*!
	 * @brief	�A�j���[�V�����̍Đ��R���g���[���B
	 * @details
	 *  ��̃A�j���[�V�����N���b�v�ɑ΂��ăA�j���[�V������i�߂āA���[�J���|�[�Y���v�Z���܂��B
	 */
	class CAnimationPlayController{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CAnimationPlayController()
		{
		}
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CAnimationPlayController()
		{
		}
		/*!
		 *@brief	�������B
		 */
		void Init(CSkeleton* skeleton);
		/*!
		 * @brief	�A�j���[�V�����N���b�v�̕ύX�B
		 */
		void ChangeAnimationClip(CAnimationClip* clip)
		{
			m_animationClip = clip;
			m_currentKeyFrameNo = 0;
			m_time = 0.0f;
		}
		void SetInterpolateTime(float interpolateTime)
		{
			if (interpolateTime < 0.0f) {
				TK_WARNING("interpolateTime is negative!!");
			}
			m_interpolateEndTime = interpolateTime;
			m_interpolateTime = 0.0f;
		}
		/*!
		 *@brief	�⊮�����擾�B
		 */
		float GetInterpolateRate() const
		{
			return min( 1.0f, m_interpolateTime / m_interpolateEndTime );
		}
		/*!
		 * @brief	�A�j���[�V������i�߂�B
		 *@param[in]	deltaTime		�A�j���[�V������i�߂鎞�ԁB
		 */
		void Update(float deltaTime);
		/*!
		 * @brief	���[�J���{�[���s����擾�B
		 */
		const std::vector<CMatrix>& GetBoneLocalMatrix() const
		{
			return m_boneMatrix;
		}
		CAnimationClip* GetAnimClip() const
		{
			return m_animationClip;
		}
	private:
		CAnimationClip*			m_animationClip = nullptr;		//!<�A�j���[�V�����N���b�v�B
		int						m_currentKeyFrameNo = 0;	//!<���ݍĐ����̃L�[�t���[���ԍ��B
		float					m_time = 0.0f;
		std::vector<CMatrix>	m_boneMatrix;			//!<���̃R���g���[���ōĐ����̃A�j���[�V�����̃{�[���s��B
		float					m_interpolateTime;		//!<�⊮����
		float					m_interpolateEndTime;	//!<�⊮�I������
	};
}