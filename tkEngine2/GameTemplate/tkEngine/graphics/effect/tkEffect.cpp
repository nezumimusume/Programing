/*!
 * @brief	エフェクト
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/effect/tkEffect.h"


namespace tkEngine {
	namespace prefab {
		CEffect::CEffect()
		{
		}
		CEffect::~CEffect()
		{
			Release();
		}

		void CEffect::Release()
		{
			if (m_handle != -1) {
				GraphicsEngine().GetEffectEngine().Stop(m_handle);
				m_handle = -1;
			}
			ES_SAFE_RELEASE(m_effect);
		}
		void CEffect::Init(const wchar_t* filePath)
		{
			m_effect = GraphicsEngine().GetEffectEngine().CreateEffekseerEffect(filePath);

		}

		void CEffect::Play()
		{
			m_handle = GraphicsEngine().GetEffectEngine().Play(m_effect);
		}
		void CEffect::Update()
		{
			CMatrix mTrans, mRot, mBaseMat;
			mTrans.MakeTranslation(m_position);
			mRot.MakeRotationFromQuaternion(m_rotation);
			mBaseMat.Mul(mRot, mTrans);
			GraphicsEngine().GetEffectEngine().GetEffekseerManager().SetBaseMatrix(m_handle, mBaseMat);
			if (IsPlay() == false) {
				//再生完了したら終わる。
				DeleteGO(this);
			}
		}
	}
}