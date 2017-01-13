/*!
 *@brief	タイトルシーン。
 */
#pragma once

class TitleScene : public IGameObject{
public:
	TitleScene();
	~TitleScene();
	bool Start();
	void Update();
	void PostRender(CRenderContext& renderContext);
private:
	CSprite sprite;		//スプライト。
	CTexture texture;	//テクスチャ。
};