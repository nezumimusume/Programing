/*!
 *@brief	形状の基本クラス。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkShapeBase.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	CShapeBase::CShapeBase() :
		m_isCreatePrimitive(false),
		m_pPrimitive(nullptr),
		m_position(CVector3::Zero),
		m_worldMatrix(CMatrix::Identity),
		m_rotationMatrix(CMatrix::Identity)
	{
	}
	CShapeBase::~CShapeBase()
	{
		Release();
	}
	void CShapeBase::Release()
	{
		if(!m_isCreatePrimitive){
			delete m_pPrimitive;
			m_pPrimitive = nullptr;
			m_isCreatePrimitive = false;
		}
	}
	void CShapeBase::UpdateWorldMatrix()
	{
		m_rotationMatrix.MakeRotationFromQuaternion(m_rotation);
		CMatrix mTrans;
		mTrans.MakeTranslation(m_position);
		m_worldMatrix.Mul(m_rotationMatrix, mTrans );
	}
	void CShapeBase::Render(CRenderContext& renderContext)
	{
		if (m_pPrimitive == nullptr) {
			return;
		}
		renderContext.SetVertexDeclaration(m_pPrimitive->GetVertexDecl());
		renderContext.SetStreamSource( 0, m_pPrimitive->GetVertexBuffer() );
		renderContext.SetIndices( m_pPrimitive->GetIndexBuffer() );
		renderContext.DrawIndexedPrimitive(	m_pPrimitive);
	}
	void CShapeBase::CreateEffect(bool hasNormal)
	{
		if (hasNormal) {
			m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
		}
		else {
			m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormal.fx");
		}
	}
	void CShapeBase::RenderLight(
		CRenderContext& renderContext,
		const CMatrix& viewProjectionMatrix,
		const CLight& light,
		bool isIluminance
		)
	{
		CMatrix mMVP;
		mMVP.Mul(m_worldMatrix, viewProjectionMatrix);
		if(isIluminance){
			m_pEffect->SetTechnique(renderContext, "ColorNormalPrimIuminance");
		}
		else {
			m_pEffect->SetTechnique(renderContext, "ColorNormalPrim");
		}
		m_pEffect->Begin(renderContext);
		m_pEffect->BeginPass(renderContext, 0);
		m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
		m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &m_rotationMatrix, sizeof(m_rotationMatrix));
		m_pEffect->SetValue(
			renderContext,
			"g_light",
			&light,
			sizeof(CLight)
			);
		m_pEffect->CommitChanges(renderContext);
		Render(renderContext);

		m_pEffect->EndPass(renderContext);
		m_pEffect->End(renderContext);
	}
}
