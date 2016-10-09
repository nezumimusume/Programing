#pragma once
#include "Physics/MeshCollider.h"
#include "Physics/RigidBody.h"

//マップチップの配置情報。
struct SMapChipLocInfo {
	const char* modelName;		//モデル。
	CVector3	pos;			//座標。
	CQuaternion	rotation;		//回転。
};
class MapChip : public IGameObject
{
public:
	MapChip();
	~MapChip();
	void Init(const std::vector<SMapChipLocInfo*>& mapChipLocInfoList);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//スキンモデル。
	CAnimation						animation;			//アニメーション。
	CLight							light;				//ライト。
	std::vector<CTexture>			specMapList;			//スペキュラマップ。
	std::vector<CTexture>			normalMapList;			//法線マップ。
	std::unique_ptr<CMatrix[]>		worldMatrixBuffer;	//ワールド行列のバッファ
	std::unique_ptr<MeshCollider[]>	meshCollider;		//メッシュコライダー。
	std::unique_ptr<RigidBody[]>	rigidBody;			//剛体。
	CMatrix*						rootBoneMatrix;		
};

