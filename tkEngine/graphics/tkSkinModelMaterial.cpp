/*!
 * @brief	マテリアル
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CSkinModelMaterial::CSkinModelMaterial()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CSkinModelMaterial::~CSkinModelMaterial()
	{
	}
	/*!
	*@brief	マテリアル情報をGPUに転送。
	*@param[in]		effect		エフェクト。
	*/
	void CSkinModelMaterial::SendMaterialParamToGPUImmidiate(ID3DXEffect* effect)
	{
		if (this->effect != effect) {
			//エフェクトが変わった。
			this->effect = effect;
			isDirty = true;
		}
		
		if (isDirty) {
			//なにか変更が発生しているので、シェーダーハンドルのリストを更新。
			shaderHandles.clear();
			
			for (auto matParam : textureMap) {
				D3DXHANDLE handle = effect->GetParameterByName(NULL, matParam.second.paramName.c_str());
				shaderHandles.push_back(handle);
			}
			isDirty = false;
		}
		//マテリアルパラメータを転送。
		int i = 0;
		for (auto& p : textureMap) {
			effect->SetTexture(shaderHandles[i], p.second.param->GetTextureDX());
			i++;
		}
	}
}