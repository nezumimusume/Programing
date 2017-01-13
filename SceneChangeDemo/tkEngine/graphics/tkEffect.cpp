/*!
 * @brief	シェーダーエフェクト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CEffect::CEffect(LPD3DXEFFECT effect) :
		m_pEffect(effect)
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CEffect::~CEffect()
	{
		if (m_pEffect) {
			m_pEffect->Release();
			m_pEffect = nullptr;
		}
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (hFile != NULL) {
			CloseHandle(hFile);
		}
#endif
	}

	void CEffect::Update()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		m_isReloadTrigger = false;
		if (!hFile) {
			//ファイルを開く。
			hFile = CreateFile(
				filePath.c_str(), 
				GENERIC_READ, 
				FILE_SHARE_READ| FILE_SHARE_WRITE| FILE_SHARE_DELETE,
				NULL, 
				OPEN_EXISTING, 
				FILE_ATTRIBUTE_NORMAL, 
				NULL
			);
			GetFileTime(hFile, NULL, NULL, &fLastWriteTime);
		}
		else {
			//タイムスタンプを取得。
			if (hFile) {
				FILETIME t;
				GetFileTime(hFile, NULL, NULL, &t);
				if (CompareFileTime(&t, &fLastWriteTime)) {
					fLastWriteTime = t;
					//ファイルが更新されているので再読込み。
					LPD3DXBUFFER  compileErrorBuffer = nullptr;
					ID3DXEffect* newEffectFile;
					HRESULT hr = D3DXCreateEffectFromFile(
						CEngine::Instance().GetD3DDevice(),
						filePath.c_str(),
						NULL,
						NULL,
						D3DXSHADER_DEBUG,
						NULL,
						&newEffectFile,
						&compileErrorBuffer
						);
					if (FAILED(hr)) {
						//読み込み失敗。
						if (compileErrorBuffer) {
							TK_LOG(r_cast<char*>(compileErrorBuffer->GetBufferPointer()));
						}
					}
					else {
						//リロード成功。
						if (m_pEffect) {
							m_pEffect->Release();
						}
						m_pEffect = newEffectFile;
						//リロード発生。
						m_isReloadTrigger = true;
					}
				}
			}
		}
#endif
	}

}