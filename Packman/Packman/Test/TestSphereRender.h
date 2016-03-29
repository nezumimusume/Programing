/*!
 *@brief	球体の描画テスト。
 */

#ifndef TESTSHAPERENDER_H
#define TESTSHAPERENDER_H

#include "tkEngine/shape/tkSphereShape.h"
#include "tkEngine/graphics/tkCamera.h"

class CTestSphereRender : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	tkEngine::CSphereShape	m_sphere;
	tkEngine::CEffect*		m_pEffect;
	tkEngine::CCamera		m_camera;
	f32						m_angle;
};


#endif // #define TESTSHAPERENDER_H