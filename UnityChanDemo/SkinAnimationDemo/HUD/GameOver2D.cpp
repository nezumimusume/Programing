/*!
 * @brief	GameOver2D
 */

#include "stdafx.h"
#include "GameOver2D.h"

GameOver2D::GameOver2D()
{
}
GameOver2D::~GameOver2D()
{
}
bool GameOver2D::Start()
{
	m_youDeadTex.Load("Assets/sprite/GameOver.png");
	m_youDeadSprite.Init(&m_youDeadTex);
	m_youDeadSprite.SetAlpha(0.0f);
	CVector2 size;
	size.x = 800.0f;
	size.y = 450.0f;
	m_youDeadSprite.SetSize(size);
	return true;
}
void GameOver2D::Update() 
{
	m_timer += GameTime().GetFrameDeltaTime();
	switch (m_state) {
	case State_WaitFadeIn:
		if (m_timer > 1.0f) {
			m_state = State_FadeIn;
			m_timer = 0.0f;
		}
		break;
	case State_FadeIn:
		float alpha = min(1.0f, m_timer / 2.0f);		//3秒かけてフェードイン。
		m_youDeadSprite.SetAlpha(alpha);
		break;
	}
	
	
}
void GameOver2D::PostRender(CRenderContext& renderContext) 
{
	m_youDeadSprite.Draw(renderContext);
}