/*!
 * @brief	シャドウマップ。
 */

#ifndef _TKSHADOWMAP_H_
#define _TKSHADOWMAP_H_

namespace tkEngine{
	/*!
	 * @brief	影モデル。
	 */
	class CShadowModel{
	public:
		CShadowModel();
		~CShadowModel();
		/*!
		 * @brief	プリミティブから作成。
		 */
		void Create( CPrimitive* prmi );
		/*!
		 * @brief	ワールド行列を設定。
		 */
		void SetWorldMatrix( const CMatrix& mWorld )
		{
			m_mWorld = mWorld;
		}
		/*!
		 * @brief	描画。
		 */
		void Render( CRenderContext& renderContext, CEffect* pEffect, const CMatrix& mLVP );
	private:
		CPrimitive*		m_prim;		//!<プリミティブ。
		CMatrix			m_mWorld;	//!<ワールド行列を設定。
	};
	class CShadowMap : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CShadowMap();
		/*!
		 * @brief	デストラクタ。
		 */
		~CShadowMap();
		/*!
		 * @brief	作成。
		 */
		void Create( int w, int h );
		/*!
		 * @brief	開放。
		 */
		void Release();
		/*!
		 * @brief	影モデルをエントリー。
		 */
		void Entry( CShadowModel* model );
		/*!
		 * @brief	シャドウマップに書き込み。
		 *@param[in]	renderContext		レンダリングコンテキスト。
		 */
		void RenderToShadowMap( CRenderContext& renderContext );
		/*!
		 * @brief	シャドウマップのテクスチャを取得。
		 */
		CTexture* GetTexture()
		{
			return m_shadowMapRT.GetTexture();
		}
		/*!
		 * @brief	ライトの方向を設定。
		 */
		void SetLightDirection( const CVector3& lightDir )
		{
			m_lightDirection = lightDir;
		}
		/*!
		 * @brief	ライトの位置を設定。
		 */
		void SetLightPosition( const CVector3& lightPosition )
		{
			m_lightPosition = lightPosition;
		}
		/*!
		* @brief	ライトビュープロジェクション行列を取得。
		*/
		const CMatrix& GetLVPMatrix() const
		{
			return m_LVPMatrix;
		}
		/*!
		* @brief	遠平面を設定。
		*/
		void SetFar(float Far)
		{
			m_far = Far;
		}
		/*!
		* @brief	遠平面を設定。
		*/
		void SetNear(float Near)
		{
			m_far = Near;
		}
		/*!
		* @brief	更新。
		*/
		void Update();
		/*!
		* @brief	近平面。
		*/
		float GetNear() const
		{
			return m_near;
		}
		/*!
		* @brief	遠平面
		*/
		float GetFar() const
		{
			return m_far;
		}
	private:
		bool						m_isEnable;			//!<有効？
		CRenderTarget				m_shadowMapRT;		//!<シャドウマップを書き込むレンダリングターゲット。
		std::vector<CShadowModel*>	m_shadowModels;		//!<シャドウマップに書き込みを行う影モデル。
		CEffect*					m_pShadowMapEffect;	//!<シャドウマップのエフェクト。
		CVector3					m_lightPosition;	//!<ライトの位置。
		CVector3					m_lightDirection;	//!<ライトの向き。
		CMatrix						m_lvMatrix;
		CMatrix						m_LVPMatrix;		//!<ライトビュープロジェクション行列。
		CMatrix						m_projectionMatrix;
		float						m_near;				//!<近平面。
		float						m_far;				//!<遠平面。
	};
}

#endif //_TKSHADOWMAP_H_