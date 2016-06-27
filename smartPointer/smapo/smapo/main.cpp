#include <stdio.h>
#include "UniquePtr.h"
#include <memory>

class HogeHoge {
public:
	HogeHoge()
	{
		printf("Call HogeHoge::Ctor\n");
	}
	~HogeHoge()
	{
		printf("Call HogeHoge::~Ctor\n");
	}

};
class Hoge {
	UniquePtr<HogeHoge>	hogehoge;			//自前のUniquePtrを使用した場合。
	std::unique_ptr<HogeHoge> hogehoge2;	//C++11で追加された標準のunique_ptrを使用した場合。こっちを使おうね。
public:
	Hoge()
	{
		hogehoge.reset(new HogeHoge);
		hogehoge2.reset(new HogeHoge);
		printf("Call Hoge::Ctor\n");
	}
	~Hoge()
	{
		printf("Call Hoge::~Ctor\n");
		//HogeHogeの開放も呼んでいないがちゃんと呼ばれる。
	}
	void Print()
	{
		printf("Hoge::Print\n");
	}
};
void Func()
{
	UniquePtr<Hoge>	hoge;	//HogeクラスのUniquePtr;
	hoge.reset(new Hoge);	//Hogeのインスタンスを生成。
	hoge->Print();			//普通のポインタのようにメンバ関数を呼ぶことももちろん可能。
	//開放をしていないけど、UniquePtrのデストラクタの中でdeleteを行っているので、newしたインスタンスは自動で削除される。
	//スコープを抜けると削除されるため、Scoped_ptrと呼ばれていた。
}
int main()
{
	Func();
	return 0;
}