/*!
 *@brief	ディレクションライト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/light/tkDirectionLight.h"

namespace tkEngine{
	namespace prefab {
		CDirectionLight::CDirectionLight()
		{
			light.color = CVector3::One;
			light.direction = CVector3::Down;
		}
		CDirectionLight::~CDirectionLight()
		{

		}
		bool CDirectionLight::StartSub()
		{
			return true;
		}
		void CDirectionLight::Update()
		{
		}
		void CDirectionLight::SetDirection(const CVector3& direction)
		{
			light.direction = direction;
			LightManager().SetDirty();
		}
		void CDirectionLight::SetColor(const CVector3& color)
		{
			light.color = color;
			LightManager().SetDirty();
		}
	}
}