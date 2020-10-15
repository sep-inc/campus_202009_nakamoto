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
/*　駒の描画に必要なリソースを返す関数   */
/*=======================================*/
const char* ShogiPieceGold::GetResouce(AttackTurn id_) const
{
	// 先手と後手によって返す文字列を変える
	switch (id_)
	{
	case AttackTurn::ATTACK_FIRST:
		return "金";
		break;
	case AttackTurn::ATTACK_SECOND:
		return "筋";
		break;
	case AttackTurn::ATTACK_NONE:
		return nullptr;
		break;
	default:
		break;
	}

	return nullptr;
}
