/*!
 *@brief	スケルトン
 */
#pragma once


namespace tkEngine{
	/*!
	*@brief	ボーン。
	*/
	class CBone : Noncopyable{
	public:
		/*!
		*@brief	コンストラクタ。
		*@param[in]	boneName		ボーンの名前。
		*@param[in]	bindPose		バインドポーズの行列。
		*@param[in] invBindPose		バインドポーズの逆行列。
		*@param[in]	parentId		親のボーン番号。
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			int parentId
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_parentId(parentId)
		{
		}
		/*!
		 *@brief	ローカル行列を設定
		 */
		void SetLocalMatrix(const CMatrix& m)
		{
			m_localMatrix = m;
		}
		/*!
		 *@brief	ローカル行列を取得。
		 */
		const CMatrix& GetLocalMatrix() const
		{
			return m_localMatrix;
		}
		/*!
		*@brief	ワールド行列を設定。
		*/
		void SetWorldMatrix(const CMatrix& m)
		{
			m_worldMatrix = m;
		}
		/*!
		 *@brief	ワールド行列を取得。
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	バインドポーズの行列を取得。
		*/
		const CMatrix& GetBindPoseMatrix() const
		{
			return m_bindPose;
		}
		/*!
		 *@brief	バインドポーズの逆行列を取得。
		 */
		const CMatrix& GetInvBindPoseMatrix() const
		{
			return m_invBindPose;
		}
		/*!
		 *@brief	親のボーン行列を取得。
		 */
		int GetParentId() const
		{
			return m_parentId;
		}
		/*!
		*@brief	子供を追加。
		*/
		void AddChild(CBone* bone) 
		{
			m_children.push_back(bone);
		}
		/*!
		*@brief	子供を取得。
		*/
		std::list<CBone*>& GetChildren()
		{
			return m_children;
		}
		const CMatrix& GetOffsetLocalMatrix() const
		{
			return m_offsetLocalMatrix;
		}
		/*!
		 *@brief	名前の取得。
		 */
		const std::wstring& GetName() const
		{
			return m_boneName;
		}
	private:
		std::wstring	m_boneName;
		int				m_parentId = -1;	//!<親のボーン番号。
		CMatrix			m_bindPose;		//!<バインドポーズ。
		CMatrix			m_invBindPose;	//!<バインドポーズの逆行列。
		CMatrix			m_localMatrix = CMatrix::Identity;	//!<ローカル行列。
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<ワールド行列。
		CMatrix			m_offsetLocalMatrix;
		std::list<CBone*>	m_children;		//!<子供。
	};
	/*!
	 *@brief	スケルトン。
	 */
	class CSkeleton : Noncopyable {
	public:
		CSkeleton();
		~CSkeleton();
		
		/*!
		 *@brief	ボーンのローカル行列を設定。
		 *@param[in]	boneNo		ボーン番号
		 *@param[in]	m			行列。
		 */
		void SetBoneLocalMatrix(int boneNo, const CMatrix& m)
		{
			if (boneNo > (int)m_bones.size() - 1) {
				TK_WARNING("boneNo is over m_bones.size() ");
				return;
			}
			m_bones[boneNo]->SetLocalMatrix(m);
		}
		/*!
		 *@brief	ボーンの数を取得。
		 */
		int GetNumBones() const
		{
			return static_cast<int>(m_bones.size());
		}
		/*!
		*@brief	ロード。
		*@param[in]	filePath	ファイルパス。
		*/
		bool Load(const wchar_t* filePath);
		/*!
		 *@brief	ボーンの名前からボーンIDを検索。
		 */
		int FindBoneID(const wchar_t* boneName) const
		{
			for (int i = 0; i < (int)m_bones.size(); i++) {
				if (m_bones[i]->GetName() == boneName) {
					return i;
				}
			}
			//見つからなかった。
			return -1;
		}
		/*!
		*@brief	ボーンを取得。
		*/
		CBone* GetBone(int boneNo)
		{
			return m_bones[boneNo].get();
		}
	public:
		
		/*!
		 *@brief	更新。
		 */
		void Update(const CMatrix& mWorld);
		/*!
		 *@brief	描画処理から呼ばれる処理。
		 */
		void Render(CRenderContext& rc);
	private:
		/*!
		*@brief	すべでのボーンの追加が完了したときに呼び出す必要がある処理。
		*/
		void OnCompleteAddedAllBones();
	private:
		static const int BONE_MAX = 512;	//!<ボーンの最大数。
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<ボーンの配列。
		std::unique_ptr<CMatrix[]>	m_boneMatrixs;	//!<ボーン行列。
		CStructuredBuffer			m_boneMatrixSB;	//!<ボーン行列のストラクチャーバッファ。
	};
}