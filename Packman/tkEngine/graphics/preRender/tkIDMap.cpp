/*!
 * @brief	IDMap
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkIDMap.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CIDMapModel::CIDMapModel() :
		m_prim(nullptr),
		m_mWVP(CMatrix::Identity)
	{

	}
	CIDMapModel::~CIDMapModel()
	{

	}
	void CIDMapModel::Create(CPrimitive* prim)	
	{
		m_prim = prim;
	}
	void CIDMapModel::Render(CRenderContext& renderContext, CEffect* pEffect )
	{
		if (m_prim) {
			m_mWVP.Transpose();
			pEffect->SetValue(renderContext, "g_mWVP", &m_mWVP, sizeof(m_mWVP));
			renderContext.SetVertexDeclaration(m_prim->GetVertexDecl());
			renderContext.SetStreamSource(0, m_prim->GetVertexBuffer());
			renderContext.SetIndices(m_prim->GetIndexBuffer());
			renderContext.DrawIndexedPrimitive(m_prim);
		}

	}
	CIDMap::CIDMap() :
		m_isEnable(false)
	{
	}
	CIDMap::~CIDMap()
	{
		Release();
	}
	void CIDMap::Create(u32 w, u32 h)
	{
		m_idMapRT.Create( w, h, 1, FMT_A8, FMT_D16, MULTISAMPLE_NONE, 0);
		m_isEnable = true;
		m_pIDMapEffect = CEngine::EffectManager().LoadEffect("Assets/presetshader/idMap.fx");
	}
	void CIDMap::Release()
	{
		m_idMapRT.Release();
	}
	void CIDMap::RenderToIDMap( CRenderContext& renderContext )
	{
		if(m_isEnable){
			CRenderTarget* pRTBackup = renderContext.GetRenderTarget(0);
			renderContext.SetRenderTarget(0, &m_idMapRT);
			m_pIDMapEffect->SetTechnique(renderContext, "RenderIDMap");
			m_pIDMapEffect->Begin(renderContext);
			m_pIDMapEffect->BeginPass(renderContext, 0);
			for (auto model : m_idMapModels) {
				model->Render( renderContext, m_pIDMapEffect );
			}
			m_pIDMapEffect->EndPass(renderContext);
			m_pIDMapEffect->End(renderContext);

			renderContext.SetRenderTarget(0, pRTBackup);
			m_idMapModels.clear();
		}
	}
	void CIDMap::Entry(CIDMapModel* model)
	{
		m_idMapModels.push_back(model);
	}
}
