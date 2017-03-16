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
		/*!
		*@brief	テクスチャのシェーダーハンドル。
		*/
		enum EnTextureShaderHandle {
			enTextureShaderHandle_DiffuseMap,	//!<ディフューズマップ。
			enTextureShaderHandle_ShadowMap_0,	//!<シャドウマップ0
			enTextureShaderHandle_ShadowMap_1,	//!<シャドウマップ1
			enTextureShaderHandle_ShadowMap_2,	//!<シャドウマップ2
			enTextureShaderHandle_NormalMap,	//!<法線マップ。
			enTextureShaderHandle_SpecularMap,	//!<スペキュラマップ。
			enTextureShaderHandle_Num,
		};
		/*!
		*@brief	行列のシェーダーハンドル。
		*/
		enum EnMatrixShaderHandle {
			enMatrixShaderHandle_LastFrameViewProj,		//!<1フレーム前のビュープロジェクション行列。
			enMatrixShaderHandle_ViewProj,				//!<ビュープロジェクション行列。
			enMatrixShaderHandle_LVP,					//!<ライトビュープロジェクション行列。
			enMatrixShaderHandle_ViewMatrixRotInv,		//!<ビュー行列の回転逆行列。
			enMatrixShaderHandle_WorldMatrix,			//!<ワールド行列
			enMatrixShaderHandle_RotationMatrix,		//!<回転行列（不要）
			enMatrixShaderHandle_Num,
		};
		/*!
		*@brief	浮動小数点ベクトルのシェーダーハンドル。
		*/
		enum EnFVectorShaderHandle {
			enFVectorShaderHandle_CameraPos,	//!<カメラの位置。
			enFVectorShaderHandle_FarNear,		//!<遠平面と近平面。
			enFVectorShaderHandle_FogParam,		//!<Fogパラメータ。
			enFVectorShaderHandle_CameraDir,	//!<カメラの方向。
			enFVectorShaderHandle_Num,
		};
		/*!
		*@brief	整数ベクトルのシェーダーハンドル。
		*/
		enum EnIVectorShaderHandle {
			enIVectorShaderHandle_Flags,		//!<各種フラグ。xに法線マップ、yはシャドウレシーバー、zはリムライト、wはスペキュラマップ。
			enIVectorShaderHandle_Flags2,		//!<各種フラグ。xに速度マップへの書き込み、yは大気錯乱シミュレーション種類。
			enIVectorShaderHandle_Num,
		};
		/*!
		*@brief	整数のシェーダーハンドル。
		*/
		enum EnIntShaderHandle {
			enIntShaderHandle_NumBone,			//!<ボーンの数。
			enIntshaderHandle_CurNumBone,		//!<スキニングを行うボーンの数。
			enIntShaderHandle_Num,
		};
		enum EnShaderHandle {
			enShaderHandleLight,				//ライト。
			enShaderHandleWorldMatrixArray,		//ボーン行列
			enShaderHandleShadowRecieverParam,	//シャドウレシーバー用のパラメータ。
			enShaderHandleNum,					//シェーダーハンドルの数。
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
		 *@brief	テクスチャを設定。
		 */
		void SetTexture(EnTextureShaderHandle eTexHandle, CTexture& tex)
		{
			TK_ASSERT(eTexHandle < enTextureShaderHandle_Num, "eTexHandle is invalid");
			m_textures[eTexHandle] = &tex;
		}
		/*!
		*@brief	行列を設定。
		*/
		void SetMatrix(EnMatrixShaderHandle eMatrixHandle, const CMatrix& mat)
		{
			TK_ASSERT(eMatrixHandle < enMatrixShaderHandle_Num, "eMatrixHandle is invalid");
			m_matrices[eMatrixHandle] = mat;
		}
		/*!
		*@brief 浮動小数ベクトルを設定。
		*/
		template<class TVector>
		void SetFVector(EnFVectorShaderHandle eFVecHandle, const TVector& v)
		{
			TK_ASSERT(eFVecHandle < enFVectorShaderHandle_Num, "eFVecHandle is invalid");
			m_fVector[eFVecHandle].Set(v);
		}
		/*!
		*@brief 整数ベクトルを設定。
		*/
		void SetIVector(EnIVectorShaderHandle eIVecHandle, const CVector4i& v)
		{
			TK_ASSERT(eIVecHandle < enIVectorShaderHandle_Num, "eIVecHandle is invalid");
			m_iVector[eIVecHandle] = v;
		}
		/*!
		*@brief 整数データを設定。
		*/
		void SetInt(EnIntShaderHandle eIntHandle, int data)
		{
			TK_ASSERT(eIntHandle < enIntShaderHandle_Num, "eIntHandle is invalid");
			m_int[eIntHandle] = data;
		}
		/*!
		*@brief 大気錯乱パラメータを設定。
		*/
		void SetAtmosphericScatteringParam(const SAtmosphericScatteringParam& param)
		{
			m_atmosParam = param;
		}
		/*!
		*@brief ライトを設定。
		*/
		void SetLight(const CLight& light)
		{
			m_light = light;
		}
		/*!
		*@brief	シャドウレシーバーパラメータを設定。
		*/
		void SetShadowRecieverParam(const CShadowMap::ShadowRecieverParam& shadowRecParam)
		{
			m_shadowRecParam = shadowRecParam;
		}
		/*!
		*@brief	初期化。
		*@param[in]		effect		エフェクト
		*@param[in]		tecName		テクニック名。
		*/
		void Init(CEffect* effect, const char* tecName);
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
		void InitShaderHandles(const char* tecName);
	protected:
		CTexture*	m_textures[enTextureShaderHandle_Num];	//!<テクスチャ。
		CMatrix 	m_matrices[enMatrixShaderHandle_Num];	//!<行列。
		CVector4 	m_fVector[enFVectorShaderHandle_Num];	//!<4要素の浮動小数ベクトル。
		CVector4i	m_iVector[enIVectorShaderHandle_Num];	//!<4要素の整数ベクトル。
		int			m_int[enIntShaderHandle_Num];			//!<整数。
		SAtmosphericScatteringParam m_atmosParam;			//!<大気錯乱パラメータ。
		CLight m_light;										//!<ライト。
		CShadowMap::ShadowRecieverParam m_shadowRecParam;	//!<シャドウレシーバーパラメータ。
	private:
		std::vector<ISkinModelMaterialNode*>	m_materialNodes;		//!<マテリアルのノード。
		CEffect* m_pEffect = nullptr;									//!<エフェクト。
		D3DXHANDLE m_hTec;												//!<テクニックハンドル。
		D3DXHANDLE m_hTexShaderHandle[enTextureShaderHandle_Num];		//!<テクスチャシェーダーハンドル。
		D3DXHANDLE m_hMatrixShaderHandle[enMatrixShaderHandle_Num];		//!<行列のシェーダーハンドル。
		D3DXHANDLE m_hFVectorShaderHandle[enFVectorShaderHandle_Num];	//!<浮動小数ベクトルのシェーダーハンドル。
		D3DXHANDLE m_hIVectorShaderHandle[enIVectorShaderHandle_Num];	//!<整数ベクトルのシェーダーハンドル。
		D3DXHANDLE m_hIntShaderHandle[enIntShaderHandle_Num];			//!<整数のシェーダーハンドル。
		D3DXHANDLE m_hAtmosShaderHandle;								//!<大気錯乱のシェーダーハンドル。
		D3DXHANDLE m_hLightShaderHandle;								//!<ライト用のシェーダーハンドル。
		D3DXHANDLE m_hShadowRecieverParamShaderHandle;					//!<シャドウレシーバーパラメータのシェーダーハンドル。						
		D3DXHANDLE m_hShaderHandle[enShaderHandleNum];				//!<シェーダーハンドル。
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		bool m_isBeginDraw = false;						//!<BeginDrawが呼ばれている？
#endif
	};
}