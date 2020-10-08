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
const char* ShogiPieceGold::GetResouce(AttackTurn id_) const
{
	// ���ƌ��ɂ���ĕԂ��������ς���
	switch (id_)
	{
	case AttackTurn::ATTACK_FIRST:
		return "��";
		break;
	case AttackTurn::ATTACK_SECOND:
		return "��";
		break;
	case AttackTurn::ATTACK_NONE:
		return nullptr;
		break;
	default:
		break;
	}

	return nullptr;
}
