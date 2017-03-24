#include "stdafx.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "Map/Ground.h"
#include "Player/Player.h"
#include "tkEngine/Physics/tkCollisionAttr.h"
#include "Scene/GameScene.h"
#include "tkEngine/nature/tkSky.h"
#include "GameCamera.h"

Ground* g_ground = NULL;
LPD3DXMESH testMesh;

Ground::Ground()
{

}
Ground::~Ground()
{
}
void Ground::OnDestroy()
{
	DeleteGO(&terrain);
}
bool Ground::Start()
{
	switch (initStep) {
	case InitStep_Load: {
		g_ground = this;
		AddGO(GetPriority(), &terrain);
		const char* textures[] = {
			"Assets/modelData/Grass.tga",
			"Assets/modelData/snow.png",
			"Assets/modelData/Sand_Albedo.tga",
			NULL
		};
		terrain.Init("Assets/modelData/ground.X", "Assets/modelData/groundSplatmap.png", textures, g_camera->GetCamera(), gameScene->GetDefaultLight());
		initStep = InitStep_Wait;
	}break;
	case InitStep_Wait: {
		if (terrain.IsStart()) {
			//’n–Ê‚ÌStartŠÖ”‚ªŠ®—¹‚µ‚½B
			return true;
		}
	}break;
	}
	
	return false;
}

void Ground::Update() 
{
}
void Ground::Render(CRenderContext& renderContext) 
{
}
