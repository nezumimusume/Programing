#pragma once

#include "Model.h"

//虎クラス。
class Tiger {
public:
	//コンストラクタ
	Tiger();
	//デストラクタ
	~Tiger();
	//初期化。
	void Init( LPDIRECT3DDEVICE9 pd3dDevice );
	//更新。
	void Update();
	//描画。
	void Tiger::Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
	);
	//開放。
	void Release();
	//親を設定。
	void SetParent(Tiger* parent);
	
	D3DXMATRIX GetWorldMatrix()
	{
		return mWorld;
	}
	D3DXMATRIX GetRotationMatrix()
	{
		return mRotation;
	}
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}
	D3DXQUATERNION GetRotation()
	{
		return rotation;
	}

	D3DXQUATERNION GetLocalRotation()
	{
		return localRotation;
	}
	void SetLocalRotation(D3DXQUATERNION rot)
	{
		localRotation = rot;
	}
	D3DXVECTOR3 GetLocalPosition()
	{
		return localPosition;
	}
	void SetLocalPosition(D3DXVECTOR3 pos)
	{
		localPosition = pos;
	}
private:
	Model					model;			//モデル。
	D3DXVECTOR3				position;		//ワールド座標。
	D3DXVECTOR3				localPosition;	//ローカル座標。
	D3DXQUATERNION			rotation;		//回転クォータニオン。
	D3DXQUATERNION			localRotation;	//ローカル回転クォータニオン。
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	Tiger*					parent;			//親。
};