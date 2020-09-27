#include "YamanoteLineDB.h"

#define YAMANOTE_AROUND_TIME 59

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


// ���E�̂ǂ���ɐi�ނ̂������߂�֐�
// entry_�ɏo���n�Aexit_�ɖړI�n�������ɓ����
// �߂�l 1���E -1����
int WhichWay(__int8 entryId_, __int8 exitId_)
{
	if (entryId_ == exitId_) return 1;

	__int8 right_cost = 0;
	__int8 left_const = 0;
	__int8 index = entryId_;

	for (int i = 0; i < YAMANOTE_STATION_NUM; ++i)
	{
		// �������݂̉w�ƖړI�n�������ɂȂ�����I��
		if (g_YamanoteDB[index].m_StationId == g_YamanoteDB[exitId_].m_StationId) break;

		right_cost += g_YamanoteDB[index].m_NextStationCost;

		index++;
		// ���݂̉w���R���DB�̗v�f���ȏ�ɂȂ�����0�ɖ߂��B
		if (index >= YAMANOTE_STATION_NUM) index = 0;
	}

	// �S�̂���E�����ɂ����鎞�Ԃ������č������ɂ����鎞�Ԃ��Z�o����
	left_const = YAMANOTE_AROUND_TIME - right_cost;
	

	return right_cost < left_const ? 1 : -1;
}