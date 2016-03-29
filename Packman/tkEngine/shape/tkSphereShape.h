/*!
 *@brief	球
 */

#ifndef _TKSPHERESHAPE_H_
#define _TKSPHERESHAPE_H_

#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/shape/tkShapeBase.h"

namespace tkEngine{
	/*!
	 *@brief	球。
	 */
	class CSphereShape : public CShapeBase{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CSphereShape();
		/*!
		 *@brief	デストラクタ
		 */
		~CSphereShape();
		/*!
		 *@brief	カラースフィアを作成。
		 *@param[in]	radius		半径。
		 *@param[in]	grid		グリッド。
		 *@param[in]	color		カラー。
		 *@param[in]	hasNormal	法線を保持している？
		 */
		void Create(f32 radius, u32 grid, u32 color, bool hasNormal );
	private:
		/*!
		*@brief	インデックスバッファの頂点を作成。
		*@param[out]	indexBuffer		インデックスバッファ。
		*@param[in]		grid			グリッド。
		*/
		void CreateIndexBuffer(std::vector<u32>& indexBuffer, u32 grid);
		/*!
		*@brief	頂点バッファの頂点を作成。
		*@param[out]	vertexBuffer	頂点バッファ。
		*@param[in]		radius			半径。
		*@param[in]		grid			グリッド。
		*@param[in]		color			カラー
		*/
		template<class TVertex>
		void CreateVertexPosition(std::vector<TVertex>& vertexBuffer, f32 radius, u32 grid, u32 color);
	};
}
#endif // _TKSPHERESHAPE_H_
