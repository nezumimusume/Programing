/*!
 * @brief	頂点バッファ
 */

#ifndef _TKRENDERBUFFER_H_
#define _TKRENDERBUFFER_H_

namespace tkEngine{
	enum EVertexFormat {
		eVertexFormat_xyz		= D3DFVF_XYZ,
		eVertexFormat_wyzrhw	= D3DFVF_XYZRHW,
		eVertexFormat_xyzw		= D3DFVF_XYZW,
		eVertexFormat_normal	= D3DFVF_NORMAL,
		eVertexFormat_diffuse	= D3DFVF_DIFFUSE,
		eVertexFormat_tex0		= D3DFVF_TEX0,
		eVertexFormat_tex1		= D3DFVF_TEX1,
		eVertexFormat_tex2		= D3DFVF_TEX2,
		eVertexFormat_tex3		= D3DFVF_TEX3,
		eVertexFormat_tex4		= D3DFVF_TEX4,
		eVertexFormat_tex5		= D3DFVF_TEX5,
		eVertexFormat_tex6		= D3DFVF_TEX6,
		eVertexFormat_tex7		= D3DFVF_TEX7,
		eVertexFormat_tex8		= D3DFVF_TEX8,
		eVertexFormat_invalid	= 0xffffffff,

	};
	/*!
	 * @brief	頂点バッファ
	 */
	class CVertexBuffer{
	public:
		CVertexBuffer();
		~CVertexBuffer();
		/*!
		 *@brief	頂点バッファの作成。
		 *@param[in]	numVertex		頂点数。
		 *@param[in]	stride			頂点ストライド。
		 *@param[in]	vertexFormat	頂点フォーマット。EVertexFormatの論理和を渡す。
		 *@param[in]	srcVertexBuffer	ソース頂点バッファ。作成された頂点バッファにコピーされます。NULLを指定可能。
		 */
		void Create( u32 numVertex, u32 stride, u32 vertexFormat, const void* pSrcVertexBuffer );
		/*!
		 * @brief	頂点バッファの開放。
		 */
		void Release();
		/*!
		* @brief	LPDIRECT3DVERTEXBUFFER9を取得。
		*/
		LPDIRECT3DVERTEXBUFFER9 GetBody()
		{
			return m_pVB;
		}
		/*!
		* @brief	頂点ストライドを取得。
		*/
		u32 GetStride() const
		{
			return m_stride;
		}
		/*!
		* @brief	頂点フォーマットを取得
		*/
		u32 GetVertexFormat() const
		{
			return m_vertexFormat;
		}
	private:
		LPDIRECT3DVERTEXBUFFER9	m_pVB;	//!<頂点バッファ。
		u32 m_stride;					//!<頂点ストライド。
		u32 m_numVertex;				//!<頂点数。
		u32 m_size;						//!<バッファサイズ。
		u32	m_vertexFormat;	//!<頂点フォーマット。
	};
}
#endif // #define _TKRENDERBUFFER_H_