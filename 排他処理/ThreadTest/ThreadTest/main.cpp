#include <future>
#include <windows.h>
int count = 0;
void Thread1()
{
	//countを10万回インクリメント
	for (int i = 0; i < 100000; i++) {
		count++;
	}
}
void Thread2()
{
	//countを10万回インクリメント
	for (int i = 0; i < 100000; i++) {
		count++;
	}
}
int main()
{
	std::thread th1 = std::thread([] {Thread1(); });	//Thread1を起動。
	std::thread th2 = std::thread([] {Thread2(); });	//Thread2を起動。
	th1.join();											//Thread1が終了するまで待機。
	th2.join();											//Thread2が終了するまで待機。

	//結果を表示。
	char message[256];
	sprintf_s(message, "count = %d\n", count);
	MessageBox(NULL, message, "Thread1の結果", MB_OK);			//20万になる？
	return 0;
}