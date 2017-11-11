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
		typedef std::function<void(CSkeleton&)>		OnPostUpdateSkeleton;

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
		*@param[in]	modelData		モデルデータ。
		*@param[in] numInstance		インスタンスの数。1より大きい場合インスタンシング描画が行われます。
		*							インスタンシング描画を行う場合は、Update関数にインスタンス番号を渡して、
		*							インスタンス固有のデータを更新する必要があります。
		*/
		void Init(CSkinModelData& modelData, int numInstance = 1);
		/*!
		*@brief	更新。
		*@details
		* 通常描画の場合の行列更新はこちらを使用する。
		* インスタンシング描画の場合はUpdateInstancingDataを使用する。
		*@param[in]		trans		平行移動。
		*@param[in]		rot			回転。
		*@param[in]		scale		拡大。
		*/
		void Update(
			const CVector3& trans, 
			const CQuaternion& rot, 
			const CVector3& scale
		);
		/*!
		 *@brief	インスタンシング用のデータの更新。
		 *@details
		 * インスタンシング描画の場合の行列更新はこちらを使用する。
		 * 全てのインスタンスの行列更新が完了したのち、PostUpadteInstancingDataを呼び出すように。
		 *@param[in]		trans		平行移動。
		 *@param[in]		rot			回転。
		 *@param[in]		scale		拡大。
		 */
		void UpdateInstancingData(
			const CVector3& trans,
			const CQuaternion& rot,
			const CVector3& scale);
		/*!
		*@brief	インスタンスデータの更新前に呼び出してください。
		*/
		void PreUpdateInstancingData()
		{
			m_updateInstance = 0;
		}
		/*!
		 *@brief	全てのインスタンスデータの更新が完了したのちに呼び出す必要がある更新関数。
		 */
		void PostUpdateInstancingData();
		/*!
		*@brief	描画
		*@param[in] renderContext	レンダリングコンテキスト。
		*@param[in]	viewMatrix		ビュー行列。
		*@param[in]	projMatrix		プロジェクション行列。
		*/
		void Draw(
			CRenderContext& renderContext, 
			const CMatrix& viewMatrix, 
			const CMatrix& projMatrix
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
		*@brief	モデルマテリアルの検索。
		*@param[in]	findEffect		マテリアルを見つけた時に呼ばれるコールバック関数
		*/
		void FindMaterial(CSkinModelData::OnFindMaterial findMaterial) const
		{
			FindMesh([&](auto& mesh) {
				CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
				findMaterial(effect);
			});
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
		/*!
		 *@brief	ワールド行列を取得。
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
	private:
		/*!
		 *@brief	ワールド行列の更新。
		 */
		void UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale);
	private:
		struct SVSConstantBuffer {
			CMatrix mWorld;
			CMatrix mView;
			CMatrix mProj;
			CVector4 screenParam;
			int isShadowReceiver;
		};
		CSkinModelData*	m_skinModelData = nullptr;
		CMatrix m_worldMatrix = CMatrix::Identity;
		CConstantBuffer m_cb;			//定数バッファ。
		CShadowCaster_SkinModel m_shadowCaster;	//!<シャドウキャスター。
		bool m_isShadowCaster = false;		//!<シャドウキャスター？
		bool m_isShadowReceiver = false;	//!<シャドウレシーバー？
		CSamplerState m_samplerState;		//!<サンプラステート。@todo ひとまとめにした方がいい。
		std::unique_ptr<CMatrix[]>	m_instancingData;		//!<インスタンシング描画用のデータ。
		CStructuredBuffer	m_instancingDataSB;				//!<インスタンシング描画用のストラクチャーバッファ。
		int m_numInstance = 1;								//!<インスタンスの数。
		int m_updateInstance = 0;							//!<行列が更新されたインスタンスの数。
	};
}