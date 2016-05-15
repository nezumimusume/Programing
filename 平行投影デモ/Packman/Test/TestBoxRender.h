/*!
 *@brief	ボックス描画のテストクラス。
 */

#ifndef _TESTBOXRENDER_H_
#define _TESTBOXRENDER_H_

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/prerender/tkIDMap.h"

class CTestBoxRender : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	tkEngine::CBoxShape		m_box;
	tkEngine::CEffect*		m_pEffect;
	tkEngine::CCamera		m_camera;		//カメラ。
	tkEngine::CLight		m_light;
	float						m_angle;		//
	tkEngine::CIDMapModel	m_idMapModel;
};
#endif //_TESTBOXRENDER_H_