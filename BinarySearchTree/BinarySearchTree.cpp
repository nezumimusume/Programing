// BinarySearchTree.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

#define NAME_MAX_LEN	256

#define USE_SEARCH_RECURSIVE_CALL		//これを定義すると再帰呼び出のsearch関数が使用される

//ノード
struct NODE {
	char	*text;		//テキスト。
	NODE*	left;		//左のノード。
	NODE*	right;		//右のノード。
};
//トップ
NODE* top = NULL;
/*
*概要　指定した単語を二分木から検索。(こっちは再帰呼び出し！！！)
*引数	tango		検索対象の単語。
*引数  result		結果の格納先。
*/
int searchRecursiveCall(NODE* node, const char* tango, NODE** result)
{
	int ret = 0;
	int cmp;
	if (node == NULL) {
		//単語帳に登録されている単語が０。
		*result = NULL;
		return 0;
	}
	cmp = strcmp(tango, node->text);	//文字列比較
	if (cmp == 0) {
		//見つかった。
		*result = node;
		ret = 1;
	}
	else if (cmp < 0) {
		if (node->left != NULL) {
			//左のノードがある。
			ret = searchRecursiveCall(node->left, tango, result);		//再帰呼び出し！！！
		}
		else {
			//終端まで調べたけど見つからなかった。
			*result = node;	//終端のノードを記録する。
			ret = -1;		//左を調べて見つからなかった印をつける。
		}
	}
	else {
		if (node->right != NULL) {
			ret = searchRecursiveCall(node->right, tango, result);		//再帰呼び出し！！！
		}
		else {
			//終端まで調べたけど見つからなかった
			*result = node;
			ret = -2;

		}
	}
	return ret;
}

/*
 *概要　指定した単語を二分木から検索。
 *引数	tango		検索対象の単語。
 *引数  result		結果の格納先。
 */
int search(const char* tango, NODE** result)
{
	NODE* node = top;
	int ret = 0;
	int cmp;
	if (top == NULL) {
		//単語帳に登録されている単語が０。
		*result = NULL;
		return 0;
	}
	do {
		cmp = strcmp( tango, node->text);	//文字列比較
		if (cmp == 0) {
			//見つかった。
			*result = node;		
			ret = 1;
		}
		else if ( cmp < 0 ) {
			if ( node->left != NULL ) {
				//左のノードがある。
				node = node->left;
			}
			else {
				//終端まで調べたけど見つからなかった。
				*result = node;	//終端のノードを記録する。
				ret = -1;		//左を調べて見つからなかった印をつける。
			}
		}
		else {
			if (node->right != NULL) {
				node = node->right;
			}
			else {
				//終端まで調べたけど見つからなかった
				*result = node;
				ret = -2;

			}
		}
	} while (ret == 0);
	return ret;
}
/*
 * 概要　	単語を二分木に追加。
 * 引数　	tango		追加する単語。
 * 戻り値　	追加したノード
*/
NODE* add(char* tango)
{
	NODE* node;
	NODE* item;
	char* word;
#ifdef USE_SEARCH_RECURSIVE_CALL
	//再帰呼び出しを使用したsearch関数を使用する。
	int result = searchRecursiveCall(top, tango, &node);
#else
	//再帰呼び出しを使用しないsearch関数を使用する。
	int result = search(tango, &node);
#endif
	if (result == 1) {
		//この単語は登録済み。
		printf("この単語は登録済みです\n");
		return NULL;
	}
	item = (NODE*)malloc( sizeof( NODE ) );
	word = (char*)malloc( strlen( tango ) + 1 );	//ヌル文字のために+1する。
	item->text = word;
	//右と左のノードをNULLで初期化する。
	item->left = NULL;
	item->right = NULL;
	strcpy_s( item->text, strlen(tango) + 1, tango );
	switch (result) {
	case 0:
		//初めて単語が追加された。
		printf("初めて単語が追加されました。\n");
		top = item;
		break;
	case -1:
		//親のノードの左に追加する。
		printf("親のノードの左に追加します。\n");
		node->left = item;
		break;
	case -2:
		//親のノードの右に追加する。
		printf("親のノードの右に追加します。\n");
		node->right = item;
		break;
	}
	return item;
}
int main()
{
	char text[NAME_MAX_LEN];
	int ret = 0;
	
	do {
		printf("追加したい文字列を入力してください。\n");
		ret = scanf_s("%s", text, NAME_MAX_LEN);
		add( text );
	} while ( ret == 1 );
	
    return 0;
}

