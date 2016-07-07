#include "stdafx.h"
#include "DoubleRelease.h"


class CHoge {
	int* a;
public:
	CHoge()
	{
		a = new int;
	}
	~CHoge()
	{
		delete a;
	}
};

//ダミー関数
void FunctionDummy(CHoge hoge)
{

}

//更新関数。
void DoubleRelease::Update()
{
	CHoge hoge;
	FunctionDummy(hoge);
	//Update関数を抜けると２重開放でクラッシュする。
}
