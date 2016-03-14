// DoublePointer.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


struct SBullet {
public:
	float velocity;		//初速度。
};
//ダブルポインタを使用するバージョン
void CreateBullet( SBullet** bullet )
{
	*bullet = new SBullet();
	(*bullet)->velocity = 10;
}
//普通のポインタを使用するバージョン
void CreateBullet2(SBullet* bullet)
{
	bullet = new SBullet();
	//bullet->velocity = 10;
}
int main()
{
	SBullet* bullet = NULL;
	//弾丸を生成
	CreateBullet( &bullet );	//期待通りbullet->velocityに10が入っている。
	SBullet* bullet2 = NULL;
	CreateBullet2(bullet2);		//bullet2はNULLのまま！

	//bulletとbullet2に入っているアドレスを表示。
	printf("bullet  addr = %x\n", (unsigned int)bullet );
	printf("bullet2 addr = %x\n", (unsigned int)bullet2 );
    return 0;
}

