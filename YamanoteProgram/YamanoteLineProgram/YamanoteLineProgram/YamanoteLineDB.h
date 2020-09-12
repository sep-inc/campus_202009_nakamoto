#ifndef YAMANOTELINEDB_H_
#define YAMANOTELINEDB_H_

// �R����̉w�̐�
#define YAMANOTE_STATION_NUM	29

// �w�̖��O�̍ő啶����
#define MAX_STATION_NAME_LENGTH 32


// �w�\����
struct Station
{
	// �w��
	char m_StationName[MAX_STATION_NAME_LENGTH];

	// ���̉w�܂ł̃R�X�g �P�� -> ��
	__int8 m_NectStationCost;
};


// �R���DB
const Station g_YamanoteDB[YAMANOTE_STATION_NUM] =
{
	{"�",		2},
	{"�c�[",		2},
	{"�����闢",	1},
	{"���闢",		2},
	{"��J",		2},
	{"���",		2},
	{"��k��",		2},
	{"�H�t��",		2},
	{"�_�c",		1},
	{"����",		2},
	{"�L�y��",		2},
	{"�V��",		2},
	{"�l����",		2},
	{"�c��",		2},
	{"�i��",		3},
	{"���",		2},
	{"�ܔ��c",		2},
	{"�ڍ�",		3},
	{"�b���",		2},
	{"�a�J",		2},
	{"���h",		2},
	{"��X��",		2},
	{"�V�h",		2},
	{"�V��v��",	2},
	{"���c�n��",	2},
	{"�ڔ�",		3},
	{"�r��",		2},
	{"���",		2},
	{"����",		2}
};


#endif