#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkAnimation.h"

namespace tkEngine{
	void CAnimation::Init(ID3DXAnimationController* anim)
	{
		pAnimController = anim;
		ID3DXAnimationSet* animSet;
		pAnimController->GetAnimationSet(0, &animSet);
		numAnimSet = pAnimController->GetMaxNumAnimationSets();
		numMaxTracks = pAnimController->GetMaxNumTracks();
		blendRateTable.reset( new float[numMaxTracks] );
		animationSets.reset(new ID3DXAnimationSet*[numAnimSet]);
		for( int i = 0; i < numMaxTracks; i++ ){
			blendRateTable[i] = 1.0f;
		}
		//アニメーションセットを初期化。
		for (int i = 0; i < numAnimSet; i++) {
			pAnimController->GetAnimationSet(i, &animationSets[i]);
		}
	}
#if 0
	void CAnimation::BlendAnimation(int animationSetIndex)
	{
		if (pAnimController){
			isBlending = true;
			currentTrackNo++;
			currentTrackNo %= numAnimSet;
			pAnimController->SetTrackWeight(0, 0.0f);
			pAnimController->SetTrackWeight(1, 1.0f);
			pAnimController->SetTrackSpeed(0, 1.0f);
			pAnimController->SetTrackSpeed(1, 1.0f);
			pAnimController->SetTrackEnable(currentTrackNo, TRUE);
			pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[animationSetIndex]);
		}
	}
#endif
	void CAnimation::PlayAnimation(int animationSetIndex)
	{
		if (animationSetIndex < numAnimSet) {
			if (pAnimController) {
				currentAnimationSetNo = animationSetIndex;
				currentTrackNo = 0;
				//0番目以外のトラックは無効にする。
				for (int i = 1; i < numMaxTracks; i++) {
					pAnimController->SetTrackEnable(i,  FALSE);
				}
				pAnimController->SetTrackWeight(0, 1.0f);
				pAnimController->SetTrackAnimationSet(currentTrackNo, animationSets[currentAnimationSetNo]);
				pAnimController->SetTrackEnable(0, TRUE);
				pAnimController->SetTrackPosition(0, 0.0f);
			}
		}
		else {
			TK_LOG("warning!!! animationSetIndex is over range!!!!!");
		}
	}
	void CAnimation::PlayAnimation(int animationSetIndex, float interpolateTime)
	{
		if (animationSetIndex < numAnimSet) {
			if (pAnimController) {
				//補間開始の印。
				isInterpolate = true;
				this->interpolateTime = 0.0f;
				interpolateEndTime = interpolateTime;
				currentTrackNo = (currentTrackNo+1) % numMaxTracks;
				pAnimController->SetTrackAnimationSet( currentTrackNo, animationSets[animationSetIndex]);
				pAnimController->SetTrackEnable(currentTrackNo, TRUE);
				pAnimController->SetTrackSpeed(currentTrackNo, 1.0f);
				pAnimController->SetTrackPosition(currentTrackNo, 0.0f);
			}
		}
		else {
			TK_LOG("warning!!! animationSetIndex is over range!!!!!");
		}
	}
	void CAnimation::Update(float deltaTime)
	{
		if (pAnimController) {
			pAnimController->AdvanceTime(deltaTime, NULL);
		}
		if(isInterpolate){
			//補間中。
			interpolateTime += deltaTime;
			float weight = 0.0f;
			if(interpolateTime > interpolateEndTime){
				//補間終了。
				isInterpolate = false;
				weight = 1.0f;
				//現在のトラック以外を無効にする。
				for( int i = 0; i < numMaxTracks; i++ ){
					if( i != currentTrackNo ){
						pAnimController->SetTrackEnable(i,  FALSE);
					}
				}
			}else{
				weight = interpolateTime / interpolateEndTime;
				float invWeight = 1.0f - weight;
				//ウェイトを設定していく。
				for( int i = 0; i < numMaxTracks; i++ ){
					if( i != currentTrackNo ){
						pAnimController->SetTrackWeight(i, blendRateTable[i] * invWeight );
					}else{
						pAnimController->SetTrackWeight(i, weight );
					}
				}
			}
		}
	}
}
