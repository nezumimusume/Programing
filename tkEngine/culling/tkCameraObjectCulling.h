/*!
 *@brief	カメラを使用したオブジェクトカリング処理。
 */

#pragma once

#include "tkEngine/culling/tkObjectCulling.h"

namespace tkEngine{
	/*!
	 *@brief	カメラを使用したオブジェクトカリング処理。
	 *@details
	 * オブジェクトを内包するAABBを構成する8頂点がカメラに映らない場合にカリングされます。
	 */
	class CCameraObjectCulling : public IObjectCulling{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CCameraObjectCulling();
		/*!
		 *@brief	デストラクタ。
		 */
		~CCameraObjectCulling();
		/*!
		 *@brief	初期化。
		 */
		void Init( const CCamera& camera )
		{
			m_camera = &camera;
		}
		/*!
		 *@brief	カリングアルゴリズムの実行。
		 */
		void Execute() override;
	private:
		const CCamera*	m_camera = nullptr;
	};
}