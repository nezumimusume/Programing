/*!
 * @brief	ガウシアンブラー。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	ガウシアンブラー。
	 */
	class CGaussianBlur{
	public:
		CGaussianBlur();
		~CGaussianBlur();
		void Init( int w, int h, const CTexture& srcTexture );
		void Draw(CRenderContext& renderContext);
		const CTexture* GetTexture() const
		{
			return m_rt[1].GetTexture();
		}

		void SetDispersion(float dispersion)
		{
			m_dispersion = dispersion;
			UpdateWeight();
		}
	private:
		/*!
		* @brief	ガウスフィルタの重みを更新。
		*/
		void UpdateWeight();
	private:
		static const int NUM_WEIGHTS = 8;
		float				m_weights[NUM_WEIGHTS];
		CRenderTarget		m_rt[2];			//!<ガウシアンブラーの結果を描きこむレンダリングターゲット。
		const CTexture*		m_srcTexture;		//!<ソースとなるテクスチャ。
		CPrimitive			m_prim;				//!<プリミティブ。
		CEffect*			m_effect;			//!<エフェクト。
		int					m_srcTexWH[2];
		float				m_dispersion;		//!<
	};
}