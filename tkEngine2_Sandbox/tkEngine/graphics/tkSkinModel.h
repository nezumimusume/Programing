/*!
 *@brief	スキンモデル。
 */

#pragma once

#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{
	class CSkinModelData;
	/*!
	 *@brief	スキンモデル。
	 */
	class CSkinModel : Noncopyable{
	public:
		/*!
		*@brief QueryEffectsを実行したときのコールバックに渡される引数構造体。
		*/
		struct SQuerryEffectsCbArg {
			DirectX::ModelMeshPart*	meshPart;		//現在のエフェクト。
		};
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	初期化
		*/
		void Init(CSkinModelData& modelData);
		/*!
		*@brief	更新。
		*@details
		*@param[in]		trans	平行移動。
		*@param[in]		rot		回転。
		*@param[in]		scale	拡大。
		*/
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale);
		
		/*!
		*@brief	描画
		*@param[in]	viewMatrix		ビュー行列。
		*@param[in]	projMatrix		プロジェクション行列。
		*@param[in]	isZPrepass		ZPrepass?
		*@param[in]	isDrawShadowMap	シャドウマップに描画中？
		*/
		void Draw(
			CRenderContext& renderContext, 
			const CMatrix& viewMatrix, 
			const CMatrix& projMatrix,
			bool isZPrepass = false,
			bool isDrawShadowMap = false
		);
		/*!
		*@brief	メッシュの検索。
		*@param[in]	findMesh		メッシュを見つけた時に呼ばれるコールバック関数
		*/
		void FindMesh(CSkinModelData::OnFindMesh findMesh) const
		{
			if (m_skinModelData != nullptr) {
				m_skinModelData->FindMesh(findMesh);
			}
		}
		/*!
		* @brief	シャドウキャスターのフラグを設定。
		*@param[in]	flag	シャドウキャスターのフラグ。
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}
		/*!
		* @brief	シャドウレシーバーのフラグを設定。
		*@param[in]	flag	シャドウレシーバーのフラグ。
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}
	private:
		struct SVSConstantBuffer {
			CMatrix mWorld;
			CMatrix mView;
			CMatrix mProj;
			CVector4 screenParam;
			int isZPrepass;
			int isDrawShadowMap;
			int isShadowReceiver;
		};
		CSkinModelData*	m_skinModelData = nullptr;
		CMatrix m_worldMatrix = CMatrix::Identity;
		CConstantBuffer m_cb;			//定数バッファ。
		CShadowCaster_SkinModel m_shadowCaster;	//!<シャドウキャスター。
		bool m_isShadowCaster = false;		//!<シャドウキャスター？
		bool m_isShadowReceiver = false;	//!<シャドウレシーバー？
	};
}