/*!
 * @brief	テクスチャ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkTexture.h"

namespace tkEngine {
	/*!
	 * @brief	テクスチャをロード。
	 */
	bool CTexture::Load(const char* fileName, bool isCubeMap)
	{
		if (fileName == nullptr) {
			return false;
		}
		Release();
		LPDIRECT3DDEVICE9 device = Engine().GetD3DDevice();
		if (!isCubeMap) {
			if (FAILED(D3DXCreateTextureFromFile(
				device,
				fileName,
				&m_tex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		else {
			if (FAILED(D3DXCreateCubeTextureFromFile(
				device,
				fileName,
				&m_cubeTex))) {
				TK_LOG("FailedTextureLoad\n");
				return false;
			}
		}
		ComputeTexSize();
		return true;
	}
}