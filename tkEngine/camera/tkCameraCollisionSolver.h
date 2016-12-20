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
		 *@param[in]	camera		カメラ。
		 */
		void Execute( CCamera& camera );
	private:
		CSphereCollider		m_collider;		 //コライダー。
		float				m_radius = 0.0f; //半径。
	};
}