/*!
 * @brief	エフェクトマネージャ
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkEffectManager.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CEffectManager::CEffectManager()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CEffectManager::~CEffectManager()
	{
		Release();
	}
	/*!
	 *@brief	エフェクトのロード。
	 *@details
	 * 読み込み済みのエフェクトの場合はロードは行われず、</br>
	 * 既存のエフェクトが返ってきます。
	 *@param[in]	filePath	ロードするエフェクトのファイルパス。
	 *@return	ロードしたエフェクトファイル。
	 */
	CEffect* CEffectManager::LoadEffect( const c8* filePath )
	{
		LPD3DXEFFECT effect;
		HRESULT hr = D3DXCreateEffectFromFile(
			CEngine::Instance().GetD3DDevice(),
			filePath,
			NULL,
			NULL,
#ifdef _DEBUG
			D3DXSHADER_DEBUG,
#else
			D3DXSHADER_SKIPVALIDATION,
#endif
			NULL,
			&effect,
			NULL
			);
		TK_ASSERT(SUCCEEDED(hr), "Failed D3DXCreateEffectFromFile");
		CEffect* pEffect = nullptr;
		u32 hash = CUtil::MakeHash(filePath);
		
		auto it = m_effectDictinary.find(hash);
		if (it == m_effectDictinary.end()) {
			//新規。
			std::pair<u32, CEffect*> node(hash, pEffect);
			m_effectDictinary.insert(node);
			pEffect = new CEffect(effect);
		}
		else {
			//登録済み。
			pEffect = it->second;
		}
		return pEffect;
	}
	/*!
	 * @brief	リリース。
	 */
	void CEffectManager::Release()
	{
		for (auto p : m_effectDictinary) {
			delete p.second;
		}
	}
}