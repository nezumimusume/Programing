#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"
#include "tkEngine/nature/tkTerrain.h"
class Ground : public IGameObject {
	enum InitStep {
		InitStep_Load,
		InitStep_Wait,
	};
	InitStep				initStep = InitStep_Load;
	CTerrain				terrain;			//地面。
	CMeshCollider			meshCollider;		//メッシュコライダー。
	CRigidBody				rigidBody;			//剛体。
public:
	Ground();
	
	~Ground();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
	void OnDestroy() override;
private:
};
extern Ground* g_ground;