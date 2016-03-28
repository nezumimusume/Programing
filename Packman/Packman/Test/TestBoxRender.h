/*!
 *@brief	ボックス描画のテストクラス。
 */

#ifndef _TESTBOXRENDER_H_
#define _TESTBOXRENDER_H_

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkCamera.h"

class CTestBoxRender : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	tkEngine::CBoxShape	m_box;
	tkEngine::CEffect*	m_pEffect;
	tkEngine::CCamera	m_camera;		//カメラ。
	f32					m_angle;		//
};
#endif //_TESTBOXRENDER_H_