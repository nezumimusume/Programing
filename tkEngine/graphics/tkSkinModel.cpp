#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/prerender/tkShadowMap.h"

namespace tkEngine{
	
	void CSkinModel::DrawMeshContainer_InstancingDrawCommon(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* meshContainer, int materialID)
	{
		LPDIRECT3DVERTEXBUFFER9 vb;
		LPDIRECT3DINDEXBUFFER9 ib;
		LPD3DXMESH mesh = meshContainer->MeshData.pMesh;
		mesh->GetVertexBuffer(&vb);
		mesh->GetIndexBuffer(&ib);
		DWORD attributeTableSize = 256;
		
		DWORD stride = m_skinModelData->GetVertexBufferStride();

		pd3dDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_skinModelData->GetNumInstance());
		pd3dDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
		
		pd3dDevice->SetVertexDeclaration(m_skinModelData->GetVertexDeclForInstancingDraw());

		pd3dDevice->SetStreamSource(0, vb, 0, stride);							//頂点バッファをストリーム0番目に設定
																					//ワールド行列を頂点バッファにコピー。
		
		pd3dDevice->SetStreamSource(
			1, 
			m_skinModelData->GetInstancingVertexBuffer().GetBody(), 
			0, 
			m_skinModelData->GetInstancingVertexBuffer().GetStride()
		);	
		pd3dDevice->SetIndices(ib);
		pd3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST, 
			0, 
			0, 
			mesh->GetNumVertices(), 
			meshContainer->pAttributeTable[materialID].FaceStart * 3, 
			meshContainer->pAttributeTable[materialID].FaceCount);
			
		//後始末
		pd3dDevice->SetStreamSourceFreq(0, 1);
		pd3dDevice->SetStreamSourceFreq(1, 1);

	}
	void CSkinModel::DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXMESHCONTAINER pMeshContainerBase, 
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		CLight* light,
		CTexture* normalMap,
		bool isInstancingDraw,
		bool isDrawToShadowMap
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
			if (isInstancingDraw) {
				if (pMeshContainer->pSkinInfo != NULL) {
					if (isDrawToShadowMap) {
						pEffect->SetTechnique("SkinModelInstancingRenderToShadowMap");
					}
					else {
						pEffect->SetTechnique("SkinModelInstancing");
					}
				}
				else {
					if (isDrawToShadowMap) {
						pEffect->SetTechnique("NoSkinModelInstancingRenderToShadowMap");
					}
					else {
						pEffect->SetTechnique("NoSkinModelInstancing");
					}
				}
			}
			else {
				if (pMeshContainer->pSkinInfo != NULL) {
					if (isDrawToShadowMap) {
						//シャドウマップに描画。
						pEffect->SetTechnique("SkinModelRenderShadowMap");
					}else{
						pEffect->SetTechnique("SkinModel");
					}
				}
				else {
					if (isDrawToShadowMap) {
						pEffect->SetTechnique("NoSkinModelRenderShadowMap");
					}else{
						pEffect->SetTechnique("NoSkinModel");
					}
				}
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
			int flag[4] = { 0 };
			if (normalMap != nullptr) {
				flag[0] = true;
				
				pEffect->SetTexture("g_normalTexture", normalMap->GetTextureDX());
			}
			if (!isDrawToShadowMap && m_isShadowReceiver) {
				//シャドウレシーバー。
				flag[1] = true;
				pEffect->SetTexture("g_shadowMap", ShadowMap().GetTexture()->GetTextureDX());
				const CMatrix& mLVP = ShadowMap().GetLVPMatrix();
				pEffect->SetValue("g_mLVP", &mLVP, sizeof(mLVP));
			}
			pEffect->SetValue("g_flags", flag, sizeof(flag));
			if (isDrawToShadowMap || m_isShadowReceiver) {
				float farNear[] = {
					ShadowMap().GetFar(),
					ShadowMap().GetNear()
				};
				pEffect->SetValue("g_farNear", farNear, sizeof(farNear));
			}
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
						TK_ASSERT(iPaletteEntry < MAX_MATRIX_PALLET, "ボーン行列パレットの最大数を超えた");
						D3DXMatrixMultiply(
							&m_boneMatrixPallet[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
					}
				}
				
					
				pEffect->SetMatrixArray("g_mWorldMatrixArray", m_boneMatrixPallet, pMeshContainer->NumPaletteEntries);
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
				if (isInstancingDraw) {
					//インスタンシング描画。
					DrawMeshContainer_InstancingDrawCommon(pd3dDevice, pMeshContainer, iAttrib);
					
				}
				else {
					pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				}
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
				if (isInstancingDraw) {
					//インスタンシング描画。
					DrawMeshContainer_InstancingDrawCommon(pd3dDevice, pMeshContainer, 0);
				}
				else {
					pMeshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
			pEffect->EndPass();
			pEffect->End();
		}
	}
	void CSkinModel::DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		bool isInstancingDraw,
		bool isDrawToShadowMap
	)
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
				m_light,
				m_normalMap,
				isInstancingDraw,
				isDrawToShadowMap
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
				isInstancingDraw,
				isDrawToShadowMap
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
				isInstancingDraw,
				isDrawToShadowMap
				);
		}
	}
	
	CSkinModel::CSkinModel() :
		m_skinModelData(nullptr),
		m_worldMatrix(CMatrix::Identity),
		m_light(nullptr),
		m_normalMap(nullptr),
		m_isShadowCaster(false),
		m_isShadowReceiver(false)
	{
	}
	CSkinModel::~CSkinModel()
	{

	}

	void CSkinModel::Init(CSkinModelData* modelData)
	{
		m_pEffect = EffectManager().LoadEffect("Assets/presetShader/skinModel.fx");
		m_skinModelData = modelData;
		m_shadowCaster.Create(this);
	}
	void CSkinModel::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
	{
		if (m_isShadowCaster && ShadowMap().IsEnable()) {
			//シャドウキャスター。
			ShadowMap().Entry(&m_shadowCaster);
		}
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
	/*!
	*@brief	シャドウマップに描画
	*@details
	* CShadowMapから呼び出されます。ユーザーは使用しないように。
	*/
	void CSkinModel::DrawToShadowMap(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_skinModelData) {
			renderContext.DrawSkinModelToShadowMap(this, viewMatrix, projMatrix);
		}
	}
	void CSkinModel::Draw(CRenderContext& renderContext, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_skinModelData) {
			renderContext.DrawSkinModel(this, viewMatrix, projMatrix);
		}
	}
	void CSkinModel::ImmidiateDraw(LPDIRECT3DDEVICE9 pd3ddevice, D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawToShadowMap)
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
				m_skinModelData->GetNumInstance() != 0,
				isDrawToShadowMap
			);
		}
	}
}