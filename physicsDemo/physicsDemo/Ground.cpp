#include "stdafx.h"
#include "Ground.h"
#include "bulletPhysics.h"


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
		
		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);

	}
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
	delete m_myMotionState;
	delete m_groundShape;
	delete m_rigidBody;
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