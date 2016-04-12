/*!
 * @brief	プレイヤー
 */

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "tkEngine/shape/tkSphereShape.h"

class CPlayer : public tkEngine::IGameObject{
public:
	CPlayer(){}
	~CPlayer(){}
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
	*@brief	移動処理。
	*/
	void Move();
private:
	tkEngine::CSphereShape	m_sphere;
	CMatrix					m_wvpMatrix;			//<ワールドビュープロジェクション行列。
	tkEngine::CIDMapModel	m_idMapModel;
	CVector3				m_position;
};

#endif 