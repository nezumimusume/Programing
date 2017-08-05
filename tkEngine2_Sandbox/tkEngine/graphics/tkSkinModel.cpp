/*!
 *@brief	スキンモデル。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	CSkinModel::CSkinModel()
	{
	}
	CSkinModel::~CSkinModel()
	{
	}
	void CSkinModel::Init(CSkinModelData& modelData)
	{
		m_skinModelData = &modelData;
		m_cb.Create(NULL, sizeof(SVSConstantBuffer));
	}
	
	void CSkinModel::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
	{
		CMatrix mScale, mTrans, mRot;
		mScale.MakeScaling(scale);
		mRot.MakeRotationFromQuaternion(rot);
		mTrans.MakeTranslation(trans);
		m_worldMatrix.Mul(mScale, mRot);
		m_worldMatrix.Mul(m_worldMatrix, mTrans);
		GraphicsEngine().GetZPrepass().AddSkinModel(this);
	}
	void CSkinModel::Draw(
		CRenderContext& renderContext, 
		const CMatrix& viewMatrix, 
		const CMatrix& projMatrix,
		bool isZPrepass
	)
	{
		(void)renderContext;
		if (m_skinModelData != nullptr) {
			DirectX::CommonStates state(GraphicsEngine().GetD3DDevice());
			//定数バッファを更新。
			SVSConstantBuffer vsCb;
			vsCb.mWorld = m_worldMatrix;
			vsCb.mProj = projMatrix;
			vsCb.mView = viewMatrix;
			vsCb.screenParam.x = 0.0f;
			vsCb.screenParam.y = 0.0f;
			vsCb.screenParam.z = static_cast<float>(GraphicsEngine().GetFrameBufferWidth());
			vsCb.screenParam.w = static_cast<float>(GraphicsEngine().GetFrameBufferHeight());
			vsCb.isZPrepass = isZPrepass ? 1 : 0;
			renderContext.UpdateSubresource(m_cb, vsCb);
			renderContext.VSSetConstantBuffer(0, m_cb);
			renderContext.PSSetConstantBuffer(0, m_cb);
			m_skinModelData->GetBody().Draw(
				GraphicsEngine().GetD3DDeviceContext(),
				state,
				m_worldMatrix,
				viewMatrix,
				projMatrix
			);
		}
	}
}
