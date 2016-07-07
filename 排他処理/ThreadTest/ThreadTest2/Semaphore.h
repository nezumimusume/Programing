#pragma once
#include <windows.h>

//セマフォ。
class Semaphore {
	HANDLE  m_hSemaphore;	//セマフォのハンドル
public:
	Semaphore() : m_hSemaphore(NULL)
	{
		
	}
	~Semaphore()
	{
		Delete();
	}
	//初期化
	//initCount	セマフォの初期値
	//maxCount	セマフォの最大値
	void Init(int initCount, int maxCount)
	{
		//セマフォを作成。
		m_hSemaphore = CreateSemaphore(
			NULL, 1, 1, TEXT("semaphore")
			);
	}
	//解放
	void Delete()
	{
		if (m_hSemaphore != NULL) {
			CloseHandle(m_hSemaphore);
			m_hSemaphore = NULL;
		}
	}
	//セマフォの資源を取得。取得できない場合は取得できるようになるまで眠る。
	void GetSemaphore()
	{
		WaitForSingleObject(m_hSemaphore, INFINITE);
	}
	//セマフォの資源を返却。
	void ReleaseSemaphore()
	{
		::ReleaseSemaphore(m_hSemaphore, 1, NULL);
	}
};