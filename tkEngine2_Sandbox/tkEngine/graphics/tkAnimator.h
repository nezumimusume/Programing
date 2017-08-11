/*!
 * @brief	アニメータークラス。
 */

#pragma once

#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine{
	
	class CSkeleton;
	/*!
	 * @brief	アニメータークラス。
	 */
	class CAnimator{
	public:
		CAnimator();
		~CAnimator();
		/*!
		 * @brief	初期化。
		 *@param[in]	skinModelData	スキンモデルデータ。
		 */
		void Init(CSkinModelData& skinModelData);
		/*!
		* @brief	アニメーションを進める。
		*@param[in]	deltaTime		アニメーションを進める時間(単位：秒)。
		*/
		void Progress(float deltaTime);
		/*!
		 *@brief	アニメーションの再生。
		 *@param[in]	no		再生するアニメーションの番号。
		 */
		void Play(int no)
		{
			if (no >= (int)m_animationClips.size()) {
				TK_LOG("warning : no is over m_animationClips.size()");
				return;
			}
			m_currentAnimationClip = m_animationClips.at(no);
			m_globalTime = 0.0f;
			m_currentKeyframeNo = 0;
		}
	private:
		std::vector<CAnimationClip*>	m_animationClips;	//!<アニメーションクリップの配列。
		CSkeleton* m_skeleton = nullptr;	//!<アニメーションを適用するスケルトン。
		CAnimationClip* m_currentAnimationClip = nullptr;	//!<現在再生中のアニメーションクリップ。
		float m_globalTime = 0.0f;
		int m_currentKeyframeNo = 0;		//!<現在再生中のアニメーションキーフレーム番号。
		
	};
}