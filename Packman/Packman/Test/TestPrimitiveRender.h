/*!
 * @brief	プリミティブ描画のテストクラス。
 */

#ifndef TESTPRIMITIVERENDER_H
#define TESTPRIMITIVERENDER_H

#include "tkEngine/graphics/tkPrimitive.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkEffect.h"

class CTestPrimitiveRender : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	tkEngine::CPrimitive	m_primitive;	//プリミティブ。
	tkEngine::CCamera		m_camera;		//カメラ。
	tkEngine::CEffect*		m_pEffect;		//エフェクト。
};
#endif //TESTPRIMITIVERENDER_H