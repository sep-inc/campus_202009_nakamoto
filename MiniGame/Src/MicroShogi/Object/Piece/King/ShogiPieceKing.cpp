#include "ShogiPieceKing.h"
#include <string.h>

const bool ShogiPieceKing::m_MovableRangeDB[4][3] = {
	{0,0,0},
	{1,1,1},
	{1,0,1},
	{1,1,1},
};

ShogiPieceKing::ShogiPieceKing()
{
	memcpy(m_MovableRange, m_MovableRangeDB, sizeof(m_MovableRangeDB));
}


/*=======================================*/
/*　駒の描画に必要なリソースを返す関数   */
/*=======================================*/
const char* ShogiPieceKing::GetResouce(AttackTurn id_) const
{
	// 先手と後手によって返す文字列を変える
	switch (id_)
	{
	case AttackTurn::ATTACK_FIRST:
		return "王";
		break;
	case AttackTurn::ATTACK_SECOND:
		return "玉";
		break;
	case AttackTurn::ATTACK_NONE:
		return nullptr;
		break;
	default:
		break;
	}

	return nullptr;
}
