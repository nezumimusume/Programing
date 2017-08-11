/*!
 *@brief	スケルトン
 */
#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine {
	CSkeleton::CSkeleton()
	{
		//リザーブ。
		m_bones.reserve(BONE_MAX);
	}
	CSkeleton::~CSkeleton()
	{
	}
	void CSkeleton::AddBone(
		const wchar_t* boneName,
		const CMatrix& bindPose,
		const CMatrix& invBindPose,
		const CMatrix& localMatrix
	)
	{
		CBonePtr bone = std::make_unique<CBone>(
			boneName, 
			bindPose,
			invBindPose,
			localMatrix
		);
		m_bones.push_back(std::move(bone));
	}
	
}
