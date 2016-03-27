/*!
 *@brief	CGameObjectのマネージャ
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/gameObject/tkgameobjectmanager.h"
#include "tkEngine/graphics/tkRenderContext.h"
#include <future>

namespace tkEngine{
	void CGameObjectManager::Execute(CRenderContext* renderContext, u32 numRenderContext, const SRenderContextMap* renderContextMap)
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreUpdateWrapper();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostUpdateWrapper();
			}
		}
		
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreRenderWrapper(renderContext[0]);
			}
		}
		if (numRenderContext == 1) {
			//シングルスレッド描画。
			for (GameObjectList objList : m_gameObjectListArray) {
				for (IGameObject* obj : objList) {
					obj->RenderWrapper(renderContext[0]);
				}
			}
		}
		else {
			//マルチスレッド描画。
			TK_ASSERT(0, "not implement!!");
			
		}
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostRenderWrapper(renderContext[numRenderContext-1]);
			}
		}
		ExecuteDeleteGameObjects();
	}
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		for(GameObjectList& goList : m_deleteObjectArray){
			for(IGameObject* go : goList){
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find( goExecList.begin(),goExecList.end(),go );
				goExecList.erase(it);
			}
			goList.clear();
		}
	}
	void CGameObjectManager::Init( u32 gameObjectPrioMax )
	{
		TK_ASSERT( gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "ゲームオブジェクトの優先度の最大数が大きすぎます。");
		m_gameObjectPriorityMax = gameObjectPrioMax;
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray.resize(gameObjectPrioMax);
	}
}