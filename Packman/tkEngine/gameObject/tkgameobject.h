/*!
 *@brief	ゲームオブジェクトの基底クラス。
 */

#ifndef _CGAMEOBJECT_H_
#define _CGAMEOBJECT_H_


namespace tkEngine{
	class CGameObjectManager;
	class CRenderContext;
	typedef unsigned char	GameObjectPrio;
	/*!
	 *@brief	ゲームオブジェクト。
	 */
	class IGameObject : Noncopyable{
	public:
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		/*!
		 *@brief	デストラクタ
		 */
		virtual ~IGameObject()
		{
		}
	public:
		virtual void Start() = 0;
		/*!
		 *@brief	更新
		 */
		virtual void Update() = 0;
		/*!
		 *@brief	描画
		 */
		virtual void Render( CRenderContext& renderContext ) = 0;
		/*!
		 *@brief	削除されるときに呼ばれる。
		 *@details	CGameManager::DeleteGameObjectを呼んだときに実行されます。
		 * デストラクタより前に実行されます。
		 */
		virtual void OnDestroy(){} 
		/*!
		*@brief	実行優先度を取得。
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
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
		virtual void PreRender( CRenderContext& renderContext ) {}
		/*!
		 *@brief	Render関数が実行された後で呼ばれる描画処理
		 */
		virtual void PostRender(CRenderContext& renderContext ) {}
	public:
		void PostRenderWrapper(CRenderContext& renderContext)
		{
			if (m_isStart) {
				PostRender(renderContext);
			}
		}
		void RenderWrapper(CRenderContext& renderContext) 
		{
			if (m_isStart) {
				Render(renderContext);
			}
		}
		void PreRenderWrapper(CRenderContext& renderContext)
		{
			if (m_isStart) {
				PreRender(renderContext);
			}
		}
		void PostUpdateWrapper()
		{
			if (m_isStart) {
				PostUpdate();
			}
		}
		void PreUpdateWrapper()
		{
			if (m_isStart) {
				PreUpdate();
			}
		}
		void UpdateWrapper()
		{
			if (m_isStart) {
				Update();
			}
		}
		void StartWrapper()
		{
			if (!m_isStart) {
				Start();
				m_isStart = true;
			}
		}
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}
		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<実行優先度。
		bool m_isStart;						//!<Startの開始フラグ。
		bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた。
		
	};
}
#endif // _CGAMEOBJECT_H_