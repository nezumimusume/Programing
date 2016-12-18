/*!
 * @brief	CSkinModelDataのハンドルクラス。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/resource/tkSkinModelDataHandle.h"

namespace tkEngine{
	
	void CSkinModelDataHandle::LoadModelData(
		const char* modelPath,
		CAnimation* anim,
		bool isInstancing,
		int numInstance
		)
	{
		m_isLoadEnd = false;
		SkinModelDataResources().Load(*this, modelPath, anim, isInstancing, numInstance );
		m_isLoadEnd = true;
	}
	
	void CSkinModelDataHandle::LoadModelDataAsync(
		const char* modelPath,
		CAnimation* anim,
		bool isInstancing ,
		int numInstance 
		)
	{
		m_isLoadEnd = false;
		SkinModelDataResources().LoadAsync(*this, modelPath, anim, isInstancing, numInstance);
	}
	void CSkinModelDataHandle::Init(const std::shared_ptr<CSkinModelData>& skinModelData, CAnimation* anim, bool isClone)
	{
		m_originalSkinModelData = skinModelData;
		if(isClone){
			//クローンを作る？
			m_skinModelData.reset( new CSkinModelData );
			m_skinModelData->CloneModelData(*m_originalSkinModelData, anim);
		}
	}
}