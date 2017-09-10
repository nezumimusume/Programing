/*!
 * @brief	アニメータークラス。
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimation.h"

namespace tkEngine{

	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
	}
	void CAnimation::Init(CSkinModelData& skinModelData, CAnimationClip* animClipList[], int numAnimClip)
	{
		TK_ASSERT(animClipList != nullptr, "animClipListがNULLです。");
		m_skeleton = &skinModelData.GetSkeleton();
		for (int i = 0; i < numAnimClip; i++) {
			m_animationClips.push_back(animClipList[i]);
		}
		for (auto& ctr : m_animationPlayController) {
			ctr.Init(m_skeleton);
		}
		
		Play(0);
	}
	/*!
	 * @brief	ローカルポーズの更新。
	 */
	void CAnimation::UpdateLocalPose(float deltaTime)
	{
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f) {
			//補間完了。
			//現在の最終アニメーションコントローラへのインデックスが開始インデックスになる。
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController-1; i++) {
			int index = GetAnimationControllerIndex(m_startAnimationPlayController, i );
			m_animationPlayController[index].Update(deltaTime);
		}
		//最後のポーズだけ進めていく。
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime);
		
	}
	/*!
	 * @brief	グローバルポーズの更新。
	 */
	void CAnimation::UpdateGlobalPose()
	{
		//グローバルポーズ計算用のメモリをスタックから確保。
		int numBone = m_skeleton->GetNumBones();
		CMatrix* globalPose = (CMatrix*)alloca(sizeof(CMatrix) * numBone);
		for (int i = 0; i < numBone; i++) {
			globalPose[i] = CMatrix::Identity;
		}
		//グローバルポーズを計算していく。
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			float intepolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			for (int boneNo = 0; boneNo < numBone; boneNo++) {
				for (int x = 0; x < 4; x++) {
					for (int y = 0; y < 4; y++) {
						globalPose[boneNo].m[x][y] = 
							globalPose[boneNo].m[x][y] * (1.0f - intepolateRate) 
							+ localBoneMatrix[boneNo].m[x][y] * intepolateRate;
					}
				}
				
			}
		}
		//グローバルポーズをスケルトンに反映させていく。
		for (int boneNo = 0; boneNo < numBone; boneNo++) {
			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				globalPose[boneNo]
			);
		}
		
		//最終アニメーション以外は補間完了していたら除去していく。
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f) {
				//補間が終わっているのでアニメーションの開始位置を前にする。
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;
	}
	/*!
	* @brief	アニメーションを進める。
	*@param[in]	deltaTime		アニメーションを進める時間(単位：秒)。
	*/
	void CAnimation::Update(float deltaTime)
	{
		if (m_numAnimationPlayController == 0) {
			return;
		}
		//ローカルポーズの更新をやっていく。
		UpdateLocalPose(deltaTime);
		
		//グローバルポーズを計算していく。
		UpdateGlobalPose();
	}
}