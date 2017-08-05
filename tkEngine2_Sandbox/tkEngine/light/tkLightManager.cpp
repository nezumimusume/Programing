/*!
 * @brief	ライトの管理者。
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/light/tkLightManager.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"

namespace tkEngine{
	CLightManager::CLightManager()
	{
	}
	CLightManager::~CLightManager()
	{
	}
	void CLightManager::Init()
	{
	}
	void CLightManager::AddLight(CLightBase* light)
	{
		//ライトの振り分け。。。
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			m_pointLights.push_back(reinterpret_cast<CPointLight*>(light));
		}
		else if (typeInfo == typeid(CDirectionLight)) {
			m_directionLights.push_back(reinterpret_cast<CDirectionLight*>(light));
		}
		
	}
	void CLightManager::RemoveLight(CLightBase* light)
	{
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			m_pointLights.erase(
				std::remove(m_pointLights.begin(), m_pointLights.end(), light), 
				m_pointLights.end()
			);
		}
		else if (typeInfo == typeid(CDirectionLight)) {
			m_directionLights.erase(
				std::remove(m_directionLights.begin(), m_directionLights.end(), light),
				m_directionLights.end()
			);
		}
	}
	void CLightManager::Update()
	{
	}
}