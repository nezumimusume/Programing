/*!
 * @brief	ゲームマネージャ。
 */

#ifndef _CGAMEMANAGER_H_
#define _CGAMEMANAGER_H_

#include "Packman/game/CCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "Packman/game/map/CMapBuilder.h"

class CGameManager : public tkEngine::IGameObject{
public:
	CGameManager();
	~CGameManager();
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	static CGameManager& GetInstance()
	{
		return *m_instance;
	}
	CGameCamera&  GetGameCamera()
	{
		return m_camera;
	}
	CLight& GetGroundLight()
	{
		return m_groundLight;
	}
private:
	CGameCamera		m_camera;
	CLight			m_groundLight;		//地面のライト
	static CGameManager*	m_instance;	//唯一のインスタンス。
	CMapBuilder		m_mapBuilder;
};

#endif //_CGAMEMANAGER_H_