#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// RθόΜwΜ
#define YAMANOTE_STATION_NUM	29

// wΜΌOΜΕεΆ
#define MAX_STATION_NAME_LENGTH 32


// w\’Μ
struct Station
{
	// wΌ
	char m_StationName[MAX_STATION_NAME_LENGTH];

	// ΜwάΕΜRXg PΚ -> ͺ
	__int8 m_NectStationCost;
};


// RθόDB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	{"ξ",		2},
	{"c[",		2},
	{"Όϊι’",	1},
	{"ϊι’",		2},
	{"ιςJ",		2},
	{"γμ",		2},
	{"δk¬",		2},
	{"Ht΄",		2},
	{"_c",		1},
	{"",		2},
	{"Ly¬",		2},
	{"V΄",		2},
	{"lΌ¬",		2},
	{"c¬",		2},
	{"iμ",		3},
	{"εθ",		2},
	{"ά½c",		2},
	{"Ϊ",		3},
	{"bδυ",		2},
	{"aJ",		2},
	{"΄h",		2},
	{"γXΨ",		2},
	{"Vh",		2},
	{"VεvΫ",	2},
	{"cnκ",	2},
	{"Ϊ",		3},
	{"rά",		2},
	{"εΛ",		2},
	{"",		2}
};


#endif