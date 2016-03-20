#ifndef _TK_CRENDERCONTEXT_H_
#define _TK_CRENDERCONTEXT_H_

namespace tkEngine{
	/*!
	* @brief	レンダリングコンテキスト。
	*/
	class CRenderContext{
	private:
		CRenderContext() {}
		~CRenderContext() {}
	public:
		static CRenderContext* GetInstance()
		{
			static CRenderContext instance;
			return &instance;
		}
		
	};
}

#endif // _TK_CRENDERCONTEXT_H_