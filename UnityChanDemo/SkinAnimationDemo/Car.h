/*!
 *@brief	車クラス。
 */
#pragma once

class Car : public IGameObject{
public:
	Car();
	~Car();
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
private:
	CSkinModelData			skinModelData;
	CSkinModel				skinModel;			//スキンモデル。
	CLight					light;				//ライト。
	CTexture				normalMap;			//法線マップ。
	CVector3				position;			//座標。
	CQuaternion				rotation;			//回転。
};