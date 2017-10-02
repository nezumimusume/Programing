/*!
 * @brief	�ǂ��g�������_�����O�X�e�[�g���܂Ƃ߂����́B
 */

#pragma once

namespace tkEngine{
	/*!
	* @brief	���u�����h�X�e�[�g�B
	*/
	struct AlphaBlendState {
		static ID3D11BlendState*	disable;	//!<�A���t�@�u�����f�B���O�������B
		static ID3D11BlendState*	trans;		//!<�����������B
		static ID3D11BlendState*	add;		//!<���Z�����B
		/*!
		* @brief	�������B
		*@param[in]	ge		�O���t�B�b�N�G���W��
		*/
		static void Init(CGraphicsEngine& ge);
	};
	/*!
	* @brief	�[�x�X�e���V���X�e�[�g�B�B
	*/
	struct DepthStencilState
	{
		static ID3D11DepthStencilState* disable;			//!<���ׂĖ����B
		static ID3D11DepthStencilState* SceneRender;		//!<3D���f����`�悷�鎞�̊�{�I�Ȑ[�x�X�e���V���X�e�[�g�B
															//!<�[�x�e�X�g�A�[�x�������݂Ƃ��ɗL���ȃX�e�[�g�ł��B

		/*!
		* @brief	�������B
		*@param[in]	ge		�O���t�B�b�N�G���W��
		*/
		static void Init(CGraphicsEngine& ge);
	};
}