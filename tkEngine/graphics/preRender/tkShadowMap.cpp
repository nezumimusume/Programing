/*!
 * @brief	シャドウマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CShadowModel::CShadowModel() :
		m_prim(nullptr),
		m_mWorld(CMatrix::Identity)
	{
	}
	CShadowModel::~CShadowModel()
	{
	}
	void CShadowModel::Create( CPrimitive* prim )
	{
		m_prim = prim;
	}
	void CShadowModel::Render( CRenderContext& renderContext, CEffect* pEffect, const CMatrix& mLVP )
	{
		CMatrix mWVP;
		mWVP.Mul(m_mWorld, mLVP);
		pEffect->BeginPass(renderContext, 0);
		pEffect->SetValue(renderContext, "g_mWVP", &mWVP, sizeof(mWVP));
		pEffect->CommitChanges(renderContext);
		renderContext.SetVertexDeclaration(m_prim->GetVertexDecl());
		renderContext.SetStreamSource(0, m_prim->GetVertexBuffer());
		renderContext.SetIndices(m_prim->GetIndexBuffer());
		renderContext.DrawIndexedPrimitive(m_prim);
		pEffect->EndPass(renderContext);
	}
	CShadowMap::CShadowMap() :
		m_isEnable(false),
		m_pShadowMapEffect(nullptr),
		m_near(1.0f),
		m_far(100.0f),
		m_lvMatrix(CMatrix::Identity)
	{
		m_lightPosition.Set(0.0f, 3.0f, 0.0f);
		m_lightDirection.Set(0.0f, -1.0f, 0.0f);
	}
	CShadowMap::~CShadowMap()
	{
		Release();
	}
	void CShadowMap::Create( int w, int h )
	{
		Release();
		m_near = 1.0f;
		m_far = 100.0f;
		m_shadowMapRT.Create( w, h, 1, FMT_A8R8G8B8, FMT_D16, MULTISAMPLE_NONMASKABLE, 0 );
		m_isEnable = true;
		m_pShadowMapEffect = CEngine::EffectManager().LoadEffect( "Assets/presetshader/shadowMap.fx" );
		m_projectionMatrix.MakeProjectionMatrix(
			CMath::DegToRad(60.0f),
			s_cast<float>(w) / s_cast<float>(h),
			m_near,
			m_far
		);
		//m_projectionMatrix.MakeOrthoProjectionMatrix(w, h, m_near, m_far);
	}
	void CShadowMap::Release()
	{
		m_shadowMapRT.Release();
	}
	void CShadowMap::Entry( CShadowModel* model )
	{
		m_shadowModels.push_back(model);
	}
	/*!
	* @brief	更新。
	*/
	void CShadowMap::Update()
	{
		if (m_isEnable) {
			//ライトビュープロジェクション行列を作成。
			CVector3 lightUp;
			float t = fabsf(m_lightDirection.Dot(CVector3::AxisY));
			if (fabsf((t - 1.0f)) < 0.00001f) {
				//ライトの方向がほぼY軸と並行。
				lightUp = CVector3::AxisX;
			}
			else {
				lightUp = CVector3::AxisY;
			}
			//ライトからみたビュー行列を作成。
			CVector3 target;
			target.Add(m_lightPosition, m_lightDirection);
			m_lvMatrix.MakeLookAt(m_lightPosition, target, lightUp);
			m_LVPMatrix.Mul(m_lvMatrix, m_projectionMatrix);
		}

	}
	void CShadowMap::RenderToShadowMap( CRenderContext& renderContext )
	{
		if(m_isEnable){
			CRenderTarget* pRTBackup = renderContext.GetRenderTarget(0);
			renderContext.SetRenderTarget( 0, &m_shadowMapRT );
			renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0xffffffff, 1.0f, 0);
			//renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pShadowMapEffect->SetTechnique( renderContext, "RenderShadowMap" );
			m_pShadowMapEffect->Begin(renderContext);
			//ライトビュープロジェクション行列を作る。
			float farNear[] = {
				m_far,
				m_near
			};
			m_pShadowMapEffect->SetValue(renderContext, "g_farNear", farNear, sizeof(farNear));
			for (auto model : m_shadowModels) {
				model->Render( renderContext, m_pShadowMapEffect, m_LVPMatrix);
			}
			m_pShadowMapEffect->End(renderContext);
			renderContext.SetRenderTarget( 0, pRTBackup );
			m_shadowModels.clear();
			
		}
	}
}