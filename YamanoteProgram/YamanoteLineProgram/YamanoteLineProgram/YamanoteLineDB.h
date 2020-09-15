﻿#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// 山手線の駅の数
#define YAMANOTE_STATION_NUM	29

// 駅の名前の最大文字数
#define MAX_STATION_NAME_LENGTH 32


// 駅構造体
struct Station
{
	// 駅名
	char m_StationName[MAX_STATION_NAME_LENGTH];

	// 次の駅までのコスト 単位 -> 分
	__int8 m_NectStationCost;
};


// 山手線DB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	{"駒込",		2},
	{"田端",		2},
	{"西日暮里",	1},
	{"日暮里",		2},
	{"鶯谷",		2},
	{"上野",		2},
	{"御徒町",		2},
	{"秋葉原",		2},
	{"神田",		1},
	{"東京",		2},
	{"有楽町",		2},
	{"新橋",		2},
	{"浜松町",		2},
	{"田町",		2},
	{"品川",		3},
	{"大崎",		2},
	{"五反田",		2},
	{"目黒",		3},
	{"恵比寿",		2},
	{"渋谷",		2},
	{"原宿",		2},
	{"代々木",		2},
	{"新宿",		2},
	{"新大久保",	2},
	{"高田馬場",	2},
	{"目白",		3},
	{"池袋",		2},
	{"大塚",		2},
	{"巣鴨",		2}
};


#endif