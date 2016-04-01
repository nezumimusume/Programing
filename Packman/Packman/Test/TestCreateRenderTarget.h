/*!
 *@brief	レンダリングターゲットの作成テスト。
 */

#ifndef _TESTCREATERENDERTARGET_H_
#define _TESTCREATERENDERTARGET_H_

#include "tkEngine/graphics/tkRenderTarget.h"

class CTestCreateRenderTarget : public tkEngine::IGameObject{
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
private:
	tkEngine::CRenderTarget		m_renderTarget;		//!<レンダリングターゲット。
};


#endif //_TESTCREATERENDERTARGET_H_