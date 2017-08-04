/*!
 *@brief	ディレクションライト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/gameObject/light/tkDirectionLight.h"

namespace tkEngine{
	CDirectionLight::CDirectionLight()
	{
		light.color = CVector3::One;
		light.direction = CVector3::Down;
	}
	CDirectionLight::~CDirectionLight()
	{

	}
	bool CDirectionLight::Start()
	{
		
		return true;
	}
	void CDirectionLight::Update()
	{
	}
}