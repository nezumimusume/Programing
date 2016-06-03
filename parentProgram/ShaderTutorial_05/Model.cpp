#include "stdafx.h"
#include "Model.h"

void Model::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//Xファイルをロード。
	LPD3DXBUFFER pD3DXMtrlBuffer;
	//Xファイルのロード。
	D3DXLoadMeshFromX("tiger.x", D3DXMESH_SYSTEMMEM,
		pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &numMaterial,
		&mesh);
	// マテリアルバッファを取得。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//テクスチャをロード。
	textures = new LPDIRECT3DTEXTURE9[numMaterial];
	for (DWORD i = 0; i < numMaterial; i++)
	{
		textures[i] = NULL;
		//テクスチャを作成する。
		D3DXCreateTextureFromFileA(pd3dDevice,
			d3dxMaterials[i].pTextureFilename,
			&textures[i]);
	}
	// マテリアルバッファを解放。
	pD3DXMtrlBuffer->Release();

	//シェーダーをコンパイル。
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//シェーダーをコンパイル。
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,
		"basic.fx",
		NULL,
		NULL,
		D3DXSHADER_SKIPVALIDATION,
		NULL,
		&effect,
		&compileErrorBuffer
		);
	if (hr != S_OK) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}
void Model::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX worldMatrix,
	D3DXMATRIX rotationMatrix,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	effect->SetTechnique("SkinModel");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);

	//定数レジスタに設定するカラー。
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//ワールド行列の転送。
	effect->SetMatrix("g_worldMatrix", &worldMatrix);
	//ビュー行列の転送。
	effect->SetMatrix("g_viewMatrix", &viewMatrix);			//ビュー行列を転送。

	effect->SetMatrix("g_projectionMatrix", &projMatrix);	//プロジェクション行列の転送。

	effect->SetMatrix("g_rotationMatrix", &rotationMatrix);		//回転行列を転送。
															//ライトの向きを転送。
	effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//ライトのカラーを転送。
	effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//環境光を設定。
	effect->SetVector("g_ambientLight", &ambientLight);

	effect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	for (DWORD i = 0; i < numMaterial; i++)
	{
		effect->SetTexture("g_diffuseTexture", textures[i]);
		// Draw the mesh subset
		mesh->DrawSubset(i);
	}

	effect->EndPass();
	effect->End();
}