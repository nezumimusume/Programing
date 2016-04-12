/*!
 * @brief	ínñ ÅB
 */

#ifndef _CGROUND_H_
#define _CGROUND_H_

#include "tkEngine/shape/tkBoxShape.h"

class CGround : public tkEngine::IGameObject{
public:
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Create( float xz_size );
private:
	tkEngine::CBoxShape		m_box;	
	tkEngine::CEffect*		m_pEffect;
};
#endif 