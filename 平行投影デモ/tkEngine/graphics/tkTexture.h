/*!
 * @brief	テクスチャ。
 */

#ifndef _TKTEXTURE_H_
#define _TKTEXTURE_H_

namespace tkEngine{
	/*!
	 * @brief	テクスチャ。
	 */
	class CTexture{
	public:
		CTexture()
		{
		}
		~CTexture()
		{
		}
		void SetTextureDX( LPDIRECT3DTEXTURE9 tex )
		{
			m_tex = tex;
		}
		LPDIRECT3DTEXTURE9 GetTextureDX() 
		{
			return m_tex;
		}
	private:
		LPDIRECT3DTEXTURE9	m_tex;		//!<テクスチャ。
	};
}

#endif // _TKTEXTURE_H_