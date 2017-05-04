/*!4
 * @brief	シャドウマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "tkEngine/graphics/tkCamera.h"



namespace tkEngine{
	namespace {
		const float shadowAreaTable[CShadowMap::MAX_SHADOW_MAP][2] =
		{
			{ 20.0f, 20.0f },
			{ 45.0f, 45.0f },
			{ 120.0f, 120.0f },
		};
	}
	CShadowMap::CShadowMap() :
		m_isEnable(false),
		m_pShadowMapEffect(nullptr),
		m_near(1.0f),
		m_far(100.0f),
		m_accpect(1.0f),
		m_camera(nullptr),
		m_calcLightViewFunc(enCalcLightViewFunc_PositionTarget),
		m_lightTarget(CVector3::Zero),
		m_isDisableVSM(false),
		m_numShadowMap(1)
	{
		m_lightPosition.Set(0.0f, 3.0f, 0.0f);
		m_lightDirection.Set(0.0f, -1.0f, 0.0f);
		
		for (int i = 0; i < MAX_SHADOW_MAP; i++) {
			m_shadowAreaW[i] = shadowAreaTable[i][0];
			m_shadowAreaH[i] = shadowAreaTable[i][1];
		}
	}
	CShadowMap::~CShadowMap()
	{
		Release();
	}
	void CShadowMap::Create( int w, int h, bool isDisableSoftShadow, int numShadowMap)
	{
		TK_ASSERT( numShadowMap <= MAX_SHADOW_MAP, "numShadowMap is invalid");
		Release();
		
		
		m_near = 1.0f;
		m_far = 100.0f;
		m_numShadowMap = numShadowMap;
		m_isEnable = true;
		int j = 0;
		for (int i = MAX_SHADOW_MAP - m_numShadowMap; i < MAX_SHADOW_MAP; i++, j++) {
			m_shadowAreaW[j] = shadowAreaTable[i][0];
			m_shadowAreaH[j] = shadowAreaTable[i][1];
		}
		m_pShadowMapEffect = CEngine::EffectManager().LoadEffect("Assets/presetshader/shadowMap.fx");
		int wh[MAX_SHADOW_MAP][2] = {
			{w, h},
			{ w >> 1, h >> 1},
			{ w >> 1, h >> 1},
		};
		for (int i = 0; i < m_numShadowMap; i++) {
			m_shadowMapRT[i].Create(wh[i][0], wh[i][1], 1, D3DFMT_G16R16F, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
			m_accpect = s_cast<float>(w) / s_cast<float>(h);
		}
		
		m_isDisableVSM = isDisableSoftShadow;
		if (!m_isDisableVSM) {
			//VSMを行う。
			for (int i = 0; i < m_numShadowMap; i++) {
				m_blur[i].Init(w, h, *m_shadowMapRT[i].GetTexture());
			}
		}
	}
	void CShadowMap::Release()
	{
		if (m_shadowMapRT) {
			for (int i = 0; i < m_numShadowMap; i++) {
				m_shadowMapRT[i].Release();
			}
		}
	}
	void CShadowMap::Entry( IShadowCaster* caster )
	{
		m_shadowCaster.push_back(caster);
	}
	
	void CShadowMap::CalcLVPMatrixFromCamera()
	{
		if (m_camera == nullptr) {
			TK_LOG("カメラを設定してね。");
			return;
		}
		//シーンをレンダリング使用としているカメラを使って、ライトカメラの回転を求める。
		CVector3 cameraDir;
		cameraDir.Subtract(m_camera->GetTarget(), m_camera->GetPosition());
		if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
			//ほぼ真上をむいている。
			return;
		}
		cameraDir.y = 0.0f;
		cameraDir.Normalize();
		CVector3 lightViewForward;
		lightViewForward.Subtract(m_lightTarget, m_lightPosition);
		lightViewForward.Normalize();
		
		CVector3 lightViewUp;
		lightViewUp.Cross(lightViewForward, cameraDir);
		lightViewUp.Normalize();
		CVector3 lgihtViewRight;
		lgihtViewRight.Cross(lightViewUp, lightViewForward);
		lgihtViewRight.Normalize();
		//ライトビューはカメラの横方向を上、カメラの下方向を前、カメラの前方向を横とするといい感じになるよ。
		CMatrix lightViewRot;
		//ライトビューの横を設定する。
		lightViewRot.m[0][0] = lgihtViewRight.x;
		lightViewRot.m[0][1] = lgihtViewRight.y;
		lightViewRot.m[0][2] = lgihtViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//ライトビューの上を設定する。
		lightViewRot.m[1][0] = lightViewUp.x;
		lightViewRot.m[1][1] = lightViewUp.y;
		lightViewRot.m[1][2] = lightViewUp.z;
		lightViewRot.m[1][3] = 0.0f;
		//ライトビューの前を設定する。
		lightViewRot.m[2][0] = lightViewForward.x;
		lightViewRot.m[2][1] = lightViewForward.y;
		lightViewRot.m[2][2] = lightViewForward.z;
		lightViewRot.m[2][3] = 0.0f;

		static float shadowAreaTbl[MAX_SHADOW_MAP] = {
			20.0f,
			40.0f,
			80.0f
		};
		//ライトの位置を決めて、カメラ行列を確定させていく。
		
		const CVector3& cameraPos = m_camera->GetPosition();
		CVector3 lightPos = cameraPos;
		CVector3 lightOffset = cameraDir;
		lightOffset.Scale(shadowAreaTbl[0] * 0.2f);
		lightPos.Add(lightOffset);
		for (int i = 0; i < m_numShadowMap; i++) {
			
			CMatrix mLightView;
			CVector3 vTmp;
			vTmp = lightViewForward;
			vTmp.Scale(-30.0f);

			mLightView = lightViewRot;
			mLightView.m[3][0] = lightPos.x + vTmp.x;
			mLightView.m[3][1] = lightPos.y + vTmp.y;
			mLightView.m[3][2] = lightPos.z + vTmp.z;
			mLightView.m[3][3] = 1.0f;
			mLightView.Inverse(mLightView);	//カメラビュー完成。
			//続いてプロジェクション行列。
			float viewAngle = m_camera->GetViewAngle();
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				shadowAreaTbl[i] * m_accpect,
				tan(viewAngle * 0.5f) * (shadowAreaTbl[i] *(i+1))* 2.0f,
				m_near,
				m_far
			);
			m_LVPMatrix[i].Mul(mLightView, proj);
			m_shadowRecieverParam.mLVP[i] = m_LVPMatrix[i];
			lightOffset = cameraDir;
			lightOffset.Scale(shadowAreaTbl[i] * 0.9f);
			lightPos.Add(lightOffset);
		}
	}
	
	void CShadowMap::Update()
	{
		if (m_isEnable) {
			//@todo strategyパターンにリファクタした方が良い。

			if (m_calcLightViewFunc == enCalcLightViewFunc_PositionTarget) {
				//ライトの位置と注視点で計算。
				m_lightDirection.Subtract(m_lightTarget, m_lightPosition);
				m_lightDirection.Normalize();

			}
			CalcLVPMatrixFromCamera();

			m_shadowRecieverParam.vsmFlag_numShadowMap[0] = m_isDisableVSM ? 0 : 1;
			m_shadowRecieverParam.vsmFlag_numShadowMap[1] = m_numShadowMap;
		}
	}
	void CShadowMap::RenderToShadowMap( CRenderContext& renderContext )
	{
		CPIXPerfTag tag(renderContext, L"CShadowMap::RenderToShadowMap");
		if (m_isEnable) {

			CRenderTarget* pRTBackup = renderContext.GetRenderTarget(0);
			for (int i = 0; i < m_numShadowMap; i++) {
				renderContext.SetRenderTarget(0, &m_shadowMapRT[i]);
				renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
				renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
				for (auto caster : m_shadowCaster) {
					caster->Render(renderContext, m_pShadowMapEffect, m_LVPMatrix[i]);
				}
				renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
				//ブラーをかけて深度マップの平均値を求める。
				if (!m_isDisableVSM) {
					m_blur[i].Draw(renderContext);
				}
			}
			renderContext.SetRenderTarget(0, pRTBackup);
			m_shadowCaster.clear();	
		}
	}
}