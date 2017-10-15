/*!
 * @brief	アニメーション再生コントローラ。
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationPlayController.h"


namespace tkEngine{
	
	/*!
	*@brief	初期化。
	*/
	void CAnimationPlayController::Init(CSkeleton* skeleton)
	{
		int numBones = skeleton->GetNumBones();
		//ボーン行列をバシッと確保。
		m_boneMatrix.resize(numBones);
	}
	/*!
	 * @brief	アニメーションを進める。
	 *@param[in]	deltaTime		アニメーションを進める時間。
	 */
	void CAnimationPlayController::Update(float deltaTime)
	{
		if(m_animationClip == nullptr){
			TK_WARNING("m_animationClip is nullptr\n");
			return ;
		}
		const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();
		m_time += deltaTime;
		//補完時間も進めていく。
		m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
		while (true) {
			if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size()) {
				//終端まで行った。
				if (m_animationClip->IsLoop()) {
					//ループ。
					m_currentKeyFrameNo = 0;
					m_time = 0.0f;
				}
				else {
					//ワンショット再生。
					m_currentKeyFrameNo--;
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time) {
				//終わり。
				break;
			}
			//次へ。
			m_currentKeyFrameNo++;
		}
		//ボーン行列を計算していく。
		const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray) {
			if (keyFrameList.size() == 0) {
				continue;
			}
			//現在再生中のキーフレームを取ってくる。
			Keyframe* keyframe = keyFrameList.at(m_currentKeyFrameNo);
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
		
	}
}