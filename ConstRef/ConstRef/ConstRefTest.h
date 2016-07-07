#pragma once

//const参照渡しのテスト。
class ConstRefCallTest : public IGameObject {
public:
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render(CRenderContext& renderContext)
	{

	}

};
