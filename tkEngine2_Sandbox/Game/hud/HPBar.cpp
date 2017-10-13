#include "stdafx.h"
#include "HPBar.h"



namespace {
	const CVector2 hpGaugeMaxSize = { 245.0f, 31.5f };
	const CVector2 hpBarMaxSize = { 230.5f, 14.2f };
	const CVector3 hpBarPos = { -592.95f, 320.0f - 3, 1.0f };
	const CVector3 hpGaugePos = { -600.0f, 320.0f - 3, 1.0f };
}
HPBar::HPBar()
{
}


HPBar::~HPBar()
{
}

bool HPBar::Start()
{
	m_hpBarTex.CreateFromDDSTextureFromFile(L"sprite/hp.dds");
	m_hpGaugeTex.CreateFromDDSTextureFromFile(L"sprite/hpsp_bar.dds");
	m_hpBarBackTex.CreateFromDDSTextureFromFile(L"sprite/hp_back.dds");

	m_hpBar.Init(m_hpBarTex, hpBarMaxSize.x, hpBarMaxSize.y);
	m_hpGauge.Init(m_hpGaugeTex, hpGaugeMaxSize.x, hpGaugeMaxSize.y);
	m_hpBarBack.Init(m_hpBarBackTex, hpBarMaxSize.x, hpBarMaxSize.y);

	m_hpBar.SetPosition(hpBarPos);
	m_hpGauge.SetPosition(hpGaugePos);
	m_hpBarBack.SetPosition(hpBarPos);

	//ピボットは左中央。
	m_hpBar.SetPivot({ 0.0f, 0.5f });
	m_hpGauge.SetPivot({ 0.0f, 0.5f });
	m_hpBarBack.SetPivot({ 0.0f, 0.5f });

	return true;
}
void HPBar::Update()
{
}
void HPBar::PostRender(CRenderContext& rc)
{
	m_hpGauge.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_hpBarBack.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_hpBar.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}