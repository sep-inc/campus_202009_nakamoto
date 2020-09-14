#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// Rθό‚Μ‰w‚Μ”
#define YAMANOTE_STATION_NUM	29

// ’†‰›ό‚Μ—v‘f”
#define YAMANOTE_INDEX_NUM     (YAMANOTE_STATION_NUM - 1)

// ’†‰›ό‚Μ‰w‚Μ”
#define CHUO_STATION_NUM        4

// ’†‰›ό‚Μ—v‘f”
#define CHUO_INDEX_NUM			(CHUO_STATION_NUM - 1)

// ‰w‚Μ–Ό‘O‚ΜΕ‘ε•¶”
#define MAX_STATION_NAME_LENGTH 32

/*
	‰w\‘Ά‘Μ
*/
struct Station
{
	// ‰w‚ΜID
	__int8 m_StationId;

	// ‰w–Ό
	char   m_StationName[MAX_STATION_NAME_LENGTH];

	// ‚Μ‰w(”z—ρ)‚ά‚Ε‚Μ‹——£, ’PΚ -> •ª

	__int8 m_NextStationCost;
};

// RθόDB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	//	ID		‰w–Ό	    ‰E‚Μ‰w‚Ζ‚Μ‹——£(”z—ρ‚Ε‚Ά‚¤‚Μ—v‘f)
		{0,		"‹ξ",			2},
		{1,		"“c’[",			2},
		{2,		"Ό“ϊ•ι—Ά",		1},
		{3,		"“ϊ•ι—Ά",	    2},
		{4,		"ις’J",			2},
		{5,		"γ–μ",			2},
		{6,		"δ“k’¬",	    2},
		{7,		"H—t΄",	    2},
		{8,		"_“c",			1},
		{9,		"“‹",			2},
		{10,	"—Ly’¬",	    2},
		{11,	"V‹΄",			2},
		{12,	"•lΌ’¬",	    2},
		{13,	"“c’¬",			2},
		{14,	"•iμ",			3},
		{15,	"‘εθ",			2},
		{16,	"ά”½“c",	    2},
		{17,	"–Ϊ•",			3},
		{18,	"b”δυ",	    2},
		{19,	"a’J",			2},
		{20,	"΄h",			2},
		{21,	"‘γX–Ψ",	    2},
		{22,	"Vh",			2},
		{23,	"V‘ε‹v•Ϋ",		2},
		{24,	"‚“c”nκ",		2},
		{25,	"–Ϊ”’",			3},
		{26,	"’r‘ά",			2},
		{27,	"‘ε’Λ",			2},
		{28,	"‘ƒ›",			2},
};


// ’†‰›όDB
const Station g_ChuoLine[CHUO_STATION_NUM] =
{
	//	ID		‰w–Ό	     ‰E‚Μ‰w‚Ζ‚Μ‹——£(”z—ρ‚Ε‚Ά‚¤‚Μ—v‘f)
		{22,	"Vh",			4},
		{29,	"lƒc’J",		5},
		{30,	"δ’ƒƒm…",		2},
		{8,		"_“c",			2},
};

#endif