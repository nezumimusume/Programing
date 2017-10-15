/*!
 *@brief	ShaderResourceView
 */

#pragma once

namespace tkEngine{
	class CStructuredBuffer;
	class CTextureData;
	/*!
	 *@brief	ShaderResourceView
	 *@details
	 * �e�N�X�`����X�g���N�`���o�b�t�@�ȂǁA�V�F�[�_�[�Ŏg�p���郊�\�[�X�Ŏg�p����r���[�B
	 */
	class CShaderResourceView : Noncopyable{
	public:
		CShaderResourceView();
		~CShaderResourceView();
		/*!
		 *@brief	StructuredBuffer�p��SRV���쐬�B
		 *@param[in]	structuredBuffer	structuredBuffer
		 */
		bool Create(CStructuredBuffer& structuredBuffer);
		/*!
		*@brief	�e�N�X�`���p��SRV���쐬�B
		*@param[in]	texture		�e�N�X�`���B
		*/
		bool Create(ID3D11Texture2D* texture);
		/*!
		*@brief	DDS�t�@�C������e�N�X�`���p��SRV���쐬�B
		*@param[in]	fileName		�t�@�C�����B
		*/
		bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
		/*!
		 *@brief	�����I�ȊJ���B
		 *@details
		 * �����I�ɊJ������K�v������Ƃ��Ɏg�p���Ă��������B
		 */
		void Release();
		/*!
		*@brief	ID3D11ShaderResourceView���擾�B
		*/
		ID3D11ShaderResourceView*& GetBody()
		{
			return m_srv;
		}
		/*!
		*@brief	�L���ȃr���[���ǂ�������B
		*/
		bool IsValid() const
		{
			return m_isValid;
		}
	private:
		ID3D11ShaderResourceView*		m_srv = nullptr;
		bool							m_isValid = false;	//!<�L���ȃf�[�^�H
	};
}