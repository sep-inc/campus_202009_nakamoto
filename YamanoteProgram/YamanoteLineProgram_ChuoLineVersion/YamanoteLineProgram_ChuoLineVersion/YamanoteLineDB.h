#ifndef YAMANOTELINEDB_H_
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
extern const Station g_YamanoteDB[YAMANOTE_STATION_NUM];

// 中央線DB
extern const Station g_ChuoLine[CHUO_STATION_NUM];


// 左右のどちらに進むのかを決める関数
// entry_に出発地、exit_に目的地を引数に入れる
// 戻り値 1が右 -1が左
int WhichWay(__int8 entryId_, __int8 exitId_);

#endif