#pragma once
#include "tkEngine/graphics/tkCamera.h"

class CDebriCreator : public IGameObject{
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	void SetCamera(CCamera* camera)
	{
		m_pCamera = camera;
	}
private:
	float	m_interval;
	CCamera*	m_pCamera;
};