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
		void Create();
	};
}
#endif // #define _TKRENDERBUFFER_H_