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
	m_skinModelData2.Load(L"Assets/modelData/background2.cmo");
	m_skinModel2.Init(m_skinModelData2);

	m_normalMapSRV.CreateFromDDSTextureFromFile(L"Assets/modelData/BB_Map_1A Normal.dds");
	m_skinModel.FindMesh([&](auto& mesh) {
		CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
		if (effect->EqualMaterialName(L"Material #25")) {
			effect->SetNormalMap(m_normalMapSRV.GetBody());
		}
	});
	m_skinModel.SetShadowReceiverFlag(true);
	m_skinModel2.SetShadowReceiverFlag(true);
	m_skinModel2.SetShadowCasterFlag(true);

	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	m_meshCollider2.CreateFromSkinModel(m_skinModel2, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;
	rbInfo.pos.Set( 0.0f, 20.0f, 0.0f );
	rbInfo.rot.SetRotationDeg(CVector3::AxisX, -90.0f);
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
	m_skinModel.Update({ 0.0f, 20.0f, 0.0f }, qRot, CVector3::One);
	m_skinModel2.Update({ 0.0f, 20.0f, 0.0f }, qRot, CVector3::One);
}
void Background::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	m_skinModel2.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
