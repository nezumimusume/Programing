/*!
 *@brief	ShaderResourceView
 */

#pragma once

namespace tkEngine{
	class CStructuredBuffer;
	class CTextureData;
	/*!
	 *@brief	ShaderResourceView
	 *@details
	 * テクスチャやストラクチャバッファなど、シェーダーで使用するリソースで使用するビュー。
	 */
	class CShaderResourceView : Noncopyable{
	public:
		CShaderResourceView();
		~CShaderResourceView();
		/*!
		 *@brief	StructuredBuffer用のSRVを作成。
		 *@param[in]	structuredBuffer	structuredBuffer
		 */
		bool Create(CStructuredBuffer& structuredBuffer);
		/*!
		*@brief	テクスチャ用のSRVを作成。
		*@param[in]	texture		テクスチャ。
		*/
		bool Create(ID3D11Texture2D* texture);
		/*!
		 *@brief	明示的な開放。
		 *@details
		 * 明示的に開放する必要があるときに使用してください。
		 */
		void Release();
		/*!
		*@brief	ID3D11ShaderResourceViewを取得。
		*/
		ID3D11ShaderResourceView*& GetBody()
		{
			return m_srv;
		}
		/*!
		*@brief	有効なビューかどうか判定。
		*/
		bool IsValid() const
		{
			return m_isValid;
		}
	private:
		ID3D11ShaderResourceView*		m_srv = nullptr;
		bool							m_isValid = false;	//!<有効なデータ？
	};
}