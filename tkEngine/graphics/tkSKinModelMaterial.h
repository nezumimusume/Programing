/*!
 * @brief	マテリアル。
 */

#ifndef _TKMATERIAL_H_
#define _TKMATERIAL_H_

#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	class CEffect;
	/*!
	 *@brief	マテリアル。
	 */
	class CSkinModelMaterial{
	private:
		template<class T>
		struct SShaderParam {
			std::string paramName;		//マテリアルパラメータの名前。シェーダーで記述されている変数名。
			T param;					//パラメータ。
		};
		typedef SShaderParam<CTexture*>	SShaderTextureParam;
		typedef SShaderParam<CMatrix>	SShaderMatrixParam;
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSkinModelMaterial();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSkinModelMaterial();
		/*!
		 *@brief	テクスチャを設定。
		 *@param[in]	paramName		パラメータ名。
		 *@param[in]	texture			テクスチャ。
		 */
		void SetTexture( const char* paramName, CTexture* texture )
		{
			if (texture) {
				int hash = CUtil::MakeHash(paramName);
				textureMap.insert(std::pair<int, SShaderTextureParam>(hash, { paramName, texture }));
				isDirty = true;
			}
		}
		/*!
		 *@brief	マテリアル名を取得。
		 */
		const char* GetMaterialName() const
		{
			return name.c_str();
		}
		/*!
		*@brief	マテリアル名を設定。
		*/
		void SetMaterialName(const char* matName)
		{
			name = matName;
		}
		/*!
		*@brief	マテリアル情報をGPUに転送。
		*@param[in]		effect		エフェクト。
		*/
		void SendMaterialParamToGPUImmidiate(ID3DXEffect* effect);
	private:
		ID3DXEffect*				effect = NULL;		//!<エフェクト。
		std::string					name;				//!<マテリアル名。
		std::map<int, SShaderTextureParam>	textureMap;	//!<テクスチャのマップ。
		std::vector<D3DXHANDLE>		shaderHandles;		//!<シェーダーハンドルのリスト。
		bool						isDirty = false;	//!<ダーティフラグ。
	};
}

#endif //_TKMATERIAL_H_