/*!
 * @brief	パックマンが食べるアイテム。
 */

#ifndef _CFOOD_H_
#define _CFOOD_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFood : public tkEngine::IGameObject{
public:
	/*!
	 *@brief	インスタンスを生成した直後に一度だけ呼ばれる処理。</br>
	 * Startより速いタイミングでコールされる。
	 */
	void Awake() override final;
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
	 *@brief	構築。
	 *必ず先にCreateShapeを一度コールしておく必要がある。
	 */
	void Build( const CVector3& pos );
	/*!
	 *@brief	形状の生成。
	 *@param[in]	radius		半径。
	 */
	static void CreateShape(float radius);
	/*!
	 *@brief	形状の解放。
	 */
	static void ReleaseShape();
private:
	static tkEngine::CSphereShape*	m_sphere;
	CMatrix							m_wvpMatrix;			//<ワールドビュープロジェクション行列。
	tkEngine::CIDMapModel			m_idMapModel;
	CVector3						m_position;
	CMatrix							m_worldMatrix;			//!<ワールド行列。
};

#endif // _CFOOD_H_