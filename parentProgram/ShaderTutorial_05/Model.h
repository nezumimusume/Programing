#pragma once

class Model {
public:
	Model() {
		mesh = NULL;
		textures = NULL;
		numMaterial = 0;
		effect = 0;
	}
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//描画。
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX worldMatrix,
		D3DXMATRIX rotationMatrix,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
private:
	LPD3DXMESH				mesh;			//メッシュ。
	LPDIRECT3DTEXTURE9*		textures;		//テクスチャ。
	DWORD					numMaterial;	//マテリアルの数。
	ID3DXEffect*			effect;			//エフェクト。
};