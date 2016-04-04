/*!
 * @brief	パックマンが食べるアイテム。
 */

#ifndef _CFOOD_H_
#define _CFOOD_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFood : public tkEngine::IGameObject{
public:
	
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Build( f32 radius, const CVector3& pos );
private:
	tkEngine::CSphereShape	m_sphere;
	tkEngine::CEffect*		m_pEffect;
	CMatrix					m_wvpMatrix;	//<ワールドビュープロジェクション行列。
	tkEngine::CIDMapModel	m_idMapModel;
};

#endif // _CFOOD_H_