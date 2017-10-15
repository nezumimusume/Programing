/*!
 *@brief	�X�L�����f���f�[�^�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/animation/tkAnimationClip.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	
	/*!
	 *@brief
	 *  �G�t�F�N�g�t�@�N�g���B
	 */
	class CSkinModelEffectFactory : public DirectX::EffectFactory {
	public:
		CSkinModelEffectFactory(ID3D11Device* device) :
			EffectFactory(device) {}
		std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info,  ID3D11DeviceContext* deviceContext)override
		{
			std::shared_ptr<CModelEffect> effect = std::make_shared<CSkinModelEffect>();
			if (info.enableSkinning) {
				//�X�L�j���O����B
				effect = std::make_shared<CSkinModelEffect>();
			}
			else {
				//�X�L�j���O�Ȃ��B
				effect = std::make_shared<CNonSkinModelEffect>();
			}
			effect->SetMatrialName(info.name);
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
///////////////////////////////////////////////////////////////////////////
// ���f���G�t�F�N�g�B
///////////////////////////////////////////////////////////////////////////
	void __cdecl CModelEffect::Apply(ID3D11DeviceContext* deviceContext) 
	{
		if (m_renderContext == nullptr) {
			TK_WARNING("m_renderContext is nullptr");
			deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
			deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		}
		else {
			EnRenderStep renderStep = m_renderContext->GetRenderStep();
			switch (renderStep)
			{
			case enRenderStep_Render3DModelToScene:
				deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
				deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
				break;
			case enRenderStep_RenderToShadowMap:
			case enRenderStep_ZPrepass:
				deviceContext->VSSetShader((ID3D11VertexShader*)m_vsRenderToDepthShader.GetBody(), NULL, 0);
				deviceContext->PSSetShader((ID3D11PixelShader*)m_psRenderToDepthShader.GetBody(), NULL, 0);
				break;
			default:
				break;
			}
		}
		
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_diffuseTex);
		m_materialParam.hasNormalMap = 0;
		if (m_normalMap != nullptr) {
			deviceContext->PSSetShaderResources(enSkinModelSRVReg_NormalMap, 1, &m_normalMap);
			m_materialParam.hasNormalMap = 1;
		}
		m_materialParam.hasSpecularMap = 0;
		if (m_specularMap != nullptr) {
			deviceContext->PSSetShaderResources(enSKinModelSRVReg_Specularmap, 1, &m_specularMap);
			m_materialParam.hasSpecularMap = 1;
		}
		deviceContext->UpdateSubresource(m_materialParamCB.GetBody(), 0, NULL, &m_materialParam, 0, 0);
		deviceContext->PSSetConstantBuffers(enSkinModelCBReg_Material, 1, &m_materialParamCB.GetBody());

	}
	CSkinModelData::CSkinModelData()
	{
	}
	CSkinModelData::~CSkinModelData()
	{
	}
	
	bool CSkinModelData::Load(const wchar_t* filePath)
	{
		CSkinModelEffectFactory effectFactory(GraphicsEngine().GetD3DDevice());
		//�{�[���𔭌������Ƃ��̃R�[���o�b�N�B
		std::vector<int> localBoneIDtoGlobalBoneIDTbl; //���b�V���ɃE�F�C�g���ݒ肳��Ă���{�[�������̃{�[���z���ID����A���ׂẴ{�[���z���ID�ɕϊ�����e�[�u���B
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
		//�{�[���C���f�b�N�X�����������Ƃ��̃R�[���o�b�N�֐��B
		auto onFindBlendIndex = [&](auto& index){
			index.x = localBoneIDtoGlobalBoneIDTbl[index.x];
			index.y = localBoneIDtoGlobalBoneIDTbl[index.y];
			index.z = localBoneIDtoGlobalBoneIDTbl[index.z];
			index.w = localBoneIDtoGlobalBoneIDTbl[index.w];
		};
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::wstring skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(L".cmo");
		skeletonFilePath.replace(pos, 4, L".tks");
		m_skeleton.Load(skeletonFilePath.c_str());

		//���f���f�[�^�����[�h�B
		m_modelDx = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(), 
			filePath,
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
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				findMesh(mesh);
			}
		}
	}
}
