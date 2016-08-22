/*!
 * @brief	ブラー。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	ブラー。
	 */
	class CBlur{
	public:
		CBlur();
		~CBlur();
		void Init( int w, int h, const CTexture& srcTexture );
		void Draw(CRenderContext& renderContext);
		const CTexture* GetTexture() const
		{
			return m_rt[1].GetTexture();
		}

	private:
		CRenderTarget		m_rt[2];			//!<ガウシアンブラーの結果を描きこむレンダリングターゲット。
		const CTexture*		m_srcTexture;		//!<ソースとなるテクスチャ。
		CPrimitive			m_prim;				//!<プリミティブ。
		CEffect*			m_effect;			//!<エフェクト。
		int					m_srcTexWH[2];
	};
}