#ifndef YAMANOTELINEDB_H_
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
extern const Station g_YamanoteDB[YAMANOTE_STATION_NUM];


#endif