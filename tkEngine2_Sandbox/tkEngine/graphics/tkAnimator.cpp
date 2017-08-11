/*!
 * @brief	アニメータークラス。
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimator.h"

namespace tkEngine{
	CAnimator::CAnimator()
	{
	}
	CAnimator::~CAnimator()
	{
	}
	void CAnimator::Init(CSkinModelData& skinModelData)
	{
		std::vector<CAnimationClipPtr>& animClips = skinModelData.GetAnimationClips();
		for(auto& clip : animClips){
			m_animationClips.push_back(clip.get());
		}
		m_skeleton = &skinModelData.GetSkeleton();
	}
	/*!
	* @brief	アニメーションを進める。
	*@param[in]	deltaTime		アニメーションを進める時間(単位：秒)。
	*/
	void CAnimator::Progress(float deltaTime)
	{
		if (m_currentAnimationClip == nullptr 
			|| m_skeleton == nullptr 
		) {
			return;
		}
		//とりあえず適当に進めていく。
		int numBones = m_skeleton->GetNumBones();
		const auto& keyFramePtrListArray = m_currentAnimationClip->GetKeyFramePtrListArray();
		const auto& topBoneKeyFrameList = keyFramePtrListArray.at(0);
		m_globalTime += deltaTime;
		while (true) {
			if (m_currentKeyframeNo >= topBoneKeyFrameList.size()) {
				//終端まで行った。
				//@todo ループするアニメーションクリップならループするようにするか？
				m_currentKeyframeNo--;
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyframeNo)->time >= m_globalTime) {
				//終わり。
				break;
			}
			//次へ。
			m_currentKeyframeNo++;
		}
		//スケルトンに反映させていく。
		//とりあえずテストデータはフルキーなので何も考えなくてよさげ。
		for (const auto& keyFrameList : keyFramePtrListArray) {
			//現在再生中のキーフレームを取ってくる。
			Keyframe* keyframe = keyFrameList.at(m_currentKeyframeNo);
			m_skeleton->SetBoneLocalMatrix(
				keyframe->boneIndex, 
				keyframe->transform
			);
		}
	}
}