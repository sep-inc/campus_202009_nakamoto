﻿#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// 山手線の駅の数
#define YAMANOTE_STATION_NUM	29

// 中央線の要素数
#define YAMANOTE_INDEX_NUM     (YAMANOTE_STATION_NUM - 1)

// 中央線の駅の数
#define CHUO_STATION_NUM        4

// 中央線の要素数
#define CHUO_INDEX_NUM			(CHUO_STATION_NUM - 1)

// 駅の名前の最大文字数
#define MAX_STATION_NAME_LENGTH 32

/*
	駅構造体
*/
struct Station
{
	// 駅のID
	__int8 m_StationId;

	// 駅名
	char   m_StationName[MAX_STATION_NAME_LENGTH];

	// 次の駅(配列)までの距離, 単位 -> 分

	__int8 m_NextStationCost;
};

// 山手線DB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	//	ID		駅名	    右の駅との距離(配列でいう次の要素)
		{0,		"駒込",			2},
		{1,		"田端",			2},
		{2,		"西日暮里",		1},
		{3,		"日暮里",	    2},
		{4,		"鶯谷",			2},
		{5,		"上野",			2},
		{6,		"御徒町",	    2},
		{7,		"秋葉原",	    2},
		{8,		"神田",			1},
		{9,		"東京",			2},
		{10,	"有楽町",	    2},
		{11,	"新橋",			2},
		{12,	"浜松町",	    2},
		{13,	"田町",			2},
		{14,	"品川",			3},
		{15,	"大崎",			2},
		{16,	"五反田",	    2},
		{17,	"目黒",			3},
		{18,	"恵比寿",	    2},
		{19,	"渋谷",			2},
		{20,	"原宿",			2},
		{21,	"代々木",	    2},
		{22,	"新宿",			2},
		{23,	"新大久保",		2},
		{24,	"高田馬場",		2},
		{25,	"目白",			3},
		{26,	"池袋",			2},
		{27,	"大塚",			2},
		{28,	"巣鴨",			2},
};


// 中央線DB
const Station g_ChuoLine[CHUO_STATION_NUM] =
{
	//	ID		駅名	     右の駅との距離(配列でいう次の要素)
		{22,	"新宿",			4},
		{29,	"四ツ谷",		5},
		{30,	"御茶ノ水",		2},
		{8,		"神田",			2},
};

#endif