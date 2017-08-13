/*!
 *@brief	スキンモデルデータ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine{
	
	/*!
	 *@brief
	 *  エフェクトファクトリ。
	 */
	class CSkinModelEffectFactory : public DirectX::EffectFactory {
	public:
		CSkinModelEffectFactory(ID3D11Device* device) :
			EffectFactory(device) {}
		std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info,  ID3D11DeviceContext* deviceContext)override
		{
			std::shared_ptr<CModelEffect> effect = std::make_shared<CSkinModelEffect>();
			if (info.enableSkinning) {
				//スキニングあり。
				effect = std::make_shared<CSkinModelEffect>();
			}
			else {
				//スキニングなし。
				effect = std::make_shared<CNonSkinModelEffect>();
			}
			
			if (info.diffuseTexture && *info.diffuseTexture)
			{
				ID3D11ShaderResourceView* texSRV;
				DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
				effect->SetDiffuseTexture(texSRV);
			}
			return effect;
		}

		void __cdecl CreateTexture( const wchar_t* name,  ID3D11DeviceContext* deviceContext,  ID3D11ShaderResourceView** textureView) override
		{
			return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
		}
	};
	CSkinModelData::CSkinModelData()
	{
	}
	CSkinModelData::~CSkinModelData()
	{
	}
	
	bool CSkinModelData::Load(const wchar_t* filePath)
	{
		CSkinModelEffectFactory effectFactory(GraphicsEngine().GetD3DDevice());
		//ボーンを発見したときのコールバック。
		auto onFindBone = [&](
			const wchar_t* boneName, 
			const VSD3DStarter::Bone* bone,
			int baseBoneNo
		) {
			int parentIndex = bone->ParentIndex;
			if (parentIndex != -1) {
				parentIndex += baseBoneNo;
			}
			m_skeleton.AddBone(
				boneName, 
				CMatrix(bone->BindPos),
				CMatrix(bone->InvBindPos), 
				CMatrix(bone->LocalTransform),
				parentIndex);
		};
		//アニメーションクリップを発見したときのコールバック。
		auto onFindAnimationClip = [&](
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip, 
			const VSD3DStarter::Keyframe* keyFrame,
			int baseBoneNo
		) {
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto& clip) {return clip->GetName() == clipName;}
			);
			if (it == m_animationClips.end()) {
				//新規
				CAnimationClipPtr animClip = std::make_unique<CAnimationClip>(clipName, clip, keyFrame);
				m_animationClips.push_back(std::move(animClip));
			}
			else {
				//既存のクリップなのでキーフレームを追加する。
				(*it)->AddKeyFrame(clip->keys, keyFrame, baseBoneNo);
			}
		};
		
		//モデルデータをロード。
		m_modelDx = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(), 
			filePath, 
			effectFactory, 
			false,
			false,
			onFindBone,
			onFindAnimationClip
		);
		//ボーンの追加完了したときの処理を呼び出す。。
		m_skeleton.OnCompleteAddedAllBones();

		return true;
	}
}

