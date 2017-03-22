#include "stdafx.h"
#include "Map/MapChip.h"
#include "Player/Player.h"
#include "Scene/GameScene.h"

MapChip::MapChip() :
	rootBoneMatrix(NULL)
{
}


MapChip::~MapChip()
{
	for (int i = 0; i < numMapChip; i++) {
		PhysicsWorld().RemoveRigidBody(&rigidBody[i]);
	}
}
void MapChip::Init(const std::vector<SMapChipLocInfo*>& mapChipLocInfoList)
{
	//まずはスキンモデルをロード。
	this->mapChipLocInfoList = mapChipLocInfoList;
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.X", mapChipLocInfoList[0]->modelName);
	skinModelData.LoadModelDataAsync(modelPath, NULL, true, (int)mapChipLocInfoList.size());
}
bool MapChip::Start()
{
	if (skinModelData.IsLoadEnd()) {
		skinModel.Init(skinModelData.GetBody());
		skinModel.SetLight(&gameScene->GetDefaultLight());
		skinModel.SetShadowCasterFlag(true);
		skinModel.SetShadowReceiverFlag(true);
		char filePath[256];
		const std::vector<CSkinModelMaterial*> materials = skinModelData.GetBody()->GetSkinModelMaterials();
	
		int i = 0;
		for (CSkinModelMaterial* mat : materials) {
			char work[256];
			strcpy(work, mat->GetName());
			strtok(work, ".");
			sprintf(filePath, "Assets/modelData/%s_n.png", work);
			CTexture* tex = TextureResources().Load(filePath);
			if (tex) {
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_NormalMap, *tex);
				skinModel.SetHasNormalMap(true);
			}
			sprintf(filePath, "Assets/modelData/%s_s.png", work);
			tex = TextureResources().Load(filePath);
			if (tex) {
				mat->SetTexture(CSkinModelMaterial::enTextureShaderHandle_SpecularMap, *tex);
				skinModel.SetHasSpeculerMap(true);
			}

			i++;
		}

		//ワールド行列のバッファを作成。
		numMapChip = (int)mapChipLocInfoList.size();
		worldMatrixBuffer.reset(new CMatrix[numMapChip]);
		meshCollider.reset(new CMeshCollider[numMapChip]);
		rigidBody.reset(new CRigidBody[numMapChip]);
		i = 0;
		for (auto& mapChiplLocInfo : mapChipLocInfoList) {
			CMatrix mTrans;
			CVector3 pos = mapChiplLocInfo->pos;

			mTrans.MakeTranslation(pos);
			CMatrix mRot;
			mRot.MakeRotationFromQuaternion(mapChiplLocInfo->rotation);
			worldMatrixBuffer[i].Mul(mRot, mTrans);

			i++;
		}
		//行列を更新。
		skinModel.UpdateInstancingDrawData(worldMatrixBuffer.get());
		skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
		rootBoneMatrix = skinModelData.GetBody()->GetRootBoneWorldMatrix();
		i = 0;
		for (auto& mapChiplLocInfo : mapChipLocInfoList) {
			CMatrix mWorld;
			mWorld.Mul(*rootBoneMatrix, worldMatrixBuffer[i]);
			meshCollider[i].CreateFromSkinModel(&skinModel, &mWorld);
			RigidBodyInfo rbInfo;
			rbInfo.collider = &meshCollider[i];
			rbInfo.mass = 0.0f;
			rigidBody[i].Create(rbInfo);
			PhysicsWorld().AddRigidBody(&rigidBody[i]);
			i++;
		}
	
		return true;
	}
	return false;
}
void MapChip::Update()
{
	skinModel.EntryShadowMap();
}
void MapChip::Render(CRenderContext& renderContext)
{
	renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}