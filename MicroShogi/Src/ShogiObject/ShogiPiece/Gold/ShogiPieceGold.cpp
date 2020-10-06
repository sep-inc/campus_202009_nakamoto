#include "ShogiPieceGold.h"
#include <string.h>

const bool ShogiPieceGold::m_MovableRangeDB[4][3] = {
	{0,0,0},
	{1,1,1},
	{1,0,1},
	{0,1,0},
};

ShogiPieceGold::ShogiPieceGold()
{
	memcpy(m_MovableRange, m_MovableRangeDB, sizeof(m_MovableRangeDB));
}


/*=======================================*/
/*�@��̕`��ɕK�v�ȃ��\�[�X��Ԃ��֐�   */
/*=======================================*/
const char* ShogiPieceGold::GetResouce(MoveTrun id_) const
{
	// ���ƌ��ɂ���ĕԂ��������ς���
	switch (id_)
	{
	case MoveTrun::MOVE_FIRST:
		return "��";
		break;
	case MoveTrun::MOVE_SECOND:
		return "��";
		break;
	case MoveTrun::MOVE_NON:
		return nullptr;
		break;
	default:
		break;
	}
}
