#pragma once
#include "tkEngine/graphics/2D/tkSprite.h"

class MPBar : public IGameObject
{
public:
	MPBar();
	~MPBar();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
private:
	CShaderResourceView m_mpBarTex;
	CShaderResourceView m_mpGaugeTex;
	CSprite	m_mpBar;
	CSprite m_mpGauge;
};

