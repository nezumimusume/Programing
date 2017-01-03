/*!
 *@brief	テクスチャのリソースクラス。
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	リソースクラス。
	 */
	class CTextureResources {
	private:
		CTextureResources();
		~CTextureResources();
	public:
		/*!
		 *@brief	テクスチャをロード。
		 *@param[in]	filePath		ファイルパス。
		 *@param[in]	isCubeMap		キューブマップをロードする場合はtrueに設定してください。
		 */
		CTexture* Load( const char* filePath, bool isCubeMap = false );
		/*!
		*@brief	解放。
		*/
		void Release();
	private:
		friend class CEngine;
		std::map<int, CTexture*>	textureMap;
	};
}
