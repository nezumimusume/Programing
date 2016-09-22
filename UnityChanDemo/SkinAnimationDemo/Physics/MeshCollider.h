#pragma once
#include "Physics/ICollider.h"

/*!
 * @brief	メッシュコライダー。
 */
class MeshCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	MeshCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~MeshCollider();
	/*!
	 * @brief	CSkinModelからメッシュコライダーを生成。
	 *@param[in]	model		スキンモデル。
	 */
	void CreateFromSkinModel( CSkinModel* model, const CMatrix* offsetMatrix );
	btCollisionShape* GetBody() override
	{
		return meshShape;
	}
private:
	typedef std::vector<CVector3>		VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ。
	std::vector<VertexBuffer*>		vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer*>		indexBufferArray;		//インデックスバッファの配列。
	btBvhTriangleMeshShape*			meshShape;				//メッシュ形状。
	btTriangleIndexVertexArray*		stridingMeshInterface;
};

