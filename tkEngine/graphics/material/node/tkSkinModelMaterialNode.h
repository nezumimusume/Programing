/*!
 *@brief	スキンモデルのマテリアルノードの基底クラス。
 */

#pragma once

#include "tkEngine/graphics/material/tkSkinModelMaterial.h"

namespace tkEngine{
	class CSkinModelMaterial;
	/*!
	 *@brief	スキンモデルのマテリアルノードの基底クラス。
	 */
	class ISkinModelMaterialNode{
	protected:
		CSkinModelMaterial*		m_material = nullptr;		//!<スキンモデルマテリアル。
	public:
		ISkinModelMaterialNode(CSkinModelMaterial* mat) :
			m_material(mat)
		{
		}
		virtual ~ISkinModelMaterialNode()
		{
		}
		/*!
		 *@brief	マテリアルパラメータをGPUに転送。
		 */
		virtual void SendMaterialParamToGPU() = 0;
	};
	/*!
	 *@brief	テクスチャ転送ノードのテンプレートクラス。
	 */
	template<CSkinModelMaterial::EnTextureShaderHandle TTex>
	class TSkinModelMaterialNode_SendTexture : public ISkinModelMaterialNode{
	public:
		TSkinModelMaterialNode_SendTexture(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		 *@brief	マテリアルパラメータをGPUに転送。
		 */
		void SendMaterialParamToGPU() final
		{
			//スプラットマップを転送。
			m_material->SendTextureTGPU(TTex);
		}
	};
	
	/*!
	*@brief	行列転送ノードのテンプレートクラス。
	*/
	template<CSkinModelMaterial::EnMatrixShaderHandle TMatrix>
	class TSkinModelMaterialNode_SendMatrix : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendMatrix(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	マテリアルパラメータをGPUに転送。
		*/
		void SendMaterialParamToGPU() final
		{
			//スプラットマップを転送。
			m_material->SendMatrixToGPU(TMatrix);
		}
	};

	//ディフューズマップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DiffuseMap>
		CSkinModelMaterialNode_SendDiffuseMap;
	//シャドウマップ0転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
		CSkinModelMaterialNode_SendShadowMap_0;
	//シャドウマップ1転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_1>
		CSkinModelMaterialNode_SendShadowMap_1;
	//シャドウマップ2転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_2>
		CSkinModelMaterialNode_SendShadowMap_2;
	//法線マップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_NormalMap>
		CSkinModelMaterialNode_SendNormalMap;
	//スペキュラマップ。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SpecularMap>
		CSkinModelMaterialNode_SendSpecularMap;
	//スカイキューブ。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SkyCubeMap>
		CSkinModelMaterialNode_SendSkyCubeMap;
	//スプラットマップ転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_SplatMap>
		CSkinModelMaterialNode_SendSplatMap;
	//地形テクスチャ0転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex0>
		CSkinModelMaterialNode_SendTerrainTex0;
	//地形テクスチャ1転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex1>
		CSkinModelMaterialNode_SendTerrainTex1;
	//地形テクスチャ2転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex2>
		CSkinModelMaterialNode_SendTerrainTex2;

	
	//1フレーム前のビュープロジェクション行列転送ノード。
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LastFrameViewProj>
		CSkinModelMaterialNode_SendLastFrameViewProj;
	//ビュープロジェクション行列転送ノード。
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_ViewProj>
		CSkinModelMaterialNode_SendViewProj;
	//ライトビュープロジェクション行列転送ノード。
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_LVP>
		CSkinModelMaterialNode_SendLVP;
	//ワールド行列
	typedef TSkinModelMaterialNode_SendMatrix<CSkinModelMaterial::enMatrixShaderHandle_WorldMatrix>
		CSkinModelMaterialNode_SendWorldMatrix;
}
