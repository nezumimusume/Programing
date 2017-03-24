/*!
 *@brief	地形。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/nature/tkTerrain.h"
#include "tkEngine/graphics/material/tkSkinModelMaterial.h"

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
	void CTerrain::CalcWidthAndHeight()
	{
		const std::vector<LPD3DXMESH>& meshList = m_skinModel.GetMeshList();
		float minX = FLT_MAX;
		float minZ = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxZ = -FLT_MAX;
		for (auto& mesh : meshList) {
			//頂点バッファを取得。
			LPDIRECT3DVERTEXBUFFER9 vb;
			mesh->GetVertexBuffer(&vb);
			//頂点定義を取得。
			D3DVERTEXBUFFER_DESC desc;
			vb->GetDesc(&desc);
			//頂点ストライドを取得。
			int stride = mesh->GetNumBytesPerVertex();
			D3DXVECTOR3* vertexPos;
			vb->Lock(0, desc.Size, (void**)&vertexPos, D3DLOCK_READONLY);
			for (unsigned int i = 0; i < mesh->GetNumVertices(); i++) {
				minX = min(minX, vertexPos->x);
				minZ = min(minZ, vertexPos->z);
				maxX = max(maxX, vertexPos->x);
				maxZ = max(maxZ, vertexPos->z);
				//次の頂点へ。
				char* p = (char*)vertexPos;
				p += stride;
				vertexPos = (D3DXVECTOR3*)p;
			}
			vb->Unlock();
			vb->Release();
		}
		m_terrainSize.x = minX;
		m_terrainSize.y = maxX;
		m_terrainSize.z = minZ;
		m_terrainSize.w = maxZ;
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
				//地形の幅と高さを計算。
				CalcWidthAndHeight();

				
				const std::vector<CSkinModelMaterial*>& materials = m_skinModelData.GetBody()->GetSkinModelMaterials();
				//地形用のマテリアルを構築する。
				for (auto& mat : materials) {
					mat->Build(CSkinModelMaterial::enTypeTerrain);
					//スプラットマップを設定する。
					mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_SplatMap, m_splatMap);
					mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_TerrainTex0, m_textures[0]);
					mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_TerrainTex1, m_textures[1]);
					mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_TerrainTex2, m_textures[2]);
					mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_TerrainTex3, m_textures[3]);
					mat->SetFVector(CSkinModelMaterial::enFVectorShaderHandle_TerrainRect, m_terrainSize);
				}

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
