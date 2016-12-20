/*!
 *@brief	カメラのコリジョンソルバー
 */

#pragma once

#include "tkEngine/Physics/tkSphereCollider.h"

namespace tkEngine{
	/*!
	 *@brief	カメラのコリジョンソルバー。
	 *@details
	 * 一般的なゲームのカメラのコリジョンソルバーを提供します。
	 */
	class CCameraCollisionSolver{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CCameraCollisionSolver();
		/*!
		 *@brief	デストラクタ。
		 */
		~CCameraCollisionSolver();
		/*!
		 *@brief	初期化。
		 *@param[in]	radius		カメラのバウンディングスフィアの半径。
		 */
		void Init(float radius);
		/*!
		 *@brief	コリジョンソルバーの実行。
		 
		 *@return	衝突する場合trueが返ってくる。
		 */
		bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
	private:
		CSphereCollider		m_collider;		 //コライダー。
		float				m_radius = 0.0f; //半径。
	};
}