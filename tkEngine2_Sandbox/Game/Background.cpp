#include "stdafx.h"
#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
}
bool Background::Start()
{
	m_skinModelData.Load(L"Assets/modelData/background.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);

	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;
	rbInfo.pos.Set( 0.0f, 20.0f, 0.0f );
	//rbInfo.rot.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_rigidBody.Create(rbInfo);
	PhysicsWorld().AddRigidBody(&m_rigidBody);

	rbInfo.collider = &m_meshCollider2;
	m_rigidBody2.Create(rbInfo);
	PhysicsWorld().AddRigidBody(&m_rigidBody2);

	return true;
}
void Background::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_skinModel.Update({ 0.0f, 20.0f, 0.0f }, CQuaternion::Identity, CVector3::One);
}
void Background::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
