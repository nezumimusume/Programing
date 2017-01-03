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
	CTexture* CTextureResources::Load( const char* filePath, bool isCubeMap )
	{
		int hash = CUtil::MakeHash(filePath);
		auto it = textureMap.find(hash);
		CTexture* tex = nullptr;
		if (it == textureMap.end()) {
			//V‹K
			tex = new CTexture;
			if (tex->Load(filePath, isCubeMap) ){
				textureMap.insert(std::pair<int, CTexture*>(hash, tex));
			}
			else {
				delete tex;
				return nullptr;
			}

		}
		else {
			tex = it->second;
		}
		return tex;
	}
}