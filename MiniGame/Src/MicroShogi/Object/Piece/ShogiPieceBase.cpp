#include "ShogiPieceBase.h"

ShogiPieceBase::ShogiPieceBase() :
	m_MovableRange{ false }
{}

/*===================================*/
/*　移動可能かどうかを判定する関数   */
/*===================================*/
bool ShogiPieceBase::IsAbleMove(IVec2 moveVec_) const
{
	// 移動可能範囲を超えていたら移動できない
	if (moveVec_.m_X > 1 || moveVec_.m_X < -1) { return false; }
	if (moveVec_.m_Y > 1 || moveVec_.m_Y < -2) { return false; }

	return m_MovableRange[2 + moveVec_.m_Y][1 + moveVec_.m_X];
}