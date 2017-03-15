/*!
 *@brief	スキンモデルマテリアル。
 */

#pragma once

#include "tkEngine/graphics/material/node/tkSkinModelMaterialNode.h"

namespace tkEngine{
	class ISkinModelMaterialNode;
	/*!
	 *@brief	スキンモデルマテリアル。
	 */
	class CSkinModelMaterialEx
	{
	public:
		enum EnShaderHandle {
			enShaderHandleLastFrameViewProj,	//1フレーム前のビュープロジェクション。	
			enShaderHandleViewProj,				//ビュープロジェクション。	
			enShaderHandleLight,				//ライト。
			enShaderHandleLVP,					//ライトビュープロジェクション行列。
			enShaderHandleCameraPos,			//カメラの位置。
			enShaderHandleAtmosParam,			//大気錯乱パラメータ。
			enShaderHandleFlags,				//g_flags
			enShaderHandleFlags2,				//g_flags2
			enShaderHandleFarNear,				//FarNear
			enShaderHandleFogParam,				//Fogパラメータ。
			enShaderHandleWorldMatrixArray,		//ボーン行列
			enShaderHandleNumBone,				//ボーンの数。
			enShaderHandleCurNumBones,			//スキングを行なうボーンの数。
			enShaderHandleViewMatrixRotInv,		//ビュー行列の回転成分の逆行列。
			enShaderHandleWorldMatrix,			//ワールド行列
			enShaderHandleRotationMatrix,		//回転行列。
			enShaderHandleShadowMap_0,			//シャドウマップ
			enShaderHandleShadowMap_1,			//シャドウマップ
			enShaderHandleShadowMap_2,		//シャドウマップ
			enShaderHandleNormalTexture,	//法線マップ。
			enShaderHandleSpeculerMap,		//スペキュラマップ。
			enShaderHandleDiffuseTexture,	//ディフューズテクスチャ。
			enShaderHandleCameraDir,		//カメラの方向。
			enShaderHandleShadowRecieverParam,	//シャドウレシーバー用のパラメータ。
			enShaderHandleTec_SkinModelInstancingRenderToShadowMap,		//SkinModelInstancingRenderToShadowMapテクニック
			enShaderHandleTec_SkinModelInstancing,						//SkinModelInstancingテクニック。
			enShaderHandleTec_NoSkinModelInstancingRenderToShadowMap,	//NoSkinModelInstancingRenderToShadowMapテクニック。
			enShaderHandleTec_NoSkinModelInstancing,					//NoSkinModelInstancingテクニック。
			enShaderHandleTec_SkinModelRenderShadowMap,					//SkinModelRenderShadowMapテクニック。
			enShaderHandleTec_SkinModel,								//SkinModelテクニック。
			enShaderHandleTec_NoSkinModelRenderShadowMap,				//NoSkinModelRenderShadowMapテクニック。
			enShaderHandleTec_NoSkinModel,								//NoSkinModelテクニック。
			enShaderHandleTec_Sky,										//Skyテクニック。
			enShaderHandleNum,				//シェーダーハンドルの数。
		};
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CSkinModelMaterialEx()
		{
		}
		/*!
		 *@brief	デストラクタ。
		 */
		~CSkinModelMaterialEx()
		{
		}
		/*!
		*@brief	初期化。
		*/
		void Init();
		/*!
		 *@brief	描画開始。
		 */
		void BeginDraw();
		/*!
		 *@brief	マテリアルパラメータをGPUに転送。
		 */
		void SendMaterialParamToGPU();
		/*!
		 *@brief	描画終了。
		 */
		void EndDraw();
	private:
		/*!
		*@brief	シェーダーハンドルの初期化。
		*/
		void InitShaderHandles();
	private:
		std::vector<ISkinModelMaterialNode*>	m_materialNodes;		//!<マテリアルのノード。
		CEffect* m_pEffect = nullptr;					//!<エフェクト。
		std::string m_tecName;							//!<テクニック名。
		D3DXHANDLE m_hShaderHandle[enShaderHandleNum];	//!<シェーダーハンドル。
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		bool m_isBeginDraw = false;						//!<BeginDrawが呼ばれている？
#endif
	};
}