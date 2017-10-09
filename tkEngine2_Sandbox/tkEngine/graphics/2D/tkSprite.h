/*!
 * @brief	スプライト。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	スプライト。
	 */
	class CSprite : Noncopyable {
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSprite();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSprite();
		/*!
		 * @brief	初期化。
		 *@param[in]	tex		テクスチャ。
		 *@param[in]	w		幅。
		 *@param[in]	h		高さ。
		 */
		void Init(CShaderResourceView& tex, float w, float h);
		/*!
		 * @brief	テクスチャを設定。
		 *@param[in]	tex		テクスチャ。
		 */
		void SetTexture(CShaderResourceView& tex)
		{
			m_textureSRV = &tex;
		}
		/*!
		*@brief	描画
		*@param[in]	viewMatrix		ビュー行列。
		*@param[in]	projMatrix		プロジェクション行列。
		*/
		void Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	座標を設定。
		*/
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		
		/*!
		*@brief	座標を取得。
		*/
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		*@brief	回転を設定。
		*/
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/*!
		*@brief	回転を取得。
		*/
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/*!
		*@brief	拡大率を設定。
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/*!
		*@brief	拡大率を取得。
		*/
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/*!
		*@brief	ピボットを設定。
		*@details
		* 0.5, 0.5で画像の中心が基点。
		* 0.0, 0.0で画像の左下。
		* 1.0, 1.0で画像の右上。
		* UnityのuGUIに準拠。
		*@param[in]	pivot		サイズ。
		*/
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
	private:
		struct SSpriteCB {
			CMatrix WVP;		//ワールドビュープロジェクション行列。
		};
		CVector3				m_position = CVector3::Zero;	//!<座標。
		CQuaternion				m_rotation = CQuaternion::Identity;		//!<回転
		CVector3				m_scale = CVector3::One;
		CMatrix					m_world = CMatrix::Identity;	//!<ワールド行列。
		CShader					m_ps;							//!<ピクセルシェーダー。
		CShader					m_vs;							//!<頂点シェーダー。
		CPrimitive				m_primitive;					//!<プリミティブ。
		CShaderResourceView*	m_textureSRV = nullptr;			//!<テクスチャ。
		CConstantBuffer			m_cb;
		CVector2				m_pivot = {0.5f, 0.5f};		//!<ピボット。
		CVector2				m_size = CVector2::Zero;		//!<サイズ。
	};
}