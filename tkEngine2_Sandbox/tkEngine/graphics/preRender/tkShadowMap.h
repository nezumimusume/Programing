/*!
 * @brief	シャドウマップ
 */

#pragma once

namespace tkEngine{
	class IShadowCaster;
	/*!
	 * @brief	シャドウマップ。
	 */
	class CShadowMap : Noncopyable{
	public:
		static const int MAX_SHADOW_MAP = 3;
		/*!
		 * @brief	コンストラクタ。
		 */
		CShadowMap();
		/*!
		 * @brief	デストラクタ。
		 */
		~CShadowMap();
		/*!
		 * @brief	シャドウマップの作成。
		 *@param[in]	config		コンフィグ。
		 *@return	trueが返ってきたらシャドウマップの作成成功。
		 */
		bool Init( const SShadowRenderConfig& config );
		/*!
		* @brief	更新。
		*/
		void Update();
		/*!
		 *@brief	シャドウマップへ書き込み。
		 */
		void RenderToShadowMap(CRenderContext& rc);
		/*!
		* @brief	開放。
		*/
		void Release();
		/*!
		* @brief	シャドウキャスターをエントリー。
		*/
		void Entry(IShadowCaster* caster);
		/*!
		* @brief	ライトビューの注視点を設定。
		*/
		void SetLightTarget(const CVector3& lightTarget)
		{
			m_lightTarget = lightTarget;
		}
		/*!
		* @brief	ライトの位置を設定。
		*/
		void SetLightPosition(const CVector3& lightPosition)
		{
			m_lightPosition = lightPosition;
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
			m_near = Near;
		}
	private:
		bool m_isEnable = false;							//!<影の処理が有効？
		CVector3 m_lightPosition = CVector3::Zero;			//!<ライトの位置。
		CVector3 m_lightTarget = CVector3::Zero;			//!<注視点
		float m_near = 0.1f;								//!<近平面。
		float m_far = 100.0f;								//!<遠平面。
		float m_accpect = 1.0f;								//!<アスペクト。不要？
		float m_shadowAreaW[MAX_SHADOW_MAP] = {0};			//!<影を落とす範囲の幅。
		float m_shadowAreaH[MAX_SHADOW_MAP] = {0};			//!<影を落とす範囲の高さ。
		CRenderTarget	m_shadowMapRT[MAX_SHADOW_MAP];		//!<シャドウマップを書き込むレンダリングターゲット。
		std::vector<IShadowCaster*> m_shadowCaster;			//!<シャドウキャスター。
		CMatrix	m_LVPMatrix[MAX_SHADOW_MAP] = { CMatrix::Identity };				//!<ライトビュープロジェクション行列。
		int m_numShadowMap = 0;								//!<シャドウマップの枚数。
	};
}