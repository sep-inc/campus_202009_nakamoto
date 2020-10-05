#include "ShogiPiecePawn.h"

const bool ShogiPiecePawn::m_MovableRange[3][3] = {
	{0,1,0},
	{0,0,0},
	{0,0,0},
};

/*===================================*/
/*　移動可能かどうかを判定する関数   */
/*===================================*/
bool ShogiPiecePawn::IsAbleMove(IVec2 moveVec_) const
{
	// 移動可能範囲を超えていたら移動できない
	if (moveVec_.m_X > 1 || moveVec_.m_X < -1) { return false; }
	if (moveVec_.m_Y > 1 || moveVec_.m_Y < -1) { return false; }

	return ShogiPiecePawn::m_MovableRange[1 + moveVec_.m_Y][1 + moveVec_.m_X];
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
