/*!
 * @brief	アニメータークラス。
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimation.h"

namespace tkEngine{
	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
	}
	void CAnimation::Init(CSkinModelData& skinModelData)
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
	void CAnimation::Update(float deltaTime)
	{
		if (m_currentAnimationClip == nullptr 
			|| m_skeleton == nullptr 
		) {
			return;
		}
		//とりあえず適当に進めていく。
		int numBones = m_skeleton->GetNumBones();
		const auto& topBoneKeyFrameList = m_currentAnimationClip->GetTopBoneKeyFrameList();
		m_globalTime += deltaTime;
		while (true) {
			if (m_currentKeyframeNo >= topBoneKeyFrameList.size()) {
				//終端まで行った。
				if (m_currentAnimationClip->IsLoop()) {
					//ループ。
					m_currentKeyframeNo = 0;
					m_globalTime = 0.0f;
				}
				else {
					//ワンショット再生。
					m_currentKeyframeNo--;
				}
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
		const auto& keyFramePtrListArray = m_currentAnimationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray) {
			if (keyFrameList.size() == 0) {
				continue;
			}
			//現在再生中のキーフレームを取ってくる。
			Keyframe* keyframe = keyFrameList.at(m_currentKeyframeNo);
			m_skeleton->SetBoneLocalMatrix(
				keyframe->boneIndex, 
				keyframe->transform
			);
		}
	}
}