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
		}
		void CPointLight::SetColor(const CVector4& color)
		{
			light.color = color;
		}
		void CPointLight::SetAttn(const CVector3& attn)
		{
			light.attn = attn;
		}
		bool CPointLight::StartSub()
		{
			return true;
		}
		void CPointLight::Update()
		{
			//カメラ空間での位置を計算する。
			const CMatrix& mView = MainCamera().GetViewMatrix();
			light.positionInView = light.position;
			mView.Mul(light.positionInView);
		}
	}
}