/*!
 * @brief	フォント。
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/font/tkFont.h"

namespace tkEngine{
	CFont::CFont()
	{
		m_spriteBatch = GraphicsEngine().GetSpriteBatch();
		m_spriteFont = GraphicsEngine().GetSpriteFont();
	}
	CFont::~CFont()
	{
	}

	void CFont::Begin()
	{
		m_spriteBatch->Begin();
	}
	void CFont::End()
	{
		m_spriteBatch->End();
	}
	void CFont::Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color,
		float rotation,
		float scale,
		CVector2 pivot)
	{		
		pivot.y = 1.0f - pivot.y;
		DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
		//座標系をスプライトと合わせる。
		CVector2 pos = position;
		float frameBufferHalfWidth = GraphicsEngine().GetFrameBufferWidth() * 0.5f;
		float frameBufferHalfHeight = GraphicsEngine().GetFrameBufferHeight() * 0.5f;
		pos.x += frameBufferHalfWidth;
		pos.y = -pos.y + frameBufferHalfHeight;
		m_spriteFont->DrawString(
			m_spriteBatch,
			text,
			pos.vec,
			color,
			rotation,
			DirectX::XMFLOAT2(pivot.x, pivot.y),
			scale
		);
	}
}