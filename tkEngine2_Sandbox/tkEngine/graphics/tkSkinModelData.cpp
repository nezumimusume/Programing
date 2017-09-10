/*!
 *@brief	スキンモデルデータ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/animation/tkAnimationClip.h"

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
		std::vector<int> localBoneIDtoGlobalBoneIDTbl; //メッシュにウェイトが設定されているボーンだけのボーン配列のIDから、すべてのボーン配列のIDに変換するテーブル。
		localBoneIDtoGlobalBoneIDTbl.reserve(512);
		auto onFindBone = [&](
			const wchar_t* boneName, 
			const VSD3DStarter::Bone* bone,
			int baseBoneNo
		) {
			int globalBoneID = m_skeleton.FindBoneID(boneName);
			if (globalBoneID == -1) {
				TK_WARNING("BoneID wasn't found!!!!");
				return;
			}
			localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
		};
		//ボーンインデックスが見つかったときのコールバック関数。
		auto onFindBlendIndex = [&](auto& index){
			index.x = localBoneIDtoGlobalBoneIDTbl[index.x];
			index.y = localBoneIDtoGlobalBoneIDTbl[index.y];
			index.z = localBoneIDtoGlobalBoneIDTbl[index.z];
			index.w = localBoneIDtoGlobalBoneIDTbl[index.w];
		};
		//スケルトンのデータを読み込み。
		std::wstring skeletonFilePath = filePath;
		skeletonFilePath += L".tks";
		m_skeleton.Load(skeletonFilePath.c_str());

		//モデルデータをロード。
		std::wstring modelDataPath = filePath;
		modelDataPath += L".cmo";
		m_modelDx = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(), 
			modelDataPath.c_str(),
			effectFactory, 
			false,
			false,
			onFindBone,
			onFindBlendIndex
		);
		

		return true;
	}
	void CSkinModelData::FindMesh(OnFindMesh findMesh)
	{
		for (const auto& modelMeshs : m_modelDx->meshes) {
			for (const std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				findMesh(mesh);
			}
		}
	}
}

