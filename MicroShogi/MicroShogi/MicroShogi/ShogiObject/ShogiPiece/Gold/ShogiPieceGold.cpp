#include "ShogiPieceGold.h"

const bool ShogiPieceGold::m_MovableRange[3][3] = {
	{1,1,1},
	{1,0,1},
	{0,1,0},
};

/*===================================*/
/*�@�ړ��\���ǂ����𔻒肷��֐�   */
/*===================================*/
bool ShogiPieceGold::IsAbleMove(IVec2 moveVec_) const
{
	// �ړ��\�͈͂𒴂��Ă�����ړ��ł��Ȃ�
	if (moveVec_.m_X > 1 || moveVec_.m_X < -1) { return false; }
	if (moveVec_.m_Y > 1 || moveVec_.m_Y < -1) { return false; }

	return ShogiPieceGold::m_MovableRange[1 + moveVec_.m_Y][1 + moveVec_.m_X];
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
