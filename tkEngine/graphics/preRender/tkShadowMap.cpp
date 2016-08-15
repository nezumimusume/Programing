/*!
 * @brief	シャドウマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{
	
	CShadowMap::CShadowMap() :
		m_isEnable(false),
		m_pShadowMapEffect(nullptr),
		m_near(1.0f),
		m_far(100.0f),
		m_lvMatrix(CMatrix::Identity),
		m_accpect(1.0f),
		m_shadowAreaW(2.0f),
		m_shadowAreaH(2.0f)
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
		m_shadowMapRT.Create( w, h, 1, FMT_G32R32F, FMT_D16, MULTISAMPLE_NONE, 0 );
		m_isEnable = true;
		m_pShadowMapEffect = CEngine::EffectManager().LoadEffect( "Assets/presetshader/shadowMap.fx" );
		m_accpect = s_cast<float>(w) / s_cast<float>(h);
		/*m_projectionMatrix.MakeProjectionMatrix(
			CMath::DegToRad(60.0f),
			s_cast<float>(w) / s_cast<float>(h),
			m_near,
			m_far
		);*/
		
		m_projectionMatrix.MakeOrthoProjectionMatrix(m_shadowAreaW * m_accpect, m_shadowAreaH, m_near, m_far);
#ifdef USE_VSM
		m_gaussianBlur.Init(w, h, *m_shadowMapRT.GetTexture());
#endif
	}
	void CShadowMap::Release()
	{
		m_shadowMapRT.Release();
	}
	void CShadowMap::Entry( IShadowCaster* caster )
	{
		m_shadowCaster.push_back(caster);
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
		
			m_projectionMatrix.MakeOrthoProjectionMatrix(m_shadowAreaW * m_accpect, m_shadowAreaH, m_near, m_far);
			
			//ライトからみたビュー行列を作成。
			CVector3 target;
			target.Add(m_lightPosition, m_lightDirection);
			m_lvMatrix.MakeLookAt(m_lightPosition, target, lightUp);
			m_LVPMatrix.Mul(m_lvMatrix, m_projectionMatrix);
		}

	}
	void CShadowMap::RenderToShadowMap( CRenderContext& renderContext )
	{
		if (m_isEnable) {

			CRenderTarget* pRTBackup = renderContext.GetRenderTarget(0);
			renderContext.SetRenderTarget(0, &m_shadowMapRT);
			renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			//renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			for (auto caster : m_shadowCaster) {
				caster->Render(renderContext, m_pShadowMapEffect, m_LVPMatrix);
			}
			renderContext.SetRenderTarget(0, pRTBackup);
			m_shadowCaster.clear();
#ifdef USE_VSM
			//ガウシアンブラーをかけて深度マップの平均値を求める。
			m_gaussianBlur.Draw(renderContext);
#endif
		}
	}
}