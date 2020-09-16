﻿#include "YamanoteLineDB.h"
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

	// 右回りの合計時間 (分)
	__int8 right_total_time = 0;

	// 左回りの合計時間 (分)
	__int8 left_total_time = 0;

	// 中央線を利用した右回りにかかる時間(分)
	__int8 chuo_right_total_time = 0;

	// 中央線を利用した左回りにかかる時間(分)
	__int8 chuo_left_total_time = 0;



	// 山手線の乗車駅から右向きのテーブル
	Station yamanote_right_table[YAMANOTE_STATION_NUM] = { 0 };

	// 山手線の乗車駅からの左向きのテーブル
	Station yamanote_left_table[YAMANOTE_STATION_NUM] = { 0 };

	// 山手線の乗車駅から左回りでかつ中央線を通るテーブル
	Station yamanote_left_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM] = { 0 };

	// 山手線の乗車駅から右回りでかつ中央線を通るテーブル
	Station yamanote_right_through_chuo_table[YAMANOTE_STATION_NUM + CHUO_STATION_NUM] = { 0 };


	////////// 乗車駅確認 /////////////////////
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


	////////// 降車駅確認 /////////////////////
	found_station = false;
	while (true)
	{
		printf("降車駅を入力してください\n");

		// 降車する駅を入力
		scanf_s("%s", exit_station_name, MAX_STATION_NAME_LENGTH);

		for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
		{
			// 乗車駅テーブルからの降車駅を探す
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




	////////////////////////////////// 各テーブルを作成 /////////////////////////////////////////////
	
	/////////////////////////////////// 右回りのテーブルを作成 //////////////////////////////////////////
	__int8 current_station_index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_right_table[i] = g_YamanoteDB[current_station_index];

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;
		
		current_station_index++;
		// 現在の要素数がDBの要素数を超えた場合0にする
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
	}


	/////////////////////////////////// 左回りのテーブルを作成 //////////////////////////////////////////
	current_station_index = entry_station_index;
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		yamanote_left_table[i] = g_YamanoteDB[current_station_index];

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		current_station_index--;
		// 現在の要素数が0よりも下になったらDBの最後の要素にする
		if (current_station_index < 0) current_station_index = YAMANOTE_INDEX_NUM;
	}

	
	//////////////////////////////////////// 中央線を利用した右回りのテーブルを作成 //////////////////////////////////////////

	// 現在の駅のインデックスを保持する変数
	current_station_index = entry_station_index;

	// 新しく作るテーブルの要素
	__int8 new_table_index = 0;

	// 中央線を抜けた後に右か左のどちらにいくかを保存する変数
	// true -> 右    false -> 左
	bool is_right = true;

	// 次の駅が+なのか-なのかを判別するための変数
	__int8 next_station = 1;
	
	// 次の駅の要素を保存する変数
	__int8 next_station_index = 0;

	while (true)
	{
		// テーブルに現在の駅を追加する
		yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[current_station_index];
		new_table_index++;

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		
		/////////////////// 次の駅が新宿なら
		next_station_index = current_station_index + next_station;
		// 次の駅が山手線DBの要素を超えたら0に戻す。
		if (next_station_index >= YAMANOTE_STATION_NUM) next_station_index = 0;

		// 次の駅が山手線DBの要素を下回ったら要素の最大に戻す
		else if (next_station_index < 0)next_station_index = YAMANOTE_INDEX_NUM;

		if (!strcmp(g_YamanoteDB[next_station_index].m_StationName, "新宿"))
		{
			for (int i = 0; i < CHUO_STATION_NUM; ++i)
			{
				// 中央線の神田まできたら
				if (!strcmp(g_ChuoLine[i].m_StationName, "神田"))
				{
					// 山手線の神田をテーブルに追加する
					yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// 現在の駅を神田に設定する
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// 中央線の駅を追加する
				yamanote_right_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}
			
			// 現在の駅を一時保存する
			__int8 temp_current_index = current_station_index;
			// 中央線を抜けたあと、右回りか左回りかを最短距離で決める
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index ++;

				// 現在の駅が山手線DBの要素を超えたら0に戻す。
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;

				// 乗車駅に来たら
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// 左回りに降車駅がある
					next_station = -1;

					// 現在の駅が山手線DBの要素を下回ったら要素の最大に戻す
					if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;
					break;
				}
				// 降車駅に来たら
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// 右回りに降車駅が
					next_station = 1;

					// 現在の駅が山手線DBの要素を超えたら0に戻す。
					if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
					break;
				}

			}
		}


		////////////// 次の駅が神田なら
		next_station_index = current_station_index + next_station;
		// 次の駅が山手線DBの要素を超えたら0に戻す。
		if (next_station_index >= YAMANOTE_STATION_NUM) next_station_index = 0;

		// 次の駅が山手線DBの要素を下回ったら要素の最大に戻す
		else if (next_station_index < 0)next_station_index = YAMANOTE_INDEX_NUM;

		if (!strcmp(g_YamanoteDB[next_station_index].m_StationName, "神田"))
		{
			for (int i = 3; i > 0; --i)
			{
				// 中央線の新宿まできたら
				if (!strcmp(g_ChuoLine[i].m_StationName, "新宿"))
				{
					// 山手線の新宿をテーブルに追加する
					yamanote_right_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// 現在の駅を新宿に設定する
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// 中央線の駅を追加する
				yamanote_right_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// 現在の駅を一時保存する
			__int8 temp_current_index = current_station_index;
			// 中央線を抜けたあと、右回りか左回りかを最短距離で決める
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index++;

				// 現在の駅が山手線DBの要素を超えたら0に戻す。
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;;

				// 乗車駅に来たら
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// 左回りに降車駅がある
					next_station = -1;

					// 現在の駅が山手線DBの要素を下回ったら要素の最大に戻す
					if (current_station_index < 0)current_station_index = YAMANOTE_STATION_NUM - 1;
					break;
				}
				// 降車駅に来たら
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// 右回りに降車駅が
					next_station = 1;

					// 現在の駅が山手線DBの要素を超えたら0に戻す。
					if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;
					break;
				}

			}
		}

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// 駅を進める
		current_station_index += next_station;

		// 現在の駅が山手線DBの要素を超えたら0に戻す。
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;

		// 現在の駅が山手線DBの要素を下回ったら要素の最大に戻す
		if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;

	}


	////////////////////////////////////// 中央線を利用した左回りのテーブルを作成 //////////////////////////////////////////

	// 現在の駅のインデックスを保持する変数
	current_station_index = entry_station_index;

	// 新しく作るテーブルの要素
	new_table_index = 0;

	// 次の駅が右か左なのかを保存する変数
	next_station = -1;
	// 次の駅の要素を保存する変数
	next_station_index = 0;

	while (true)
	{
		// テーブルに現在の駅を追加する
		yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[current_station_index];
		new_table_index++;

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;


		/////////////////// 次の駅が新宿なら
		next_station_index = current_station_index + next_station;
		// 次の駅が山手線DBの要素を超えたら0に戻す。
		if (next_station_index >= YAMANOTE_STATION_NUM) next_station_index = 0;

		// 次の駅が山手線DBの要素を下回ったら要素の最大に戻す
		else if (next_station_index < 0)next_station_index = YAMANOTE_INDEX_NUM;

		if (!strcmp(g_YamanoteDB[next_station_index].m_StationName, "新宿"))
		{
			for (int i = 0; i < CHUO_STATION_NUM; ++i)
			{
				// 中央線の神田まできたら
				if (!strcmp(g_ChuoLine[i].m_StationName, "神田"))
				{
					// 山手線の神田をテーブルに追加する
					yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// 現在の駅を神田に設定する
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// 中央線の駅を追加する
				yamanote_left_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// 現在の駅を一時保存する
			__int8 temp_current_index = current_station_index;
			// 中央線を抜けたあと、右回りか左回りかを最短距離で決める
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index++;

				// 現在の駅が山手線DBの要素を超えたら0に戻す。
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;

				// 乗車駅に来たら
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// 左回りに降車駅がある
					next_station = -1;
					break;
				}
				// 降車駅に来たら
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// 右回りに降車駅が
					next_station = 1;
					break;
				}

			}
		}


		////////////// 次の駅が神田なら
		next_station_index = current_station_index + next_station;
		// 次の駅が山手線DBの要素を超えたら0に戻す。
		if (next_station_index >= YAMANOTE_STATION_NUM) next_station_index = 0;

		// 次の駅が山手線DBの要素を下回ったら要素の最大に戻す
		else if (next_station_index < 0)next_station_index = YAMANOTE_INDEX_NUM;

		if (!strcmp(g_YamanoteDB[next_station_index].m_StationName, "神田"))
		{
			for (int i = CHUO_INDEX_NUM; i >= 0; --i)
			{
				// 中央線の新宿まできたら
				if (!strcmp(g_ChuoLine[i].m_StationName, "新宿"))
				{
					// 山手線の新宿をテーブルに追加する
					yamanote_left_through_chuo_table[new_table_index] = g_YamanoteDB[g_ChuoLine[i].m_StationId];
					new_table_index++;

					// 現在の駅を新宿に設定する
					current_station_index = g_ChuoLine[i].m_StationId;
					break;
				}

				// 中央線の駅を追加する
				yamanote_left_through_chuo_table[new_table_index] = g_ChuoLine[i];
				new_table_index++;
			}

			// 現在の駅を一時保存する
			__int8 temp_current_index = current_station_index;
			// 中央線を抜けたあと、右回りか左回りかを最短距離で決める
			for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
			{
				temp_current_index++;

				// 現在の駅が山手線DBの要素を超えたら0に戻す。
				if (temp_current_index >= YAMANOTE_STATION_NUM) temp_current_index = 0;;

				// 乗車駅に来たら
				if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, entry_station_name))
				{
					// 左回りに降車駅がある
					next_station = -1;
					break;
				}
				// 降車駅に来たら
				else if (!strcmp(g_YamanoteDB[temp_current_index].m_StationName, exit_station_name))
				{
					// 右回りに降車駅が
					next_station = 1;
					break;
				}

			}
		}

		// もし目的地ならテーブル作成終了
		if (!strcmp(g_YamanoteDB[current_station_index].m_StationName, exit_station_name)) break;

		// 駅を進める
		current_station_index += next_station;

		// 現在の駅が山手線DBの要素を超えたら0に戻す。
		if (current_station_index >= YAMANOTE_STATION_NUM) current_station_index = 0;

		// 現在の駅が山手線DBの要素を下回ったら要素の最大に戻す
		if (current_station_index < 0)current_station_index = YAMANOTE_INDEX_NUM;

	}



	////////////////////////////////////////////// 各テーブルにかかる時間を算出 /////////////////////////////////////////////////////
	__int8 short_distance = 127;
	char short_root[16]   = "\0";


	printf("\n------------------------------------ 右回り ---------------------------------------------\n\n");
	// 右回りの時間を算出
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// テーブルに駅がなくなったら終了
		if (!strcmp(yamanote_right_table[i].m_StationName, ""))break;

		// 現在の駅名を出力
		printf("%s -> ", yamanote_right_table[i].m_StationName);

		// 時間を足していく
		right_total_time += yamanote_right_table[i].m_NextStationCost;
	}

	if (right_total_time < short_distance) {
		short_distance = right_total_time;
		strcpy_s(short_root, 16, "右回り");
	}

	printf("\n右回りにかかる時間は %d です。\n", right_total_time);

	printf("\n-----------------------------------------------------------------------------------------\n");


	printf("\n------------------------------------ 左回り ---------------------------------------------\n\n");
	// 左回りの時間を出力
	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// テーブルに駅がなくなったら終了
		if (!strcmp(yamanote_left_table[i].m_StationName, ""))break;

		// 現在の駅名を出力
		printf("%s -> ", yamanote_left_table[i].m_StationName);

		// 始めの1ループ目は足さない
		if (i != 0)left_total_time += yamanote_left_table[i].m_NextStationCost;
	}

	if (left_total_time < short_distance) {
		short_distance = left_total_time;
		strcpy_s(short_root, 16, "左回り");
	}

	printf("\n左回りにかかる時間は %d です。\n", left_total_time);

	printf("\n-----------------------------------------------------------------------------------------\n");


	printf("\n------------------------------------ 右回り中央線 ---------------------------------------\n\n");
	// 右回りの中央線を通る時間
	for (int i = 0; i < YAMANOTE_STATION_NUM + CHUO_STATION_NUM; ++i)
	{
		// テーブルに駅がなくなったら終了
		if (!strcmp(yamanote_right_through_chuo_table[i].m_StationName, ""))break;

		// 現在の駅名を出力
		printf("%s -> ", yamanote_right_through_chuo_table[i].m_StationName);

		// 時間を足していく
		chuo_right_total_time += yamanote_right_through_chuo_table[i].m_NextStationCost;
	}

	if (chuo_right_total_time < short_distance) {
		short_distance = chuo_right_total_time;
		strcpy_s(short_root, 16,  "右回り中央線");
	}

	printf("\n右回り中央線にかかる時間は %d です。\n", chuo_right_total_time);

	printf("\n-----------------------------------------------------------------------------------------\n");


	printf("\n------------------------------------ 左回り中央線 ---------------------------------------\n\n");
	// 左回りの中央線を通る時間
	for (int i = 0; i < YAMANOTE_STATION_NUM + CHUO_STATION_NUM; ++i)
	{
		// テーブルに駅がなくなったら終了
		if (!strcmp(yamanote_left_through_chuo_table[i].m_StationName, ""))break;

		// 現在の駅名を出力
		printf("%s -> ", yamanote_left_through_chuo_table[i].m_StationName);

		// 時間を足していく
		chuo_left_total_time += yamanote_left_through_chuo_table[i].m_NextStationCost;
	}
	printf("\n左回り中央線にかかる時間は %d です。\n", chuo_left_total_time);

	if (chuo_left_total_time < short_distance) {
		short_distance = chuo_left_total_time;
		strcpy_s(short_root, 16, "左回り中央線");
	}

	printf("\n-----------------------------------------------------------------------------------------\n");


	// 最短ルートを表示
	printf("最短ルートは %s です。\n", short_root);


	return 0;
}
