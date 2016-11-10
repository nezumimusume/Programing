/*!
 *@brief	波形データバンク。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Sound/tkWaveFile.h"
#include "tkEngine/Sound/tkWaveFileBank.h"

namespace tkEngine{
	CWaveFileBank::CWaveFileBank()
	{
	}
	CWaveFileBank::~CWaveFileBank()
	{
	}
	void CWaveFileBank::RegistWaveFile(int groupID, CWaveFilePtr waveFile)
	{
		TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
	}
	/*!
	*@brief	引数で指定したファイルパスの波形データがバンクに登録されているか検索する。
	*@param[in]	groupID		グループＩＤ。指定できるＩＤの最大値はMAX_GROUP-1。
	*@param[in]	filePath	ファイルパス。
	*@return 波形データ。登録されていない場合はNULLが返る。
	*/
	CWaveFilePtr CWaveFileBank::FindWaveFile(int groupID, const char* filePath)
	{
		TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		auto value = m_waveFileMap[groupID].find(CUtil::MakeHash(filePath));
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return CWaveFilePtr();
	}
}
