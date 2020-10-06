#include "ShogiPieceGold.h"
#include <string.h>

const bool ShogiPieceGold::m_MovableRange[4][3] = {
	{0,0,0},
	{1,1,1},
	{1,0,1},
	{0,1,0},
};

ShogiPieceGold::ShogiPieceGold()
{
	memcpy(ShogiPieceBase::m_MovableRange, this->m_MovableRange, sizeof(this->m_MovableRange));
}


/*=======================================*/
/*　駒の描画に必要なリソースを返す関数   */
/*=======================================*/
const char* ShogiPieceGold::GetResouce(MoveTrun id_) const
{
	// 先手と後手によって返す文字列を変える
	switch (id_)
	{
	case MoveTrun::MOVE_FIRST:
		return "金";
		break;
	case MoveTrun::MOVE_SECOND:
		return "筋";
		break;
	case MoveTrun::MOVE_NON:
		return nullptr;
		break;
	default:
		break;
	}
}
