/*!
 *@brief	ínå`ÅB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/nature/tkTerrain.h"

namespace tkEngine{
	CTerrain::CTerrain()
	{
	}
	CTerrain::~CTerrain()
	{
	}
	void CTerrain::Init( 
		const char* skinModelDataPath, 
		const char* splatMapPath, 
		const char* texturePaths[],
		const CCamera& camera,
		const CLight& light
	)
	{
		m_skinModelDataPath = skinModelDataPath;
		m_splatMapPath = splatMapPath;
		for (int i = 0; i < MAX_TEXTURE; i++) {
			if (texturePaths[i] == NULL) {
				//î‘ï∫
				break;
			}
			m_texturePaths[i] = texturePaths[i];
		}
		m_camera = &camera;
		m_light = &light;
	}
	bool CTerrain::Start()
	{
		switch (m_initStep) {
		case InitStep::enStartLoad:
			m_skinModelData.LoadModelDataAsync(m_skinModelDataPath.c_str(), nullptr);
			break;
		case InitStep::enWatiLoad:
			if (m_skinModelData.IsLoadEnd()) {
				m_skinModel.Init(m_skinModelData.GetBody());
				m_skinModel.SetLight(m_light);
				m_splatMap.Load(m_splatMapPath.c_str());
				int i = 0;
				for (auto& texPath : m_texturePaths) {
					m_textures[i].Load(texPath.c_str());
					i++;
				}
			}
			break;
		}
		return true;
	}
	void CTerrain::Update() 
	{
		m_skinModel.Update(m_position, m_rotation, m_scale);
	}
	void CTerrain::Render(CRenderContext& renderContext)
	{
		m_skinModel.Draw(renderContext, m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
	}
}
