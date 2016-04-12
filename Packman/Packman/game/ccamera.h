/*!
 * @brief	カメラ。
 */

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "tkEngine/graphics/tkCamera.h"

/*!
 *@brief	カメラクラス。
 */
class CGameCamera : public tkEngine::IGameObject{ 
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	CGameCamera();
	/*!
	 *@brief	デストラクタ。
	 */
	~CGameCamera();
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
	 *@brief	ビュープロジェクション行列を取得。
	 */
	const CMatrix& GetViewProjectionMatrix()
	{
		return m_camera.GetViewProjectionMatrix();
	}
private:
	tkEngine::CCamera	m_camera;	//!<カメラ。
	CVector3			m_playerDist;
};
#endif // _CCAMERA_H_