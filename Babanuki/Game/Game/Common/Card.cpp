/*!
 * @brief	カード。
 */

#include "stdafx.h"
#include "Common/Card.h"
#include "Scene/GameScene.h"

namespace {
	const CVector2 cardSize = { 96.0f, 144.0f };
}
Card::Card()
{
}
Card::~Card()
{
}

void Card::Init(EnCardType type, int no)
{
	this->type = type;
	this->no = no;
}
bool Card::Start()
{
	switch(initStep){
	case enInitStep_StartModelLoad:{
		char textureFilePath[256];
		static char cardPrefix[] = {
			'h', 'd', 's', 'c'
		};
		
		//カードの図柄のテクスチャをロード。
		if (type != enCardType_Joker) {
			sprintf(textureFilePath, "Assets/modelData/%c%02d.png", cardPrefix[type], no);
		}
		else {
			strcpy(textureFilePath, "Assets/modelData/x01.png");
		}
		texture = TextureResources().Load(textureFilePath);
		modelData.LoadModelDataAsync("Assets/modelData/card.x", nullptr);
		initStep = enInitStep_WaitModelLoad;
	}break;
	case enInitStep_WaitModelLoad:
		if (modelData.IsLoadEnd()) {
			CSkinModelMaterial* mat = modelData.FindMaterial("c01.png");
			//画像を差し替え。
			mat->SetTexture("g_diffuseTexture", texture);
			model.Init(&modelData);
			model.SetLight(&g_gameScene->GetLight());
			SetActiveFlag(false);
			return true;
		}
		break;
	}
	return false;
}
void Card::Update()
{
	model.Update(position, rotation, CVector3::One);
}
void Card::Render(CRenderContext& renderContext)
{
	model.Draw(renderContext, g_gameScene->GetCamera().GetViewMatrix(), g_gameScene->GetCamera().GetProjectionMatrix());
}