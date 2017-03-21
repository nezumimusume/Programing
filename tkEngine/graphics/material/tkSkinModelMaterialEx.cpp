/*!
 *@brief	スキンモデルマテリアル。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/material/tkSkinModelMaterialEx.h"
#include "tkEngine/graphics/tkEffect.h"


namespace tkEngine{
	void CSkinModelMaterialEx::Init(const char* tecName, const char* matName)
	{
		m_pEffect = EffectManager().LoadEffect("Assets/presetShader/skinModel.fx");
		m_materialName = matName;
		InitShaderHandles(tecName);
	}
	void CSkinModelMaterialEx::InitShaderHandles(const char* tecName)
	{
		if (m_pEffect) {
			ID3DXEffect* effectDx = m_pEffect->GetD3DXEffect();
			//テクスチャのシェーダーハンドル。
			m_hTexShaderHandle[enTextureShaderHandle_DiffuseMap] = effectDx->GetParameterByName(NULL, "g_diffuseTexture");
			m_hTexShaderHandle[enTextureShaderHandle_NormalMap] = effectDx->GetParameterByName(NULL, "g_normalTexture");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_0] = effectDx->GetParameterByName(NULL, "g_shadowMap_0");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_1] = effectDx->GetParameterByName(NULL, "g_shadowMap_1");
			m_hTexShaderHandle[enTextureShaderHandle_ShadowMap_2] = effectDx->GetParameterByName(NULL, "g_shadowMap_2");
			m_hTexShaderHandle[enTextureShaderHandle_SpecularMap] = effectDx->GetParameterByName(NULL, "g_speculerMap");
			m_hTexShaderHandle[enTextureShaderHandle_SkyCubeMap] = effectDx->GetParameterByName(NULL, "g_skyCubeMap");
			//行列のシェーダーハンドル。
			m_hMatrixShaderHandle[enMatrixShaderHandle_LastFrameViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProjLastFrame");
			m_hMatrixShaderHandle[enMatrixShaderHandle_ViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProj");
			m_hMatrixShaderHandle[enMatrixShaderHandle_LVP] = effectDx->GetParameterByName(NULL, "g_mLVP");
			m_hMatrixShaderHandle[enMatrixShaderHandle_ViewMatrixRotInv] = effectDx->GetParameterByName(NULL, "g_viewMatrixRotInv");
			m_hMatrixShaderHandle[enMatrixShaderHandle_WorldMatrix] = effectDx->GetParameterByName(NULL, "g_worldMatrix");
			m_hMatrixShaderHandle[enMatrixShaderHandle_RotationMatrix] = effectDx->GetParameterByName(NULL, "g_rotationMatrix");
			//浮動小数ベクトルのシェーダーハンドル。
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraPos] = effectDx->GetParameterByName(NULL, "g_cameraPos");
			m_hFVectorShaderHandle[enFVectorShaderHandle_FarNear] = effectDx->GetParameterByName(NULL, "g_farNear");
			m_hFVectorShaderHandle[enFVectorShaderHandle_FogParam] = effectDx->GetParameterByName(NULL, "g_fogParam");
			m_hFVectorShaderHandle[enFVectorShaderHandle_CameraDir] = effectDx->GetParameterByName(NULL, "g_cameraDir");
			//整数ベクトルのシェーダーハンドル。
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags] = effectDx->GetParameterByName(NULL, "g_flags");
			m_hIVectorShaderHandle[enIVectorShaderHandle_Flags2] = effectDx->GetParameterByName(NULL, "g_flags2");
			//整数のシェーダーハンドル。
			m_hIntShaderHandle[enIntShaderHandle_NumBone] = effectDx->GetParameterByName(NULL, "g_numBone");
			m_hIntShaderHandle[enIntshaderHandle_CurNumBone] = effectDx->GetParameterByName(NULL, "CurNumBones");
			//大気錯乱のシェーダーハンドル。
			m_hAtmosShaderHandle = effectDx->GetParameterByName(NULL, "g_atmosParam");
			//ライトのシェーダーハンドル。
			m_hLightShaderHandle = effectDx->GetParameterByName(NULL, "g_light");
			//シャドウレシーバーパラメータハンドル。
			m_hShadowRecieverParamShaderHandle = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");
			//ボーン行列のシェーダーハンドル。
			m_hBoneMatrixArrayShaderHandle = effectDx->GetParameterByName(NULL, "g_mWorldMatrixArray");
			
			m_hShaderHandle[enShaderHandleWorldMatrixArray] = effectDx->GetParameterByName(NULL, "g_mWorldMatrixArray");
			m_hShaderHandle[enShaderHandleShadowRecieverParam] = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");

			//シェーダーテクニック。
			m_hTechniqueHandle[enTecShaderHandle_SkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("SkinModelInstancingRenderToShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_SkinModelInstancing] = effectDx->GetTechniqueByName("SkinModelInstancing");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("NoSkinModelInstancingRenderToShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelInstancing] = effectDx->GetTechniqueByName("NoSkinModelInstancing");
			m_hTechniqueHandle[enTecShaderHandle_SkinModelRenderShadowMap] = effectDx->GetTechniqueByName("SkinModelRenderShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_SkinModel] = effectDx->GetTechniqueByName("SkinModel");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModelRenderShadowMap] = effectDx->GetTechniqueByName("NoSkinModelRenderShadowMap");
			m_hTechniqueHandle[enTecShaderHandle_NoSkinModel] = effectDx->GetTechniqueByName("NoSkinModel");
			m_hTechniqueHandle[enTecShaderHandle_Sky] = effectDx->GetTechniqueByName("Sky");
			
			SetTechnique(enTecShaderHandle_SkinModel);
		}
	}
	void CSkinModelMaterialEx::BeginDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(!m_isBeginDraw, "forgot call EndDraw!!!!");
		m_isBeginDraw = true;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->SetTechnique(m_hTec);
			effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			effect->BeginPass(0);
		}
	}
	void CSkinModelMaterialEx::SendMaterialParamToGPU()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			//ちょい適当
			for( int i = 0; i < enTextureShaderHandle_Num; i++ ){
				if (m_textures[i]) {
					if (m_textures[i]->IsCubeMap()) {
						effect->SetTexture(m_hTexShaderHandle[i], m_textures[i]->GetCubeMapDX());
					}
					else {
						effect->SetTexture(m_hTexShaderHandle[i], m_textures[i]->GetTextureDX());
					}
				}
			}
			for (int i = 0; i < enMatrixShaderHandle_Num; i++) {
				effect->SetMatrix(m_hMatrixShaderHandle[i], (D3DXMATRIX*)&m_matrices[i]);
			}
			for (int i = 0; i < enFVectorShaderHandle_Num; i++) {
				effect->SetVector(m_hFVectorShaderHandle[i], (D3DXVECTOR4*)&m_fVector[i]);
			}
			for (int i = 0; i < enIVectorShaderHandle_Num; i++) {
				effect->SetIntArray(m_hIVectorShaderHandle[i], (int*)&m_iVector[i], 4);
			}
			for (int i = 0; i < enIntShaderHandle_Num; i++) {
				effect->SetInt(m_hIntShaderHandle[i], m_int[i]);
			}
			effect->SetValue(m_hLightShaderHandle, &m_light, sizeof(m_light));
			effect->SetValue(m_hAtmosShaderHandle, &m_atmosParam, sizeof(m_atmosParam));
			effect->SetValue(m_hShadowRecieverParamShaderHandle, &m_shadowRecParam, sizeof(m_shadowRecParam));
			effect->SetMatrixArray(m_hBoneMatrixArrayShaderHandle, m_boneMatrixArray, m_boneMatrixArraySize);
			for (auto& node : m_materialNodes) {
				node->SendMaterialParamToGPU();
			}

			effect->CommitChanges();
		}
	}
	void CSkinModelMaterialEx::EndDraw()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		TK_ASSERT(m_isBeginDraw, "forgot call BeginDraw!!!!");
		m_isBeginDraw = false;
#endif
		if (m_pEffect) {
			ID3DXEffect* effect = m_pEffect->GetD3DXEffect();
			effect->EndPass();
			effect->End();
		}
	}
}