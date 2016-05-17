#pragma once
#include "tkEngine/shape/tkSphereShape.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkCamera.h"

class CPlayer : public IGameObject{
public:
	CPlayer()
	{
		m_camera = nullptr;
	}
	virtual void Start() ;
	virtual void PreUpdate();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	void SetCamera(CCamera* cam)
	{
		m_camera = cam;
	}
private:
	CVector3		m_position;
	CSphereShape	m_shape;
	CCamera*		m_camera;
	CLight			m_light;
	float			m_radius;
	CShadowModel	m_shadowModel;	//影モデル。
	CVector3		m_moveSpeed;	//移動速度。
	
	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
};
