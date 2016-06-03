#include "stdafx.h"
#include "Tiger.h"

//コンストラクタ
Tiger::Tiger()
{
	//初期化。
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRotation);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	parent = NULL;
	localPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	localRotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}
//デストラクタ
Tiger::~Tiger()
{
	Release();
}

//初期化。
void Tiger::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice);
}
//親を設定。
void Tiger::SetParent(Tiger* parent)
{
	//親が設定されたので、ワールド座標を求めるために。一旦Updateを呼び出す。
	Update();

	this->parent = parent;
	//親が設定されたので、ローカル座標を親のローカル座標に変換する。
	D3DXMATRIX mParentWorldInv = parent->GetWorldMatrix();
	D3DXMatrixInverse(&mParentWorldInv, NULL, &mParentWorldInv);
	D3DXVECTOR4 pos;
	D3DXVec3Transform(&pos, &position, &mParentWorldInv);
	localPosition.x = pos.x;
	localPosition.y = pos.y;
	localPosition.z = pos.z;

	//回転クォータニオンをローカル回転クォータニオンに変換する。
	D3DXQUATERNION qParentRotInv = parent->GetRotation();
	D3DXQuaternionInverse(&qParentRotInv, &qParentRotInv);
	localRotation = rotation * qParentRotInv;
}
//更新。
void Tiger::Update()
{
	if (parent) {
		//親がいる。
		D3DXMATRIX mParentWorld = parent->GetWorldMatrix();
		D3DXQUATERNION qParentRot = parent->GetRotation();
		//親のワールド行列を乗算して、ローカル座標をワールド座標に変換する。
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		
		rotation = localRotation * qParentRot;
	}
	else {
		position = localPosition;
		rotation = localRotation;
	}

	//ワールド行列を求める。
	D3DXVECTOR4 pos;
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&mRotation, &rotation);
	mWorld = mRotation * mWorld;
}
//描画。
void Tiger::Render( 
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix, 
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
)
{
	model.Render(pd3dDevice, mWorld, mRotation, viewMatrix, projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight);

}
//開放。
void Tiger::Release()
{}