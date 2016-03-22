/*!
 *@brief	インデックスバッファ
 */

#ifndef _TKINDEXBUFFER_H_
#define _TKINDEXBUFFER_H_

namespace tkEngine{
	class CIndexBuffer{
	public:
		CIndexBuffer();
		~CIndexBuffer();
		/*!
		 *@brief	インデックスバッファの作成。
		 *@param[in]	size			インデックスバッファのサイズ。
		 *@param[in]	format			インデックスバッファのフォーマット。
		 *@param[in]	pSrcIndexBuffer	ソースインデックスバッファ。作成されたインデックスバッファにコピーされます。NULLを指定可能。
		 */
		void Create( u32 size, D3DFORMAT format, const void* pSrcIndexBuffer );
		/*!
		 *@brief	インデックスバッファの解放。
		 */
		void Release();
	private:
		LPDIRECT3DINDEXBUFFER9	m_pIB;	//!<インデックスバッファ。
	};
}

#endif //_TKINDEXBUFFER_H_