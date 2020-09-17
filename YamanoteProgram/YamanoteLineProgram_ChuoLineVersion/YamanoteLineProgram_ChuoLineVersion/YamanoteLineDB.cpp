#include "YamanoteLineDB.h"

#define YAMANOTE_AROUND_TIME 59

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


// 左右のどちらに進むのかを決める関数
// entry_に出発地、exit_に目的地を引数に入れる
// 戻り値 1が右 -1が左
int WhichWay(__int8 entryId_, __int8 exitId_)
{
	if (entryId_ == exitId_) return 1;

	__int8 right_cost = 0;
	__int8 left_const = 0;
	__int8 index = entryId_;

	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// もし現在の駅と目的地が同じになったら終了
		if (g_YamanoteDB[index].m_StationId == g_YamanoteDB[exitId_].m_StationId) break;

		right_cost += g_YamanoteDB[index].m_NextStationCost;

		index++;
		// 現在の駅が山手線DBの要素を以上になったら0に戻す。
		if (index >= YAMANOTE_STATION_NUM) index = 0;
	}

	// 全体から右向きにかかる時間を引いて左向きにかかる時間を算出する
	left_const = YAMANOTE_AROUND_TIME - right_cost;
	

	return right_cost < left_const ? 1 : -1;
}