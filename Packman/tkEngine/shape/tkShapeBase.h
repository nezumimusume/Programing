/*!
 *@brief	形状の基本クラス。
 */
#ifndef _TKSHAPEBASE_H_
#define _TKSHAPEBASE_H_

namespace tkEngine{
	/*!
	 *@brief	形状の基本クラス。
	 */
	class CShapeBase{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CShapeBase();
		/*!
		 *@brief	デストラクタ。
		 */
		virtual ~CShapeBase();
		/*!
		*@brief	ワールド行列の取得。
		*/
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	座標を設定。
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	回転を設定。
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	プリミティブを取得。
		*/
		CPrimitive* GetPrimitive()
		{
			return m_pPrimitive;
		}
		/*!
		 * @brief	リリース。
		 */
		void Release();
		/*!
		*@brief	更新
		*/
		void UpdateWorldMatrix();
		/*!
		*@brief	描画。
		*@param[in]	renderContext	レンダリングコンテキスト。
		*/
		void Render(CRenderContext& renderContext);
	protected:
		bool m_isCreatePrimitive;	//!<内部でプリミティブを作成したかどうかのフラグ。
		CPrimitive*	m_pPrimitive;	//!<プリミティブ。
		CVector3	m_position;		//!<座標。
		CQuaternion	m_rotation;		//!<回転。
		CMatrix		m_worldMatrix;	//!<ワールド行列。
	};
}
#endif //_TKSHAPEBASE_H_