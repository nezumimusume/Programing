#include "stdafx.h"
#include "MPBar.h"



namespace {
	const CVector2 mpGaugeMaxSize = { 245.0f, 31.5f };
	const CVector2 mpBarMaxSize = { 230.5f, 14.2f };
	const CVector3 mpBarPos = { -592.95f, 278.0f - 3, 1.0f };
	const CVector3 mpGaugePos = { -600.0f, 278.0f - 3, 1.0f };
}
MPBar::MPBar()
{
}


MPBar::~MPBar()
{
}

bool MPBar::Start()
{
	m_mpBarTex.CreateFromDDSTextureFromFile(L"Assets/sprite/mp.dds");
	m_mpGaugeTex.CreateFromDDSTextureFromFile(L"Assets/sprite/hpsp_bar.dds");

	m_mpBar.Init(m_mpBarTex, mpBarMaxSize.x, mpBarMaxSize.y);
	m_mpGauge.Init(m_mpGaugeTex, mpGaugeMaxSize.x, mpGaugeMaxSize.y);

	m_mpBar.SetPosition(mpBarPos);
	m_mpGauge.SetPosition(mpGaugePos);


	//ピボットは左中央。
	m_mpBar.SetPivot({ 0.0f, 0.5f });
	m_mpGauge.SetPivot({ 0.0f, 0.5f });

	return true;
}
void MPBar::Update()
{
}
void MPBar::PostRender(CRenderContext& rc)
{
	m_mpGauge.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_mpBar.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}