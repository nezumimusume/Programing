/*!
 *@brief	CGameObjectのマネージャー。
 */

#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	struct SRenderContextMap;
	/*!
	 *@brief	CGameObjectのマネージャ
	 */
	class CGameObjectManager : Noncopyable{
	private:
		CGameObjectManager() :
			m_gameObjectPriorityMax(0)
		{
		}
		~CGameObjectManager()
		{
		}
	public:
		/*!
		 *@brief	インスタンスの取得。
		 */
		static CGameObjectManager& GetInstance()
		{
			static CGameObjectManager instance;
			return instance;
		}
		/*!
		*@brief	実行。
		*@param[in]	renderContext		レンダリングコンテキスト。
		*@param[in]	numRenderContext	レンダリングコンテキストの数。
		*@param[in]	renderContextMap	レンダリングコンテキストのマップ。
		*/
		void Execute( CRenderContext* renderContext, u32 numRenderContext, const SRenderContextMap* renderContextMap );
		/*!
		 *@brief	初期化。
		 *@param[in]	gameObjectPrioMax	ゲームオブジェクトの優先度の最大値。(255まで)
		 */
		void Init( u32 gameObjectPrioMax );
		/*!
		 *@brief	ゲームオブジェクトのnew
		 *@param	prio	実行優先順位。
		 */
		template<class T>
		T* NewGameObject(GameObjectPrio prio )
		{
			TK_ASSERT( prio <= m_gameObjectPriorityMax, "ゲームオブジェクトの優先度の最大数が大きすぎます。");
			T* newObject = new T();
			newObject->Awake();
			m_gameObjectListArray.at(prio).push_back(newObject);
			return newObject;
		}
		/*!
		 *@brief	ゲームオブジェクトの削除。
		 */
		void DeleteGameObject( IGameObject* gameObject )
		{
			gameObject->OnDestroy();
			m_deleteObjectArray.at(gameObject->GetPriority()).push_back(gameObject);
		}
	private:
		/*!
		 *@brief	ゲームオブジェクトの削除を実行。
		 */
		void ExecuteDeleteGameObjects();
	private:
		typedef std::list<IGameObject*>	GameObjectList;
		std::vector<GameObjectList>	m_gameObjectListArray;	//!<ゲームオブジェクトの優先度付きリスト。
		std::vector<GameObjectList>	m_deleteObjectArray;	//!<削除するオブジェクトのリスト。
		GameObjectPrio				m_gameObjectPriorityMax;		//!<ゲームオブジェクトの優先度の最大数。
		static const u8 			GAME_OBJECT_PRIO_MAX = 255;		//!<ゲームオブジェクトの優先度の最大値。
	};
}
#endif // _CGAMEOBJECTMANAGER_H_
 