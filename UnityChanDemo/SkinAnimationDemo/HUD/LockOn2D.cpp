/*!
 * @brief	ロックオン
 */

#include "stdafx.h"
#include "HUD/LockOn2d.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyParameter.h"

LockOn2D::LockOn2D()
{
}
LockOn2D::~LockOn2D()
{
}
bool LockOn2D::Start()
{
	m_lockOnTexture.Load("Assets/sprite/LockOn.png");
	m_lockOnSprite.Init(&m_lockOnTexture);
	m_lockOnSprite.SetPosition({0.0f, 0.0f});
	m_lockOnSprite.SetSize({ 64, 64 });
	return true;
}
void LockOn2D::Update()
{
	if (m_lockOnEnemy) {
		//ロックオンカーソルの座標を更新する。
		CVector2 lockOnCursorPos;
		CVector3 enemyCenterPos = m_lockOnEnemy->GetPosition();
		float positionMend = 0.0f;
		if (!strcmp(m_lockOnEnemy->GetEnemyParam()->name, "enemy_01"))
		{
			positionMend = 1.0f;
		}
		enemyCenterPos.y += m_lockOnEnemy->GetHeight() * 0.5f + positionMend;
		g_camera->GetCamera().CalcScreenPositionFromWorldPosition(
			lockOnCursorPos,
			enemyCenterPos
		);
		m_lockOnSprite.SetPosition(lockOnCursorPos);
	}
}
void LockOn2D::PostRender(CRenderContext& renderContext) 
{
	if (m_lockOnEnemy) {
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
		renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);
		m_lockOnSprite.Draw(renderContext);
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}