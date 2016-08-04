/*!
 *@brief	スキンモデルデータ
 */
#ifndef _TKSKINMODELDATA_H_
#define _TKSKINMODELDATA_H_


namespace tkEngine{
	struct D3DXFRAME_DERIVED : public D3DXFRAME {
		D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
	};
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9* ppTextures;
		LPD3DXMESH pOrigMesh;
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD NumAttributeGroups;
		DWORD NumInfl;
		LPD3DXBUFFER pBoneCombinationBuf;
		D3DXMATRIX** ppBoneMatrixPtrs;
		D3DXMATRIX* pBoneOffsetMatrices;
		DWORD NumPaletteEntries;
		bool UseSoftwareVP;
		DWORD iAttributeSW;
	};
	class CAnimation;
	/*!
	 *@brief	スキンモデルデータ
	 */
	class CSkinModelData{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CSkinModelData();
		/*!
		 *@brief	デストラクタ。
		 */
		~CSkinModelData();
		/*!
		 * @brief	モデルデータをロード。
		 *@param[in]	filePath	ファイルパス。
		 *@param[out]	anim		アニメーション付きモデルデータの場合、アニメーションクラスも構築されます。
		 */
		void LoadModelData( const char* filePath, CAnimation* anim );
		/*!
		* @brief	引数で渡されたモデルデータを元にモデルを作成。
		*			メッシュデータだけ使いまわしされます。
		*@param[in]		modelData		モデルデータ。
		*/
		void CreateModelData( const CSkinModelData& modelData, CAnimation* anim);
		/*!
		* @brief	リリース。
		*/
		void Release();
		LPD3DXFRAME GetFrameRoot()
		{
			return m_frameRoot;
		}
		//テスト。
		void SetupOutputAnimationRegist(LPD3DXFRAME frame, ID3DXAnimationController* animCtr);
		/*!
		* @brief	ボーン行列を更新。
		*/
		void UpdateBoneMatrix( const CMatrix& matWorld );
	private:
		/*!
		* @brief	スケルトンのクローンを作成。
		*@param[out]	dstFrame		クローン先のスケルトンの格納先。
		*@param[in]		srcFrame		クローン元のスケルトン。
		*/
		void CloneSkeleton(LPD3DXFRAME& dstFrame, LPD3DXFRAME srcFrame);
			/*!
			* @brief	スケルトンのクローンを削除。
			*@param[in]	frame		削除するスケルトン。
			*/
			void DeleteCloneSkeleton(LPD3DXFRAME frame);
	private:
		LPD3DXFRAME					m_frameRoot;		//フレームルート。
		ID3DXAnimationController*	m_animController;	//アニメーションコントローラ。
		bool						m_isClone;			//クローン？
	};
}

#endif //_TKSKINMODELDATA_H_
