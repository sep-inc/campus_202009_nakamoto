#include "YamanoteLineDB.h"
#include <stdio.h>
#include <string.h>

int main()
{
	// 乗車する駅名を保存する変数
	char entry_station_name[MAX_STATION_NAME_LENGTH] = { '\0' };

	// 乗車駅の要素番号を保存する変数
	__int8  entry_station_index = 0;

	// 降車する駅名を保存する変数
	char exit_station_name[MAX_STATION_NAME_LENGTH] = { '\0' };

	// 降車駅の要素を保存する変数
	__int8  exit_station_index = 0;

	// 駅が見つかったかどうかを保持する変数
	bool found_station = false;

	// 山手線の一周の時間
	__int8 yamanote_total_time = 0;

	// 右周りの合計時間 (分)
	__int8 right_total_time = 0;

	// 左周りの合計時間 (分)
	__int8 left_total_time = 0;

	// 山手線の乗車駅から右向きのテーブル
	Station yamanote_right_table[YAMANOTE_STATION_NUM];

	// 山手線の乗車駅からの左向きのテーブル
	Station yamanote_left_table[YAMANOTE_STATION_NUM];

	
	/* 乗車駅確認 */
	while (true)
	{
		printf("乗車駅を入力してください\n");

		// 乗車する駅を入力
		scanf_s("%s", entry_station_name, MAX_STATION_NAME_LENGTH);


		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// DBに駅があったら
			if (!strcmp(g_YamanoteDB[i].m_StationName, entry_station_name)) {
				printf("乗車駅 -> %s \n", &entry_station_name);
				found_station = true;

				// 要素を保存
				entry_station_index = i;
				break;
			}
		}

		// もし見つかったらループを抜ける
		if (found_station)break;

		printf("見つかりません。もう一度入力してください。\n");
	}


	/* 降車駅確認 */
		////////// 降車駅確認 /////////////////////
	found_station = false;
	while (true)
	{
		printf("降車駅を入力してください\n");

		// 降車する駅を入力
		scanf_s("%s", exit_station_name, MAX_STATION_NAME_LENGTH);

		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// DBに駅があったら
			if (!strcmp(g_YamanoteDB[i].m_StationName, exit_station_name)) {
				printf("降車駅 -> %s \n", &exit_station_name);
				found_station = true;

				// 要素を保存
				exit_station_index = i;
				break;
			}
		}
		// もし見つかったらループを抜ける
		if (found_station)break;

		// else もう一度入力
		printf("見つかりません。もう一度入力してください。 \n");
	}


	// 乗車駅からの右回りのテーブルを作る
	// 乗車駅の要素を取得
	__int8 index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_right_table[i] = g_YamanoteDB[index];

		index++;
		// 現在の要素数がDBの要素数を超えた場合0にする
		if (index >= YAMANOTE_STATION_NUM) index = 0;
	}

	// 乗車駅からの左回りのテーブルを作る
	// 乗車駅の要素を取得
	index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_left_table[i] = g_YamanoteDB[index];

		index--;
		// 現在の要素数が0よりも下になったらDBの最後の要素にする
		if (index < 0) index = YAMANOTE_STATION_NUM - 1;
	}


	// 右回りの時間を計測
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		if (!strcmp(yamanote_right_table[i].m_StationName, exit_station_name))
		{
			break;
		}

		right_total_time += yamanote_right_table[i].m_NectStationCost;
	}

	// 左回りの時間を計測
	// i = 1 にすることで次の乗車駅の次の駅から時間を足していく
	for (int i = 1; i < YAMANOTE_STATION_NUM; ++i)
	{
		left_total_time += yamanote_left_table[i].m_NectStationCost;

		if (!strcmp(yamanote_left_table[i].m_StationName, exit_station_name))
		{
			break;
		}
	}


	// 結果を出力
	printf("%s -> %s\n", entry_station_name, exit_station_name);
	printf("右回りにかかる時間は[ %d ]分です\n", right_total_time);
	printf("左回りにかかる時間は[ %d ]分です\n", left_total_time);


	// プログラム終了
	return 0;
}