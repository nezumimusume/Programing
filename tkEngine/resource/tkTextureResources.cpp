#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/resource/tkTextureResources.h"
#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	CTextureResources::CTextureResources()
	{
	}
	CTextureResources::~CTextureResources()
	{
		Release();
	}
	void CTextureResources::Release()
	{
		for (auto p : textureMap) {
			delete p.second;
		}
		textureMap.clear();
	}
	CTexture* CTextureResources::Load( const char* filePath )
	{
		int hash = CUtil::MakeHash(filePath);
		auto it = textureMap.find(hash);
		CTexture* tex = nullptr;
		if (it == textureMap.end()) {
			//V‹K
			LPDIRECT3DTEXTURE9 texDx;
			HRESULT hr = D3DXCreateTextureFromFileA(Engine().GetD3DDevice(), filePath, &texDx);
			if (FAILED(hr)) {
				if (FAILED(hr)) {
					return nullptr;
				}
			}
			tex = new CTexture;
			tex->SetTextureDX(texDx);
			textureMap.insert(std::pair<int, CTexture*>(hash, tex));
		}
		else {
			tex = it->second;
		}
		return tex;
	}
}