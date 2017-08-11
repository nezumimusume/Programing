/*!
 *@brief	スケルトン
 */
#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine {
	namespace {
		void UpdateBoneWorldMatrix(CBone& bone, const CMatrix& parentMatrix)
		{
			CMatrix mBoneWorld;
			CMatrix localMatrix = bone.GetLocalMatrix();
			if (bone.GetParentId() == -1) {
				localMatrix.Mul(localMatrix, bone.GetOffsetLocalMatrix());
			}
			mBoneWorld.Mul(localMatrix, parentMatrix);
			bone.SetWorldMatrix(mBoneWorld);
			for (auto childBone : bone.GetChildren()) {
				UpdateBoneWorldMatrix(*childBone, mBoneWorld);
			}
		}
	}
	CSkeleton::CSkeleton()
	{
		//リザーブ。
		m_bones.reserve(BONE_MAX);
	}
	CSkeleton::~CSkeleton()
	{
	}
	void CSkeleton::AddBone(
		const wchar_t* boneName,
		const CMatrix& bindPose,
		const CMatrix& invBindPose,
		const CMatrix& localMatrix,
		int parentId
	)
	{
		CBonePtr bone = std::make_unique<CBone>(
			boneName, 
			bindPose,
			invBindPose,
			localMatrix,
			parentId
		);
		m_bones.push_back(std::move(bone));
		//ボーン行列を確保
		m_boneMatrixs = std::make_unique<CMatrix[]>(m_bones.size());
		//StructuredBufferを作成。
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(CMatrix);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
		desc.ByteWidth = stride * m_bones.size();
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_boneMatrixSB.Create(NULL, desc);
	}
	void CSkeleton::BuildHierarchy()
	{
		for (auto& bone : m_bones) {
			if (bone->GetParentId() != -1) {
				m_bones.at(bone->GetParentId())->AddChild(bone.get());
			}
		}
	}
	void CSkeleton::Update(const CMatrix& mWorld)
	{
		//ワールド行列を構築していく
		for (auto& bone : m_bones) {
			if (bone->GetParentId() != -1) {
				continue;
			}
			//ルート。
			UpdateBoneWorldMatrix(*bone, mWorld);
		}

		//ボーン行列を計算。
		int boneNo = 0;
		for (auto& bonePtr : m_bones) {
			CMatrix mBone;
			mBone.Mul(bonePtr->GetInvBindPoseMatrix(), bonePtr->GetWorldMatrix());
			m_boneMatrixs[boneNo] = mBone;
			boneNo++;
		}
	}
	void CSkeleton::Render(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_boneMatrixSB, m_boneMatrixs.get());
		//ボーン行列をSRVに設定。
		rc.VSSetShaderResource(103, m_boneMatrixSB.GetSRV());
	}
	
}
