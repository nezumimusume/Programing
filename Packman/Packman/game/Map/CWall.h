/*!
 * @brief	壁。
 */

#ifndef _CWALL_H_
#define _CWALL_H_

#include "tkEngine/graphics/prerender/tkIDMap.h"
#include "tkEngine/shape/tkBoxShape.h"

class CWall : public tkEngine::IGameObject{
public:
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Build( const CVector3& size, const CVector3& pos );
private:
	tkEngine::CBoxShape		m_box;	
	tkEngine::CEffect*		m_pEffect;
	tkEngine::CIDMapModel	m_idMapModel;
	tkEngine::CShadowModel	m_shadowModel;
	CMatrix					m_wvpMatrix;	//<ワールドビュープロジェクション行列。
};
#endif