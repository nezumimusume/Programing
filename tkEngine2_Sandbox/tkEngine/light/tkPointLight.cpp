/*!
 *@brief	ポイントライト
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/light/tkPointLight.h"

namespace tkEngine{
	namespace prefab {
		CPointLight::CPointLight()
		{
			light.color = CVector3::One;
			light.position = CVector3::Zero;
			light.positionInView = CVector3::Zero;
		}
		CPointLight::~CPointLight()
		{

		}
		void CPointLight::SetPosition(const CVector3& pos)
		{
			light.position = pos;
			LightManager().SetDirty();
			m_isDirty = true;
		}
		void CPointLight::SetColor(const CVector4& color)
		{
			light.color = color;
			LightManager().SetDirty();
		}
		void CPointLight::SetAttn(const CVector3& attn)
		{
			light.attn = attn;
			LightManager().SetDirty();
		}
		bool CPointLight::StartSub()
		{
			return true;
		}
		void CPointLight::Update()
		{
			if (!m_isDirty) {
				return;
			}
			//カメラ空間での位置を計算する。
			const CMatrix& mView = MainCamera().GetViewMatrix();
			light.positionInView = light.position;
			mView.Mul(light.positionInView);
			m_isDirty = false;
		}
	}
}