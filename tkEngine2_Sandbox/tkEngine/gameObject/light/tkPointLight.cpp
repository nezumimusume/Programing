/*!
 *@brief	ポイントライト
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/gameObject/light/tkPointLight.h"

namespace tkEngine{
	CPointLight::CPointLight()
	{
		light.color = CVector3::One;
		light.position = CVector3::Zero;
		light.positionInView = CVector3::Zero;
	}
	CPointLight::~CPointLight()
	{
		
	}
	bool CPointLight::Start()
	{
		return true;
	}
	void CPointLight::Update()
	{
	}
}