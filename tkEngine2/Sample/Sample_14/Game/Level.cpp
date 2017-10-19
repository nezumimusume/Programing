#include "stdafx.h"
#include "Level.h"
#include "MapChip.h"

Level::Level()
{
}


Level::~Level()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}
/*!
*@brief	レベルの作成。
*@param[in]	levelDataFilePath	読み込むレベルデータのファイルパス。
*/
void Level::Build(const wchar_t* levelDataFilePath)
{
	//今回は配置データとしてスケルトンを利用する。
	CSkeleton skeleton;
	skeleton.Load(levelDataFilePath);
	int numMapChip = skeleton.GetNumBones();
	for (int i = 1; i < numMapChip; i++) {	//0番目はダミーデータなので無視。
		CBone* bone = skeleton.GetBone(i);
		//ボーンから拡大率、平行移動、回転を取得する。
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//3dsMaxとは軸が違うので、補正を入れる。
		float t = position.y;
		position.y = position.z;
		position.z = -t;
		t = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -t;
		//拡大どうしようかねぇ・・・

		//ボーン名からモデルデータのファイルパスを作成する。
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(mapChip);
	}

}