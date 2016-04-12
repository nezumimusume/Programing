/*!
 * @brief	ゲームマネージャ。
 */

#ifndef _CGAMEMANAGER_H_
#define _CGAMEMANAGER_H_

#include "Packman/game/CCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "Packman/game/map/CMapBuilder.h"
#include "Packman/game/Player/CPlayer.h"

/*!
 *@brief	ゲームマネージャー。
 */
class CGameManager : public tkEngine::IGameObject{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	CGameManager();
	/*!
	 *@brief	デストラクタ。
	 */
	~CGameManager();
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
	 *@brief	ゲームマネージャーのインスタンスを取得。
	 */
	static CGameManager& GetInstance()
	{
		return *m_instance;
	}
	/*!
	 *@brief	ゲームカメラのインスタンスを取得。
	 */
	CGameCamera&  GetGameCamera()
	{
		return m_camera;
	}
	/*!
	 *@brief	地面のライトを取得。
	 */
	CLight& GetGroundLight()
	{
		return m_groundLight;
	}
	/*!
	 *@brief	壁のライトを取得。
	 */
	CLight& GetWallLight()
	{
		return m_wallLight;
	}
	/*!
	 *@brief	食べ物のライトを取得。
	 */
	CLight& GetFoodLight()
	{
		return m_foodLight;
	}
	/*!
	*@brief	プレイヤを取得。
	*/
	CPlayer& GetPlayer()
	{
		return m_player;
	}
private:
	CGameCamera		m_camera;			//カメラ。
	CLight			m_groundLight;		//地面のライト
	CLight			m_wallLight;		//壁のライト。
	CLight			m_foodLight;		//食べ物のライト。
	static CGameManager*	m_instance;	//唯一のインスタンス。
	CMapBuilder		m_mapBuilder;		//マップ構築処理。
	CPlayer			m_player;			//プレイヤ
};

static inline CPlayer& Player()
{
	return CGameManager::GetInstance().GetPlayer();
}

#endif //_CGAMEMANAGER_H_