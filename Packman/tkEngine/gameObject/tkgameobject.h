/*!
 *@brief	ゲームオブジェクトの基底クラス。
 */

#ifndef _CGAMEOBJECT_H_
#define _CGAMEOBJECT_H_


namespace tkEngine{
	class CGameObjectManager;
	/*!
	 *@brief	ゲームオブジェクト。
	 */
	class IGameObject : Noncopyable{
	public:
		IGameObject()
		{
		}
		/*!
		 *@brief	デストラクタ
		 */
		virtual ~IGameObject()
		{
		}
	public:
		/*!
		 *@brief	更新
		 */
		virtual void Update() = 0;
		/*!
		 *@brief	描画
		 */
		virtual void Render() = 0;
		/*!
		 *@brief	削除されるときに呼ばれる。
		 *@details	CGameManager::DeleteGameObjectを呼んだときに実行されます。
		 * デストラクタより前に実行されます。
		 */
		virtual void OnDestroy(){} 
	public:
		/*!
		 *@brief	インスタンスが生成された直後に呼ばれる関数。
		 *@details	コンストラクタが呼ばれた後で即呼ばれます。
		 */
		virtual void Awake(){}
		/*!
		 *@brief	Update関数が実行される前に呼ばれる更新関数。
		 */
		virtual void PreUpdate() {}
		/*!
		 *@brief	Update関数が実行された後で呼ばれる更新関数。
		 */
		virtual void PostUpdate() {} 
		/*!
		 *@brief	Render関数が実行される前に呼ばれる描画処理。
		 */
		virtual void PreRender() {}
		/*!
		 *@brief	Render関数が実行された後で呼ばれる描画処理
		 */
		virtual void PostRender() {}

		friend class CGameObjectManager;
		
	};
}
#endif // _CGAMEOBJECT_H_