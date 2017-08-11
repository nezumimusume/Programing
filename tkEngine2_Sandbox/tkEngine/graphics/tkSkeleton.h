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
		*@param[in] localMatrix		ローカル行列。
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_localMatrix(localMatrix)
		{
		}

	private:
		std::wstring	m_boneName;
		CMatrix			m_bindPose;		//!<バインドポーズ。
		CMatrix			m_invBindPose;	//!<バインドポーズの逆行列。
		CMatrix			m_localMatrix;	//!<ローカル行列。
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<ワールド行列。
	};
	/*!
	 *@brief	スケルトン。
	 */
	class CSkeleton : Noncopyable{
	public:
		CSkeleton();
		~CSkeleton();
		/*!
		*@brief	ボーンを追加。
		*@param[in]	boneName		ボーンの名前。
		*@param[in]	bindPose		バインドポーズの行列。
		*@param[in] invBindPose		バインドポーズの逆行列。
		*@param[in] localMatrix		ローカル行列。
		*/
		void AddBone(
			const wchar_t* boneName, 
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			const CMatrix& localMatrix
		);
	private:
		static const int BONE_MAX = 512;	//!<ボーンの最大数。
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<ボーンの配列。
	};
}