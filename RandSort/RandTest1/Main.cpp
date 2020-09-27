#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <vector>
#include <time.h>

// データの要素数
#define DATA_NUM 10


struct SomeData
{
	__int8 m_Number;
	__int8 m_Id;
}; 


// 10個の配列を0～100(被りなし)で初期化して返す関
SomeData* RandPerm();

// 昇順ソート関数
void AscendingSort(SomeData* data_, int indexNum_);

// 引数a_とb_を入れ替える関数
void Swap(__int8* a_, __int8* b_);

// 出力
void Print(SomeData* data_, int indexNum_);

/*===============MAIN================*/
int main()
{
	// メモリリーク検出用
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 乱数生成
	srand((unsigned int)time(nullptr));

	// 乱数を取得
	SomeData* hoge = RandPerm();

	// nullチェック
	if (hoge == nullptr) return -1;

	/****** ソート前 ******/
	printf("-----Befor-----\n");

	Print(hoge, DATA_NUM);

	printf("---------------\n");

	/****** ソート ******/
	AscendingSort(hoge, DATA_NUM);

	/****** ソート後の値を表示 ******/
	printf("-----Affter-----\n");

	Print(hoge, DATA_NUM);

	printf("---------------\n");


	// 解放
	free(hoge);
	getchar();


	return 0;
}


SomeData* RandPerm()
{
	// 戻り値用のデータを確保
	SomeData* ret_data = (SomeData*)malloc(sizeof(SomeData) * DATA_NUM);
	// データの初期化
	for (int i = 0; i < DATA_NUM; ++i) {
		// 全て-1で初期化
		ret_data[i].m_Number = -1;
		// 1番からIDを振っていく
		ret_data[i].m_Id = i + 1;
	}

	// 現在どこのデータまでいっているかをカウントする変数
	int count = 0;
	while (count != DATA_NUM)
	{
		// 0から100までの乱数を取得する
		int random_num = rand() % 101;
		for (int j = 0; j <= count; ++j)
		{
			// もしランダムででた値がすでに配列にあった場合
			if (ret_data[j].m_Number == random_num) {
				break;
			}

			// 最後まで探して同じ数がなかった場合
			if (j == count) {
				// 追加する
				ret_data[count].m_Number = random_num;
				count++;
				break;
			}
		}
	}

	return ret_data;
}

void AscendingSort(SomeData* data_, int indexNum_)
{
	for (int i = 0; i < indexNum_; ++i){
		for (int j = i+1; j < indexNum_; ++j){

			// 現在の要素 i と 次の要素を比較して現在の要素の方が大きければ入れ替える
			if (data_[i].m_Number > data_[j].m_Number) {
				Swap(&data_[i].m_Number, &data_[j].m_Number);
			}

		}
	}
}

void Swap(__int8* a_, __int8* b_)
{
	int temp = *a_;
	*a_ = *b_;
	*b_ = temp;
}

void Print(SomeData* data_, int indexNum_)
{
	for (int i = 0; i < indexNum_; ++i) {
		printf("id = %d\tnum = %d\n", data_[i].m_Id, data_[i].m_Number);
	}
}

