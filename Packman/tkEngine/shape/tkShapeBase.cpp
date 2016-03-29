/*!
 *@brief	形状の基本クラス。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkShapeBase.h"

namespace tkEngine{
	CShapeBase::CShapeBase() :
		m_isCreatePrimitive(false),
		m_pPrimitive(nullptr),
		m_position(CVector3::Zero),
		m_worldMatrix(CMatrix::Identity)
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
		CMatrix mRot;
		mRot.MakeRotationFromQuaternion(m_rotation);
		CMatrix mTrans;
		mTrans.MakeTranslation(m_position);
		m_worldMatrix.Mul(mRot, mTrans );
	}
	void CShapeBase::Render(CRenderContext& renderContext)
	{
		if (m_pPrimitive == nullptr) {
			return;
		}
		renderContext.SetRenderCommand(CRenderCommand_SetFVF(m_pPrimitive->GetVertexFormat()));
		renderContext.SetRenderCommand(CRenderCommand_SetStreamSource(
			0,
			m_pPrimitive->GetVertexBuffer()
			));
		renderContext.SetRenderCommand(CRenderCommand_SetIndices(
			m_pPrimitive->GetIndexBuffer()
			));
		renderContext.SetRenderCommand(CRenderCommand_DrawIndexedPrimitive(
			m_pPrimitive
			));
	}
}
