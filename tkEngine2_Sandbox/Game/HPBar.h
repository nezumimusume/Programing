#pragma once
#include "tkEngine/graphics/2D/tkSprite.h"

class HPBar : public IGameObject
{
public:
	HPBar();
	~HPBar();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
private:
	CShaderResourceView m_hpBarTex;
	CShaderResourceView m_hpGaugeTex;
	CShaderResourceView m_hpBarBackTex;
	CSprite	m_hpBar;
	CSprite m_hpBarBack;
	CSprite m_hpGauge;
};

