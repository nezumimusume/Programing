/*!
 * @brief	壁。
 */

#ifndef _CWALL_H_
#define _CWALL_H_

#include "tkEngine/graphics/prerender/tkIDMap.h"
#include "tkEngine/shape/tkBoxShape.h"

class CWall : public tkEngine::IGameObject{
public:
	/*!
	 *@brief	Updateが初めて呼ばれる直前に一度だけ呼ばれる処理。
	 */
	void Start() override final;
	/*!
	 *@brief	更新処理。60fpsなら16ミリ秒に一度。30fpsなら32ミリ秒に一度呼ばれる。
	 */
	void Update() override final;
	/*!
	 *@brief	描画処理。60fpsなら16ミリ秒に一度。30fpsなら32ミリ秒に一度呼ばれる。
	 */
	void Render(tkEngine::CRenderContext& renderContext) override final;
	/*!
	 *@brief	構築処理。
	 *@param[in]	size	箱のサイズ。
	 *@param[in]	pos		箱の座標。
	 */
	void Build( const CVector3& size, const CVector3& pos );
private:
	tkEngine::CBoxShape		m_box;			//!<箱の形状。
	tkEngine::CIDMapModel	m_idMapModel;	//!<IDMapへの書き込み用のモデル。
	tkEngine::CShadowModel	m_shadowModel;	//!<シャドウマップへの書き込み用のモデル。
	CMatrix					m_wvpMatrix;	//<ワールドビュープロジェクション行列。
};
#endif