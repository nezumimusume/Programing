#include "stdafx.h"
#include "ScreenEffect/Fade.h"


Fade::Fade()
{
}
Fade::~Fade()
{
}
bool Fade::Start()
{
	m_texture.Load("Assets/sprite/fade.png");
	m_sprite.Init(&m_texture);
	m_sprite.SetSize({ 
		static_cast<float>(Engine().GetFrameBufferWidth()), 
		static_cast<float>(Engine().GetFrameBufferHeight()) });
	SetActiveFlag(false);
	m_sprite.SetAlpha(0.0f);
	return true;
}	
void Fade::Update()
{
	if (m_isExecute) {
		switch (m_state) {
		case eFadeOut: {
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(min(t, 1.0f));
			}
			else {
				m_isExecute = false;
				m_sprite.SetAlpha(1.0f);
			}
		}break;
		case eFadeIn:
			m_timer += GameTime().GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite.SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//透明になったので非アクティブにする。
				m_sprite.SetAlpha(0.0f);
				SetActiveFlag(false);
				m_isExecute = false;
			}
			break;
		}
	}
}
void Fade::PostRender( CRenderContext& renderContext )
{
	m_sprite.Draw(renderContext);
}
