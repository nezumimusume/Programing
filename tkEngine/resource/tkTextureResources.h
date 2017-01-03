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
		 */
		CTexture* Load( const char* filePath );
		/*!
		*@brief	解放。
		*/
		void Release();
	private:
		friend class CEngine;
		std::map<int, CTexture*>	textureMap;
	};
}
