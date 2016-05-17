#include "stdafx.h"
#include "Wall.h"
#include "bulletPhysics.h"


void CWall::Start()
{
	m_light.SetDiffuseLightColor(0, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetDiffuseLightDirection(0, CVector3(0.0f, -1.0f, 0.0f));
}
void CWall::Update()
{

}
void CWall::Render(CRenderContext& renderContext)
{
	m_box.RenderLight(
		renderContext,
		m_camera->GetViewProjectionMatrix(),
		m_light,
		false,
		true
		);
}
void CWall::OnDestroy()
{
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	delete m_myMotionState;
	delete m_groundShape;
	delete m_rigidBody;
}
/*!
*@brief	構築処理。
*@param[in]	size	箱のサイズ。
*@param[in]	pos		箱の座標。
*/
void CWall::Build(const CVector3& size, const CVector3& pos)
{
	m_box.Create(size, 0xffff0000, true);
	m_box.SetPosition(pos);
	m_box.UpdateWorldMatrix();
	m_shadowModel.Create(m_box.GetPrimitive());

	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_groundShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 0.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);

	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);

}
