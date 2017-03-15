/*!
 *@brief	スキンモデルマテリアル。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/material/tkSkinModelMaterialEx.h"
#include "tkEngine/graphics/tkEffect.h"


namespace tkEngine{
	void CSkinModelMaterialEx::Init()
	{
		InitShaderHandles();
	}
	void CSkinModelMaterialEx::InitShaderHandles()
	{
		if (m_pEffect) {
			ID3DXEffect* effectDx = m_pEffect->GetD3DXEffect();
			m_hShaderHandle[enShaderHandleLastFrameViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProjLastFrame");
			m_hShaderHandle[enShaderHandleAtmosParam] = effectDx->GetParameterByName(NULL, "g_atmosParam");
			m_hShaderHandle[enShaderHandleViewProj] = effectDx->GetParameterByName(NULL, "g_mViewProj");
			m_hShaderHandle[enShaderHandleLight] = effectDx->GetParameterByName(NULL, "g_light");
			m_hShaderHandle[enShaderHandleLVP] = effectDx->GetParameterByName(NULL, "g_mLVP");
			m_hShaderHandle[enShaderHandleCameraPos] = effectDx->GetParameterByName(NULL, "g_cameraPos");
			m_hShaderHandle[enShaderHandleFlags] = effectDx->GetParameterByName(NULL, "g_flags");
			m_hShaderHandle[enShaderHandleFlags2] = effectDx->GetParameterByName(NULL, "g_flags2");
			m_hShaderHandle[enShaderHandleFarNear] = effectDx->GetParameterByName(NULL, "g_farNear");
			m_hShaderHandle[enShaderHandleFogParam] = effectDx->GetParameterByName(NULL, "g_fogParam");
			m_hShaderHandle[enShaderHandleWorldMatrixArray] = effectDx->GetParameterByName(NULL, "g_mWorldMatrixArray");
			m_hShaderHandle[enShaderHandleNumBone] = effectDx->GetParameterByName(NULL, "g_numBone");
			m_hShaderHandle[enShaderHandleCurNumBones] = effectDx->GetParameterByName(NULL, "CurNumBones");
			m_hShaderHandle[enShaderHandleViewMatrixRotInv] = effectDx->GetParameterByName(NULL, "g_viewMatrixRotInv");
			m_hShaderHandle[enShaderHandleWorldMatrix] = effectDx->GetParameterByName(NULL, "g_worldMatrix");
			m_hShaderHandle[enShaderHandleRotationMatrix] = effectDx->GetParameterByName(NULL, "g_rotationMatrix");
			m_hShaderHandle[enShaderHandleShadowMap_0] = effectDx->GetParameterByName(NULL, "g_shadowMap_0");
			m_hShaderHandle[enShaderHandleShadowMap_1] = effectDx->GetParameterByName(NULL, "g_shadowMap_1");
			m_hShaderHandle[enShaderHandleShadowMap_2] = effectDx->GetParameterByName(NULL, "g_shadowMap_2");
			m_hShaderHandle[enShaderHandleNormalTexture] = effectDx->GetParameterByName(NULL, "g_normalTexture");
			m_hShaderHandle[enShaderHandleSpeculerMap] = effectDx->GetParameterByName(NULL, "g_speculerMap");
			m_hShaderHandle[enShaderHandleDiffuseTexture] = effectDx->GetParameterByName(NULL, "g_diffuseTexture");
			m_hShaderHandle[enShaderHandleCameraDir] = effectDx->GetParameterByName(NULL, "g_cameraDir");
			m_hShaderHandle[enShaderHandleTec_SkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("SkinModelInstancingRenderToShadowMap");
			m_hShaderHandle[enShaderHandleTec_SkinModelInstancing] = effectDx->GetTechniqueByName("SkinModelInstancing");
			m_hShaderHandle[enShaderHandleTec_NoSkinModelInstancingRenderToShadowMap] = effectDx->GetTechniqueByName("NoSkinModelInstancingRenderToShadowMap");
			m_hShaderHandle[enShaderHandleTec_NoSkinModelInstancing] = effectDx->GetTechniqueByName("NoSkinModelInstancing");
			m_hShaderHandle[enShaderHandleTec_SkinModelRenderShadowMap] = effectDx->GetTechniqueByName("SkinModelRenderShadowMap");
			m_hShaderHandle[enShaderHandleTec_SkinModel] = effectDx->GetTechniqueByName("SkinModel");
			m_hShaderHandle[enShaderHandleTec_NoSkinModelRenderShadowMap] = effectDx->GetTechniqueByName("NoSkinModelRenderShadowMap");
			m_hShaderHandle[enShaderHandleTec_NoSkinModel] = effectDx->GetTechniqueByName("NoSkinModel");
			m_hShaderHandle[enShaderHandleShadowRecieverParam] = effectDx->GetParameterByName(NULL, "gShadowReceiverParam");
			m_hShaderHandle[enShaderHandleTec_Sky] = effectDx->GetTechniqueByName("Sky");
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
			effect->SetTechnique(m_tecName.c_str());
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