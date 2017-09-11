#include "stdafx.h"
#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
}
bool Background::Start()
{
	m_skinModelData.Load(L"Assets/modelData/background.cmo");
	m_skinModel.Init(m_skinModelData);
	return true;
}
void Background::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_skinModel.Update({ 0.0f, 0.0f, 0.0f }, qRot, CVector3::One);
}
void Background::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
