#include "stdafx.h"
#include "Ground.h"
#include "bulletPhysics.h"
#include "DebriCreator.h"
#include "Camera.h"

void CGround::OnPlayerOverlapDebriCreator(const btCollisionObject* collisionObject)
{
	if (m_debriCreateSwitch == collisionObject)
	{
		CDebriCreator* debriCreator = CGameObjectManager::Instance().NewGameObject<CDebriCreator>(0);	//ゴミ生成機を登録。
		debriCreator->SetCamera(camera.GetCamera());
		//ワールドから削除
		g_bulletPhysics.RemoveCollisionObject(m_debriCreateSwitch);
	}
}
void CGround::Start()
{
	CVector3 boxSize(1000.0f, 10.0f, 1000.0f);
	CVector3 boxPosition(0.0f, -5.0f, 0.0f);
	//剛体を初期化。
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		m_groundShape = new btBoxShape(btVector3(boxSize.x*0.5f,boxSize.y*0.5f,boxSize.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin( btVector3( boxPosition.x, boxPosition.y, boxPosition.z ) );
		float mass = 0.0f;
		
		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(rbInfo);
		m_rigidBody->setUserIndex(CollisionType_Ground);
		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);
	}
	m_debriCreateSwitch = new btGhostObject();
	m_debriCreateSwitch->setCollisionShape(new btSphereShape(2.0f));
	btTransform trans(btQuaternion(0.0f,0.0f,0.0f,1.0f),btVector3(0.0f,0.0f,0.0f) );
	m_debriCreateSwitch->setWorldTransform(trans);
	m_debriCreateSwitch->setUserPointer(this);

	g_bulletPhysics.AddCollisionObject(m_debriCreateSwitch);
	m_debriCreateSwitch->setUserIndex(CollisionType_DebriCreator);
	//m_rigidBody = new btRigidBody
	m_box.Create(boxSize, 0x88888888, true);
	m_box.SetPosition(boxPosition);
	m_box.UpdateWorldMatrix();
	m_light.SetDiffuseLightColor(0, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetDiffuseLightDirection(0, CVector3(0.0f, -1.0f, 0.0f));
}
void CGround::OnDestroy()
{
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	g_bulletPhysics.RemoveCollisionObject(m_debriCreateSwitch);
	delete m_myMotionState;
	delete m_groundShape;
	delete m_rigidBody;
	delete m_debriCreateSwitch;
}
void CGround::Update()
{

}
void CGround::Render(CRenderContext& renderContext)
{
	m_box.RenderLight(
		renderContext,
		m_camera->GetViewProjectionMatrix(),
		m_light,
		false,
		true
	);
}