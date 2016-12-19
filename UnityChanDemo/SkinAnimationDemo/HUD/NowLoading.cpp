/*!
 * @brief	NowLoading
 */

#include "stdafx.h"
#include "NowLoading.h"

NowLoading::NowLoading()
{
	
}
NowLoading::~NowLoading()
{
}
bool NowLoading::Start()
{
	m_backGroundTex.Load("Assets/sprite/NowLoadingBG.jpg");
	m_backGround.Init(&m_backGroundTex);

	CVector2 size;
	size.x = (float)Engine().GetFrameBufferWidth();
	size.y = (float)Engine().GetFrameBufferHeight();
	m_backGround.SetSize(size);

	m_iconTex.Load("Assets/sprite/NowLoadingIcon.png");
	m_icon.Init(&m_iconTex);
	size.x = 64.0f;
	size.y = 64.0f;
	m_icon.SetSize(size);
	CVector2 pos;
	pos.x = Engine().GetFrameBufferWidth() * 0.5f;
	pos.y = Engine().GetFrameBufferHeight() * -0.5f;
	pos.x -= size.x * 1.4f;
	pos.y += size.y * 1.4f;
	m_icon.SetPosition(pos);
	//ロードが終わったら非アクティブにする。
	SetActiveFlag(false);
	return true;
}
void NowLoading::Update()
{
	m_angle += 0.1f;
	m_rotation.SetRotation(CVector3::AxisZ, m_angle);
	m_icon.SetRotation(m_rotation);
}
void NowLoading::PostRender(CRenderContext& renderContext)
{
	m_backGround.Draw(renderContext);
	m_icon.Draw(renderContext);
}