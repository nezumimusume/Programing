/*!
 * @brief	カメラ。
 */

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "tkEngine/graphics/tkCamera.h"

class CGameCamera : public tkEngine::IGameObject{ 
public:
	CGameCamera();
	~CGameCamera();
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	const CMatrix& GetViewProjectionMatrix()
	{
		return m_camera.GetViewProjectionMatrix();
	}
private:
	tkEngine::CCamera	m_camera;	//!<カメラ。
};
#endif // _CCAMERA_H_