#include <future>
#include "Semaphore.h"

Semaphore sem;		//countへのアクセスを排他処理をするためのセマフォ。
int count = 0;
void Thread1()
{
	//countを10万回インクリメント
	for (int i = 0; i < 100000; i++) {
		sem.GetSemaphore();		//セマフォ資源を取得(1減算)。セマフォを獲得できなかったら待ち行列に追加。
		count++;
		sem.ReleaseSemaphore();	//セマフォ資源を返却(1加算)。
	}
}
void Thread2()
{
	//countを10万回インクリメント
	for (int i = 0; i < 100000; i++) {
		sem.GetSemaphore();		//セマフォ資源を取得(1減算)。セマフォを獲得できなかったら眠る。
		count++;
		sem.ReleaseSemaphore();	//待ち行列入っているスレッドがいたら起こす。いなければセマフォ資源を返却(1加算)。
	}
}
int main()
{
	sem.Init( 1, 1 );									//セマフォを初期化。
	std::thread th1 = std::thread([] {Thread1(); });	//Thread1を起動。
	std::thread th2 = std::thread([] {Thread2(); });	//Thread2を起動。
	th1.join();											//Thread1が終了するまで待機。
	th2.join();											//Thread2が終了するまで待機。

	//結果を表示。
	char message[256];
	sprintf_s( message, "count = %d\n", count);
	MessageBox(NULL, message, "Thread2の結果", MB_OK);
	return 0;
}