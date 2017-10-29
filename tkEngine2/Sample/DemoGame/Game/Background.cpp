/*!
 * @brief	îwåiÅB
 */
#include "stdafx.h"
#include "Background.h"

bool Background::Start()
{
	m_skinModelData.Load(L"modelData/Background.cmo");
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	m_skinModel.SetShadowCasterFlag(true);
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;

	m_rigidBody.Create(rbInfo);
	PhysicsWorld().AddRigidBody(m_rigidBody);

	return true;
}
void Background::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Background::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}