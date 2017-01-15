#pragma once

namespace tkEngine {
	class CPIXPerfTag {
		CRenderContext& renderContext;
	public:
		CPIXPerfTag(CRenderContext& rc, LPCWSTR name) :
			renderContext(rc)
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			renderContext.SetRenderCommand(CRenderCommand_PerfBeginEvent(name));
#endif
		}
		~CPIXPerfTag()
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			renderContext.SetRenderCommand(CRenderCommand_PerfEndEvent());
#endif
		}
	};
}
