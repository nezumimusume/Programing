#include "stdafx.h"
#include "DebriCreator.h"
#include "Debri.h"


void CDebriCreator::Start()
{
	m_interval = 0.0f;
}
void CDebriCreator::Update()
{
	//m_interval += 1.0f / 60.0f;
	//if (m_interval > 0.1f) {
		//1秒経過。
		//ゴミ作成。
		CDebri* debri = CGameObjectManager::Instance().NewGameObject<CDebri>(0);
		int x = rand() % 10;
		int z = rand() % 10;
		if (rand() % 2 == 0) {
			x *= -1;
		}
		if (rand() % 2 == 0) {
			z *= -1;
		}
		debri->Build(CVector3(0.02f, 0.02f, 0.02f), CVector3(0.2f *x, 5.0f, 0.2f*z));
		debri->SetCamera(m_pCamera);
		//m_interval = 0.0f;
	//}
}
void CDebriCreator::Render(CRenderContext& renderContext)
{

}