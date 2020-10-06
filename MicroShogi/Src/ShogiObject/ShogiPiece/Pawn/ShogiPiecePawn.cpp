﻿#include "ShogiPiecePawn.h"
#include <string.h>

const bool ShogiPiecePawn::m_MovableRangeDB[4][3] = {
	{0,0,0},
	{0,1,0},
	{0,0,0},
	{0,0,0},
};

ShogiPiecePawn::ShogiPiecePawn()
{
	memcpy(m_MovableRange, m_MovableRangeDB, sizeof(m_MovableRangeDB));
}


/*=======================================*/
/*　駒の描画に必要なリソースを返す関数   */
/*=======================================*/
const char* ShogiPiecePawn::GetResouce(MoveTrun id_) const
{
	// 先手と後手によって返す文字列を変える
	switch (id_)
	{
	case MoveTrun::MOVE_FIRST:
		return "歩";
		break;
	case MoveTrun::MOVE_SECOND:
		return "ふ";
		break;
	case MoveTrun::MOVE_NON:
		return nullptr;
		break;
	default:
		break;
	}
}
