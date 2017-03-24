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
			m_material->SendMatrixToGPU(TMatrix);
		}
	};
	/*!
	*@brief	浮動小数ベクトル転送ノードのテンプレートクラス。
	*/
	template<CSkinModelMaterial::EnFVectorShaderHandle TVector>
	class TSkinModelMaterialNode_SendFVector : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendFVector(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	マテリアルパラメータをGPUに転送。
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendFVectorToGPU(TVector);
		}
	};
	/*!
	*@brief	整数ベクトル転送ノードのテンプレートクラス。
	*/
	template<CSkinModelMaterial::EnIVectorShaderHandle TVector>
	class TSkinModelMaterialNode_SendIVector : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendIVector(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	マテリアルパラメータをGPUに転送。
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendIVectorToGPU(TVector);
		}
	};

	/*!
	*@brief	整数転送ノードのテンプレートクラス。
	*/
	template<CSkinModelMaterial::EnIntShaderHandle TInt>
	class TSkinModelMaterialNode_SendInt : public ISkinModelMaterialNode {
	public:
		TSkinModelMaterialNode_SendInt(CSkinModelMaterial* mat) :
			ISkinModelMaterialNode(mat)
		{
		}
		/*!
		*@brief	マテリアルパラメータをGPUに転送。
		*/
		void SendMaterialParamToGPU() final
		{
			m_material->SendIntToGPU(TInt);
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
	//地形テクスチャ3転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainTex3>
		CSkinModelMaterialNode_SendTerrainTex3;

	//地形法線マップ0転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap0>
		CSkinModelMaterialNode_SendTerrainNormalMap0;
	//地形法線マップ1転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap1>
		CSkinModelMaterialNode_SendTerrainNormalMap1;
	//地形法線マップ2転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap2>
		CSkinModelMaterialNode_SendTerrainNormalMap2;
	//地形法線マップ3転送ノード
	typedef TSkinModelMaterialNode_SendTexture<CSkinModelMaterial::enTextureShaderHandle_TerrainNormalMap3>
		CSkinModelMaterialNode_SendTerrainNormalMap3;

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

	//カメラの位置。
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_CameraPos>
		CSkinModelMaterialNode_SendCameraPos;
	//Fogパラメータ転送ノード。
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_FogParam>
		CSkinModelMaterialNode_SendFogParam;
	//カメラの方向転送ノード。
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_CameraDir>
		CSkinModelMaterialNode_SendCameraDir;
	//地形のXZ平面上のサイズ転送ノード。
	typedef TSkinModelMaterialNode_SendFVector<CSkinModelMaterial::enFVectorShaderHandle_TerrainRect>
		CSkinModelMaterialNode_SendTerrainRect;

	//!<各種フラグ。xに法線マップ、yはシャドウレシーバー、zはリムライト、wはスペキュラマップ。転送ノード。
	typedef TSkinModelMaterialNode_SendIVector<CSkinModelMaterial::enIVectorShaderHandle_Flags>
		CSkinModelMaterialNode_SendFlags;

	//!<各種フラグ。xに速度マップへの書き込み、yは大気錯乱シミュレーション種類。
	typedef TSkinModelMaterialNode_SendIVector<CSkinModelMaterial::enIVectorShaderHandle_Flags2>
		CSkinModelMaterialNode_SendFlags2;

	//!<ボーンの数。
	typedef TSkinModelMaterialNode_SendInt<CSkinModelMaterial::enIntShaderHandle_NumBone>
		CSkinModelMaterialNode_NumBone;	

	//!<スキニングを行うボーンの数。
	typedef TSkinModelMaterialNode_SendInt<CSkinModelMaterial::enIntshaderHandle_CurNumBone>
		CSkinModelMaterialNode_CurNumBone;
}
