/*!
 * @brief	�e�N�X�`���B
 */

#ifndef _TKTEXTURE_H_
#define _TKTEXTURE_H_

namespace tkEngine{
	/*!
	 * @brief	�e�N�X�`���B
	 */
	class CTexture{
	public:
		CTexture()
		{
		}
		~CTexture()
		{
			Release();
		}
		void SetTextureDX( LPDIRECT3DTEXTURE9 tex )
		{
			if (m_tex != NULL) {
				m_tex->Release();
			}
			m_tex = tex;
			m_tex->AddRef();
			ComputeTexSize();
		}
		LPDIRECT3DTEXTURE9 GetTextureDX() const
		{
			return m_tex;
		}
		LPDIRECT3DCUBETEXTURE9 GetCubeMapDX() const
		{
			return m_cubeTex;
		}
		void Release()
		{
			if (m_tex) {
				m_tex->Release();
				m_tex = nullptr;
			}
			if (m_cubeTex) {
				m_cubeTex->Release();
				m_cubeTex = nullptr;
			}
		}
		//�e�N�X�`���̕����擾�B
		int GetWidth() const
		{
			return m_texW;
		}
		//�e�N�X�`���̍������擾�B
		int GetHeight() const
		{
			return m_texH;
		}
		bool IsCubeMap() const
		{
			return m_cubeTex != nullptr;
		}
		/*!
		 * @brief	�e�N�X�`�������[�h�B
		 */
		bool Load( const char* fileName, bool isCubeMap = false);
		
	private:
		//�e�N�X�`���T�C�Y���v�Z�B
		void ComputeTexSize()
		{
			D3DSURFACE_DESC desc;
			if (m_tex) {
				m_tex->GetLevelDesc(0, &desc);
			}
			else if (m_cubeTex) {
				m_cubeTex->GetLevelDesc(0, &desc);
			}
			m_texW = desc.Width;
			m_texH = desc.Height;
		}
	private:
		LPDIRECT3DTEXTURE9	m_tex = nullptr;		//!<�e�N�X�`���B
		LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;	//!<�L���[�u�e�N�X�`���B
		int m_texW = 0;								//!<�e�N�X�`���̉����B
		int m_texH = 0;								//!<�e�N�X�`���̏c���B
	};
}

#endif // _TKTEXTURE_H_