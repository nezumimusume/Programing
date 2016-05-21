/*!
*@brief	スキンモデル
*/
#ifndef _TKSKINMODEL_H_
#define _TKSKINMODEL_H_

#include "tkEngine/graphics/tkAnimation.h"

namespace tkEngine {
	class CEffect;
	class CSkinModelData;
	class CRenderContext;

	/*!
	*@brief	スキンモデル
	*/
	class CSkinModel {
	public:
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	描画
		*/
		void Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix);
		/*!
		*@brief	スキンモデルデータをセット。。
		*/
		void SetSkinModelData(CSkinModelData* modelData)
		{
			m_skinModelData = modelData;
		}
		/*!
		*@brief	イミディエイト描画。
		*@details
		* この関数を実行すると即描画コマンドがGPUに送られます。
		*/
		void ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
		
		/*!
		*@brief	ワールド行列を更新。
		*@details
		* 後でCMotionクラスに移動させます。
		*@param[in]		trans	平行移動。
		*@param[in]		rot		回転。
		*@param[in]		scale	拡大。
		*/
		void UpdateWorldMatrix( const CVector3& trans, const CQuaternion& rot, const CVector3& scale );
	private:
		CMatrix				m_worldMatrix;		//!<ワールド行列。
		CMatrix				m_rotationMatrix;	//!<回転行列。
		CSkinModelData*		m_skinModelData;	//!<スキンモデルデータ。
		CEffect*			m_pEffect;			//!<エフェクト。
		CAnimation			m_animation;		//!<アニメーション。
	};
}

#endif // #ifndef _TKSKINMODEL_H_