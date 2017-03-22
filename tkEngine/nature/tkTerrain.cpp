/*!
 *@brief	地形。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/nature/tkTerrain.h"

namespace tkEngine{
	CTerrain::CTerrain()
	{
	}
	CTerrain::~CTerrain()
	{
		PhysicsWorld().RemoveRigidBody(&m_rigidBody);
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
		if (splatMapPath != nullptr) {
			m_splatMapPath = splatMapPath;
		}
		for (int i = 0; i < MAX_TEXTURE; i++) {
			if (texturePaths[i] == NULL) {
				//番兵
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
			m_initStep = InitStep::enWatiLoad;
			break;
		case InitStep::enWatiLoad:
			if (m_skinModelData.IsLoadEnd()) {
				m_skinModel.Init(m_skinModelData.GetBody());
				m_skinModel.SetLight(m_light);
				m_skinModel.SetShadowReceiverFlag(true);
				m_skinModel.SetShadowCasterFlag(true);
				m_splatMap.Load(m_splatMapPath.c_str());
				int i = 0;
				for (auto& texPath : m_texturePaths) {
					m_textures[i].Load(texPath.c_str());
					i++;
				}
				//コリジョンを初期化。
				Update();
				CMatrix* rootBoneMatrix = m_skinModelData.GetBody()->GetRootBoneWorldMatrix();
				//メッシュコライダーを作成。
				m_meshCollider.CreateFromSkinModel(&m_skinModel, rootBoneMatrix);
				//剛体を作成。
				RigidBodyInfo rbInfo;
				rbInfo.collider = &m_meshCollider;
				rbInfo.mass = 0.0f;
				m_rigidBody.Create(rbInfo);
				m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Ground);
				//剛体をワールドに追加。
				PhysicsWorld().AddRigidBody(&m_rigidBody);

				return true;
			}
			break;
		}
		return false;
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
