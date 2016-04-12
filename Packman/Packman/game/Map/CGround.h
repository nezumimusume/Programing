/*!
 * @brief	地面。
 */

#ifndef _CGROUND_H_
#define _CGROUND_H_

#include "tkEngine/shape/tkBoxShape.h"

class CGround : public tkEngine::IGameObject{
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
	 *@brief	地面作成。
	 */
	void Create( float xz_size );
private:
	tkEngine::CBoxShape		m_box;	
};
#endif 