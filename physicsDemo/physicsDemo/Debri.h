#pragma once

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"

class CDebri : public IGameObject {
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	virtual void OnDestroy();
	/*!
	*@brief	構築処理。
	*@param[in]	size	箱のサイズ。
	*@param[in]	pos		箱の座標。
	*/
	void Build(const CVector3& size, const CVector3& pos);
	void SetCamera(CCamera* camera)
	{
		m_camera = camera;
	}
private:
	CCamera*	m_camera;
	CLight		m_light;
	CBoxShape	m_box;
	CShadowModel	m_shadowModel;	//影モデル。
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	float m_life;
};