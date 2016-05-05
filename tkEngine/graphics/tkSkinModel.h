/*!
*@brief	スキンモデル
*/
#ifndef _TKSKINMODEL_H_
#define _TKSKINMODEL_H_

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
	private:
		CSkinModelData*		m_skinModelData;
		CEffect*			m_pEffect;
	};
}

#endif // #ifndef _TKSKINMODEL_H_