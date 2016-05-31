#pragma once

#include "tkEngine/shape/tkBoxShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"

class CGround : public IGameObject {
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	virtual void OnDestroy();
	void SetCamera(CCamera* cam)
	{
		m_camera = cam;
	}
	void OnPlayerOverlapDebriCreator(const btCollisionObject* collisionObject);
private:
	CCamera*		m_camera;
	CLight			m_light;
	CBoxShape		m_box;
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape;			//地面のコリジョン形状。
	btRigidBody*		m_rigidBody;			//剛体。
	btDefaultMotionState* m_myMotionState;
	btGhostObject*		m_debriCreateSwitch;		//デブリ作成スイッチ。
};