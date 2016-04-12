/*!
 * @brief	パックマンが食べるアイテム。
 */

#ifndef _CFOOD_H_
#define _CFOOD_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFood : public tkEngine::IGameObject{
public:
	void Awake() override final;
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Build( f32 radius, const CVector3& pos );
private:
	static tkEngine::CSphereShape*	m_sphere;
	CMatrix							m_wvpMatrix;			//<ワールドビュープロジェクション行列。
	tkEngine::CIDMapModel			m_idMapModel;
	CVector3						m_position;
};

#endif // _CFOOD_H_