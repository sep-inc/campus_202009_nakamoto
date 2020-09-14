#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// �R����̉w�̐�
#define YAMANOTE_STATION_NUM	29

// �������̗v�f��
#define YAMANOTE_INDEX_NUM     (YAMANOTE_STATION_NUM - 1)

// �������̉w�̐�
#define CHUO_STATION_NUM        4

// �������̗v�f��
#define CHUO_INDEX_NUM			(CHUO_STATION_NUM - 1)

// �w�̖��O�̍ő啶����
#define MAX_STATION_NAME_LENGTH 32

/*
	�w�\����
*/
struct Station
{
	// �w��ID
	__int8 m_StationId;

	// �w��
	char   m_StationName[MAX_STATION_NAME_LENGTH];

	// ���̉w(�z��)�܂ł̋���, �P�� -> ��

	__int8 m_NextStationCost;
};

// �R���DB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	//	ID		�w��	    �E�̉w�Ƃ̋���(�z��ł������̗v�f)
		{0,		"�",			2},
		{1,		"�c�[",			2},
		{2,		"�����闢",		1},
		{3,		"���闢",	    2},
		{4,		"��J",			2},
		{5,		"���",			2},
		{6,		"��k��",	    2},
		{7,		"�H�t��",	    2},
		{8,		"�_�c",			1},
		{9,		"����",			2},
		{10,	"�L�y��",	    2},
		{11,	"�V��",			2},
		{12,	"�l����",	    2},
		{13,	"�c��",			2},
		{14,	"�i��",			3},
		{15,	"���",			2},
		{16,	"�ܔ��c",	    2},
		{17,	"�ڍ�",			3},
		{18,	"�b���",	    2},
		{19,	"�a�J",			2},
		{20,	"���h",			2},
		{21,	"��X��",	    2},
		{22,	"�V�h",			2},
		{23,	"�V��v��",		2},
		{24,	"���c�n��",		2},
		{25,	"�ڔ�",			3},
		{26,	"�r��",			2},
		{27,	"���",			2},
		{28,	"����",			2},
};


// ������DB
const Station g_ChuoLine[CHUO_STATION_NUM] =
{
	//	ID		�w��	     �E�̉w�Ƃ̋���(�z��ł������̗v�f)
		{22,	"�V�h",			4},
		{29,	"�l�c�J",		5},
		{30,	"�䒃�m��",		2},
		{8,		"�_�c",			2},
};

#endif