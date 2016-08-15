/*!
 * @brief	シャドウマップ。
 */

#ifndef _TKSHADOWMAP_H_
#define _TKSHADOWMAP_H_

#include "tkEngine/graphics/tkGaussianBlur.h"


namespace tkEngine{
	class IShadowCaster;
	class CCamera;
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
		 * @brief	シャドウキャスターをエントリー。
		 */
		void Entry( IShadowCaster* caster );
		/*!
		 * @brief	シャドウマップに書き込み。
		 *@param[in]	renderContext		レンダリングコンテキスト。
		 */
		void RenderToShadowMap( CRenderContext& renderContext );
		/*!
		 * @brief	シャドウマップのテクスチャを取得。
		 */
		const CTexture* GetTexture() const
		{
#ifdef USE_VSM
			//return m_gaussianBlur.GetTexture();
			return m_shadowMapRT.GetTexture();
#else
			return m_shadowMapRT.GetTexture();
#endif
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
		/*!
		* @brief	シャドウマップが有効か判定。
		*/
		bool IsEnable() const
		{
			return m_isEnable;
		}
		/*!
		* @brief	カメラを設定。PSMを行うときに使用される。
		*/
		void SetCamera(CCamera* camera)
		{
			m_camera = camera;
		}
	private:
		bool						m_isEnable;			//!<有効？
		CRenderTarget				m_shadowMapRT;		//!<シャドウマップを書き込むレンダリングターゲット。
		std::vector<IShadowCaster*>	m_shadowCaster;		//!<シャドウキャスター。
		CEffect*					m_pShadowMapEffect;	//!<シャドウマップのエフェクト。
		CVector3					m_lightPosition;	//!<ライトの位置。
		CVector3					m_lightDirection;	//!<ライトの向き。
		CMatrix						m_lvMatrix;
		CMatrix						m_LVPMatrix;		//!<ライトビュープロジェクション行列。
		CMatrix						m_projectionMatrix;
		float						m_near;				//!<近平面。
		float						m_far;				//!<遠平面。
		float						m_accpect;
		float						m_shadowAreaW;		//!<影を落とす範囲の幅。
		float						m_shadowAreaH;		//!<影を落とす範囲の高さ。
		CCamera*					m_camera;			//!<PSMを計算するときに使用するカメラ。
#ifdef USE_VSM
		CGaussianBlur				m_gaussianBlur;		//!<深度マップの平均値を求めるためのガウシアンブラー処理。
#endif 
	};
}

#endif //_TKSHADOWMAP_H_