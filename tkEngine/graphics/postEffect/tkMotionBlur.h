/*!
 * @brief	速度マップを使用したモーションブラー。
 */

#pragma once

#include "tkEngine/Graphics/tkCamera.h"

namespace tkEngine{
	/*!
	 * @brief	速度マップを使用したモーションブラー。
	 */
	class CMotionBlur : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CMotionBlur();
		/*!
		 * @brief	デストラクタ。
		 */
		~CMotionBlur();
		/*!
		* @brief	作成。
		*@param[in]	config		グラフィックコンフィグ。
		*/
		void Create(const SGraphicsConfig& config);
		/*!
		* @brief	更新。
		*/
		void Update()
		{
			if (m_isEnable && m_camera != nullptr) {
				m_lastFrameViewProjMatrix = m_camera->GetViewProjectionMatrix();
			}
		}
		/*!
		* @brief	モーションブラーの有効、無効を設定。
		*@details
		* tkEngineの初期化時にモーションブラーを有効にしていない場合は</br>
		* 本関数を使用してもモーションブラーは有効になりません。</br>
		* 詳細はtkEngine::CEngine::Init関数を参照してください。
		*/
		void SetEnable(bool flag)
		{
			if (flag && !m_isEnable && m_camera != nullptr) {
				//ブラーが無効から有効に変更される場合はビュープロジェクション行列を更新する。
				m_lastFrameViewProjMatrix = m_camera->GetViewProjectionMatrix();
			}
			m_isEnable = flag;
		}
		/*!
		* @brief	モーションブラーで使用するカメラを設定する。
		* @details
		* 　ブラーをかけたいシーンを描画するカメラを設定してください。
		*/
		void SetCamera(const CCamera* camera)
		{
			m_camera = camera;
			m_lastFrameViewProjMatrix = m_camera->GetViewProjectionMatrix();
		}
		/*!
		* @brief	1フレーム前のビュープロジェクション行列。
		*/
		const CMatrix& GetLastFrameViewProjectionMatrix()
		{
			return m_lastFrameViewProjMatrix;
		}
		/*!
		 * @brief	速度マップを書き込むためのレンダリングターゲット。
		 */
		CRenderTarget* GetVelocityMapRenderTarget()
		{
			return &m_velocityMapRT;
		}
		/*!
		* @brief	描画。
		*/
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);
	private:
		const CCamera*		m_camera = nullptr;		//!<カメラ。
		CRenderTarget		m_velocityMapRT;		//!<速度マップを書き込むためのレンダリングターゲット。
		bool				m_isEnable = false;		//!<速度マップ有効？
		bool				m_isInited = false;		//!<初期化されている？
		CMatrix				m_lastFrameViewProjMatrix = CMatrix::Identity;	//!<1フレーム前のビュープロジェクション行列。
		CEffect*			m_effect = nullptr;		//!<エフェクト。
	};
}