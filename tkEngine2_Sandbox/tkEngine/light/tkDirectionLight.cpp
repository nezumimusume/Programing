/*!
 *@brief	ディレクションライト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/light/tkDirectionLight.h"

namespace tkEngine{
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
}