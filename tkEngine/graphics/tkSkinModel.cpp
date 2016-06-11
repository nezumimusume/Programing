#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	extern UINT                 g_NumBoneMatricesMax;
	extern D3DXMATRIXA16*       g_pBoneMatrices ;
	namespace {
		void DrawMeshContainer(
			IDirect3DDevice9* pd3dDevice, 
			LPD3DXMESHCONTAINER pMeshContainerBase, 
			LPD3DXFRAME pFrameBase,
			ID3DXEffect* pEffect,
			D3DXMATRIX* worldMatrix,
			D3DXMATRIX* rotationMatrix,
			D3DXMATRIX* viewMatrix,
			D3DXMATRIX* projMatrix,
			CLight* light
		)
		{
			D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
			D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
			UINT iAttrib;
			LPD3DXBONECOMBINATION pBoneComb;

			D3DXMATRIXA16 matTemp;
			D3DCAPS9 d3dCaps;
			pd3dDevice->GetDeviceCaps(&d3dCaps);
			D3DXMATRIX viewProj;
			D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
			
			//テクニックを設定。
			{
				if (pMeshContainer->pSkinInfo != NULL) {
					pEffect->SetTechnique("SkinModel");
				}
				else {
					pEffect->SetTechnique("NoSkinModel");
				}
			}
			//共通の定数レジスタを設定
			{
				//ビュープロジェクション
				pEffect->SetMatrix("g_mViewProj", &viewProj);
				//ライト
				pEffect->SetValue(
					"g_light",
					light,
					sizeof(CLight)
				);
			}
			if (pMeshContainer->pSkinInfo != NULL)
			{
				//スキン情報有り。
				pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
				for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
				{
					// first calculate all the world matrices
					for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
					{
						DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
						if (iMatrixIndex != UINT_MAX)
						{
							D3DXMatrixMultiply(
								&g_pBoneMatrices[iPaletteEntry],
								&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
								pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
							);
							//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
						}
					}
				
					
					pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
					pEffect->SetInt("g_numBone", pMeshContainer->NumInfl);
					// ディフューズテクスチャ。
					pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

					// ボーン数。
					pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
					D3DXMATRIX viewRotInv;
					D3DXMatrixInverse(&viewRotInv, NULL, viewMatrix);
					viewRotInv.m[3][0] = 0.0f;
					viewRotInv.m[3][1] = 0.0f;
					viewRotInv.m[3][2] = 0.0f;
					viewRotInv.m[3][3] = 1.0f;
					D3DXMatrixTranspose(&viewRotInv, &viewRotInv);
					pEffect->SetMatrix("g_viewMatrixRotInv", &viewRotInv);
					pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
					pEffect->BeginPass(0);
					pEffect->CommitChanges();
					// draw the subset with the current world matrix palette and material state
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
					pEffect->EndPass();
					pEffect->End();

				}
			}
			else {
				
				D3DXMATRIX mWorld;
				if (pFrame != NULL) {
					mWorld = pFrame->CombinedTransformationMatrix;
				}
				else {
					mWorld = *worldMatrix;
				}
				
				pEffect->SetMatrix("g_worldMatrix", &mWorld);
				pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
				pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
				pEffect->BeginPass(0);

				for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {
					pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
					pEffect->CommitChanges();
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
				pEffect->EndPass();
				pEffect->End();
			}
		}
		void DrawFrame(
			IDirect3DDevice9* pd3dDevice, 
			LPD3DXFRAME pFrame, 
			ID3DXEffect* pEffect,
			D3DXMATRIX* worldMatrix,
			D3DXMATRIX* rotationMatrix,
			D3DXMATRIX* viewMatrix, 
			D3DXMATRIX* projMatrix,
			CLight* light)
		{
			LPD3DXMESHCONTAINER pMeshContainer;

			pMeshContainer = pFrame->pMeshContainer;
			while (pMeshContainer != NULL)
			{
				DrawMeshContainer(
					pd3dDevice, 
					pMeshContainer, 
					pFrame, 
					pEffect,
					worldMatrix,
					rotationMatrix,
					viewMatrix,
					projMatrix,
					light
					);

				pMeshContainer = pMeshContainer->pNextMeshContainer;
			}

			if (pFrame->pFrameSibling != NULL)
			{
				DrawFrame(
					pd3dDevice, 
					pFrame->pFrameSibling, 
					pEffect,
					worldMatrix,
					rotationMatrix,
					viewMatrix,
					projMatrix,
					light
					);
			}

			if (pFrame->pFrameFirstChild != NULL)
			{
				DrawFrame(
					pd3dDevice, 
					pFrame->pFrameFirstChild, 
					pEffect,
					worldMatrix,
					rotationMatrix,
					viewMatrix,
					projMatrix,
					light
					);
			}
		}
	}
	CSkinModel::CSkinModel() :
		m_skinModelData(nullptr),
		m_worldMatrix(CMatrix::Identity),
		m_light(nullptr)
	{
	}
	CSkinModel::~CSkinModel()
	{

	}

	void CSkinModel::Init(CSkinModelData* modelData)
	{
		m_pEffect = EffectManager().LoadEffect("Assets/presetShader/skinModel.fx");
		m_skinModelData = modelData;
	}
	void CSkinModel::UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
	{
		CMatrix mTrans, mScale;
		mTrans.MakeTranslation(trans);
		m_rotationMatrix.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		m_worldMatrix.Mul(mScale, m_rotationMatrix);
		m_worldMatrix.Mul(m_worldMatrix, mTrans);
		if (m_skinModelData) {
			m_skinModelData->UpdateBoneMatrix(m_worldMatrix);	//ボーン行列を更新。
		}
	}
	void CSkinModel::Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_skinModelData) {
			renderContext.DrawSkinModel(this, viewMatrix, projMatrix);
		}
	}
	void CSkinModel::ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix)
	{
		if (m_skinModelData) {
			DrawFrame(
				pd3ddevice, 
				m_skinModelData->GetFrameRoot(), 
				m_pEffect->GetD3DXEffect(),
				r_cast<D3DXMATRIX*>(&m_worldMatrix),
				r_cast<D3DXMATRIX*>(&m_rotationMatrix),
				viewMatrix,
				projMatrix,
				m_light
				);
		}
	}
}