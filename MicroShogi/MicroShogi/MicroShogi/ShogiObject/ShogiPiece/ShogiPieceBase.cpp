#include "ShogiPieceBase.h"

/*===================================*/
/*@ˆÚ“®‰Â”\‚©‚Ç‚¤‚©‚ð”»’è‚·‚éŠÖ”   */
/*===================================*/
bool ShogiPieceBase::IsAbleMove(IVec2 moveVec_) const
{
	// ˆÚ“®‰Â”\”ÍˆÍ‚ð’´‚¦‚Ä‚¢‚½‚çˆÚ“®‚Å‚«‚È‚¢
	if (moveVec_.m_X > 1 || moveVec_.m_X < -1) { return false; }
	if (moveVec_.m_Y > 1 || moveVec_.m_Y < -2) { return false; }

	return this->m_MovableRange[2 + moveVec_.m_Y][1 + moveVec_.m_X];
}