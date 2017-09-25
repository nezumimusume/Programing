/*!
 * @brief	シャドウマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	
	CShadowMap::CShadowMap()
	{
	}
	
	CShadowMap::~CShadowMap()
	{
	}
	
	bool CShadowMap::Init(const SShadowRenderConfig& config)
	{
		Release();
		m_isEnable = config.isEnable;
		if (m_isEnable == false) {
			return true;
		}
		int wh[NUM_SHADOW_MAP][2] = {
			{ config.shadowMapWidth, config.shadowMapHeight},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
		};
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			m_shadowMapRT[i].Create(
				wh[i][0], 
				wh[i][1], 
				1, 
				1,
				DXGI_FORMAT_R16G16_FLOAT,
				DXGI_FORMAT_D24_UNORM_S8_UINT, 
				multiSampleDesc
			);
		}
		m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));
		return true;
	}
	
	void CShadowMap::Release()
	{
		m_shadowCb.Release();
		for (auto& rt : m_shadowMapRT) {
			rt.Release();
		}
	}
	
	void CShadowMap::Entry(IShadowCaster* caster)
	{
		if (!m_isEnable) {
			return;
		}
		m_shadowCaster.push_back(caster);
	}
	
	void CShadowMap::Update()
	{
		if (!m_isEnable) {
			return;
		}
		//シーンをレンダリング使用としているカメラを使って、ライトカメラの回転を求める。
		CVector3 cameraDir;
		cameraDir.Subtract(MainCamera().GetTarget(), MainCamera().GetPosition());
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

		float toFarPlane = m_far - m_near;
		float shadowAreaTbl[NUM_SHADOW_MAP] = {
			200,
			400,
			800
		};

		CVector3 lightPos = m_lightPosition;
		CVector3 lightOffset;
		SShadowCb shadowCB;
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {

			CMatrix mLightView;
			mLightView = lightViewRot;
			mLightView.m[3][0] = lightPos.x;
			mLightView.m[3][1] = lightPos.y;
			mLightView.m[3][2] = lightPos.z;
			mLightView.m[3][3] = 1.0f;
			mLightView.Inverse(mLightView);	//カメラビュー完成。
											//続いてプロジェクション行列。
			float viewAngle = MainCamera().GetViewAngle();
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				shadowAreaTbl[i] * m_accpect,
				tan(viewAngle * 0.5f) * (shadowAreaTbl[i] * (i + 1))* 2.0f,
				m_near,
				m_far
			);
			m_LVPMatrix[i].Mul(mLightView, proj);
			m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
			
			lightOffset = cameraDir;
			lightOffset.Scale(shadowAreaTbl[i] * 0.9f);
			lightPos.Add(lightOffset);
		}
	}
	/*!
	*@brief	シャドウマップへ書き込み。
	*/
	void CShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSUnsetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i);
		}

		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			CRenderTarget* renderTargets[] = {
				&m_shadowMapRT[i]
			};

			rc.OMSetRenderTargets(1, renderTargets);
			rc.RSSetViewport(
				0.0f, 0.0f, 
				(float)m_shadowMapRT[i].GetWidth(),
				(float)m_shadowMapRT[i].GetHeight()
			);
			float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor);

			for (auto& caster : m_shadowCaster) {
				caster->Render(rc, m_LVPMatrix[i]);
			}

		}
		m_shadowCaster.clear();
		//レンダリングターゲットを差し戻す。
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//@todo レンダリングステートはリストアする方法に変更する。
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
	}
	/*!
	*@brief	影を落とすためのパラメータをGPUに転送する。
	*/
	void CShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_shadowCb, &m_shadowCbEntity);
		rc.PSSetConstantBuffer(enSkinModelCBReg_Shadow, m_shadowCb);
		//テクスチャを転送。
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSSetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i, m_shadowMapRT[i].GetRenderTargetSRV());
		}
	}
}