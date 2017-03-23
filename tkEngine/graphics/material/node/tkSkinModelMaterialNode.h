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
	//ディフューズマップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_DiffuseMap>
		CSkinModelMaterialNode_SendDiffuseMap;
	//シャドウマップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
		CSkinModelMaterialNode_SendShadowMap_0;
	//シャドウマップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
		CSkinModelMaterialNode_SendShadowMap_1;
	//シャドウマップ転送ノード。
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_ShadowMap_0>
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
}
