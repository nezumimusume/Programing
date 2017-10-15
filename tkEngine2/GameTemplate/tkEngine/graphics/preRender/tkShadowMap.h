/*!
 * @brief	�V���h�E�}�b�v
 */

#pragma once

namespace tkEngine{
	class IShadowCaster;
	/*!
	 * @brief	�V���h�E�}�b�v�B
	 */
	class CShadowMap : Noncopyable{
	public:
		static const int NUM_SHADOW_MAP = 3;	//�V���h�E�}�b�v�̖����B
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CShadowMap();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CShadowMap();
		/*!
		 * @brief	�V���h�E�}�b�v�̍쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 *@return	true���Ԃ��Ă�����V���h�E�}�b�v�̍쐬�����B
		 */
		bool Init( const SShadowRenderConfig& config );
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/*!
		 *@brief	�e�𗎂Ƃ����߂̃p�����[�^��GPU�ɓ]������B
		 */
		void SendShadowReceiveParamToGPU(CRenderContext& rc);
		/*!
		 *@brief	�V���h�E�}�b�v�֏������݁B
		 */
		void RenderToShadowMap(CRenderContext& rc);
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		* @brief	�V���h�E�L���X�^�[���G���g���[�B
		*/
		void Entry(IShadowCaster* caster);
		/*!
		 *@brief	���C�g�̕�����ݒ�B
		 */
		void SetLightDirection(const CVector3 lightDir)
		{
			m_lightDirection = lightDir;
		}
		
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetFar(float Far)
		{
			m_far = Far;
		}
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetNear(float Near)
		{
			m_near = Near;
		}
	private:
		/*!
		 *@brief	���̒��g��ύX������AmodelCB.h��ShadowCb���ύX����悤�ɁB
		 */
		struct SShadowCb {
			CMatrix mLVP[NUM_SHADOW_MAP];
		};
		bool m_isEnable = false;							//!<�e�̏������L���H
		CVector3 m_lightDirection = CVector3::Down;			//!<���C�g�̕����B
		float m_near = 0.1f;								//!<�ߕ��ʁB
		float m_far = 100.0f;								//!<�����ʁB
		float m_accpect = 1.0f;								//!<�A�X�y�N�g�B�s�v�H
		float m_shadowAreaW[NUM_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̕��B
		float m_shadowAreaH[NUM_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̍����B
		CRenderTarget	m_shadowMapRT[NUM_SHADOW_MAP];		//!<�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
		std::vector<IShadowCaster*> m_shadowCaster;			//!<�V���h�E�L���X�^�[�B
		CMatrix	m_LVPMatrix[NUM_SHADOW_MAP] = { CMatrix::Identity };				//!<���C�g�r���[�v���W�F�N�V�����s��B
		SShadowCb m_shadowCbEntity;
		CConstantBuffer m_shadowCb;							//!<�e�𗎂Ƃ����Ɏg�p����萔�o�b�t�@�B
	};
}