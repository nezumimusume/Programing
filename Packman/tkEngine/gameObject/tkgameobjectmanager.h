/*!
 *@brief	CGameObjectのマネージャー。
 */

#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	/*!
	 *@brief	CGameObjectのマネージャクラス。
	 */
	class CGameManager : Noncopyable{
	private:
		CGameManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameManager()
		{
		}
	public:
		/*!
		 *@brief	インスタンスの取得。
		 */
		static CGameManager& GetInstance()
		{
			static CGameManager instance;
			return instance;
		}
		/*!
		 *@brief	初期化。
		 *@param[in]	gameObjectPrioMax	ゲームオブジェクトの優先度の最大数。
		 */
		void Init( u32 gameObjectPrioMax )
		{
			m_gameObjectPriorityMax = gameObjectPrioMax;
		}
		/*!
		 *@brief	ゲームオブジェクトのnew
		 *@param	prio	実行優先順位。
		 */
		template<class T>
		T* NewGameObject( u32 prio )
		{
			T* newObject = new T();
			newObject->Awake();
		}
		/*!
		 *@brief	ゲームオブジェクトの削除。
		 */
		void DeleteGameObject( IGameObject* gameObject )
		{
			gameObject->OnDestroy();
		}
	private:
		std::list<IGameObject*>	m_gameObjectList;	//!<ゲームオブジェクトのリスト。
		std::list<IGameObject*>	m_deleteObjectList;	//!<削除するオブジェクトのリスト。
		u32 m_gameObjectPriorityMax;	//!<ゲームオブジェクトの優先度の最大数。
	};
}
#endif // _CGAMEOBJECTMANAGER_H_
 