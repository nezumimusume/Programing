/*!
 * @brief	頂点バッファ
 */

#ifndef _TKRENDERBUFFER_H_
#define _TKRENDERBUFFER_H_

namespace tkEngine{
	/*!
	 * @brief	頂点バッファ
	 */
	class CVertexBuffer{
	public:
		CVertexBuffer();
		~CVertexBuffer();
		/*!
		 *@brief	頂点バッファの作成。
		 *@param[in]	size	頂点バッファのサイズ。
		 *@param[in]	fvf		頂点バッファのフォーマット。D3DFVFの組み合わせ。
		 */
		void Create( u32 size, u32 format );
		/*!
		 * @brief	頂点バッファの開放。
		 */
		void Release();
	private:
		LPDIRECT3DVERTEXBUFFER9	m_pVB;	//!<頂点バッファ。
	};
}
#endif // #define _TKRENDERBUFFER_H_