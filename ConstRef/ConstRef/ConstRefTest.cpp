
#include "stdafx.h"
#include "ConstRefTest.h"
#include "tkEngine/timer/tkStopwatch.h"
#include "tkEngine/random/tkRandom.h"

//メンバ変数にint型の1024分の配列を保持するだけのクラス。
class CDummy {
public:
	int a[1024];
};
int hoge = 0;

extern tkEngine::CRandom random;
//値渡しの関数。
void FunctionParamCopy(CDummy dummy)
{
}
//const参照の関数。
void FunctionConstRef(const CDummy& dummy)
{
}


/*!
*@brief	更新
*/
void ConstRefCallTest::Update()
{
	{
		CStopwatch sw;
		sw.Start();
		CDummy dummy;
		//参照渡し
		for (int i = 0; i < 10000000; i++) {
			FunctionConstRef(dummy);
		}

		sw.Stop();

		char resultTxt[256];
		sprintf(resultTxt, "const 参照の処理時間 = %lf(ミリ)\n", sw.GetElapsedMillisecond());
		MessageBox(NULL, resultTxt, "結果", MB_OK);
	}

	{
		CStopwatch sw;
		sw.Start();
		CDummy dummy;
		//コピー。
		for (int i = 0; i < 10000000; i++) {
			FunctionParamCopy(dummy);
		}
		sw.Stop();

		char resultTxt[256];
		sprintf(resultTxt, "値渡しの処理時間 = %lf(ミリ)\n", sw.GetElapsedMillisecond());
		MessageBox(NULL, resultTxt, "結果", MB_OK);
	}
	//死亡
	DeleteGO(this);
}

