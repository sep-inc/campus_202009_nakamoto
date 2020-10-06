#include "ShogiPieceKing.h"
#include <string.h>

const bool ShogiPieceKing::m_MovableRange[4][3] = {
	{0,0,0},
	{1,1,1},
	{1,0,1},
	{1,1,1},
};

ShogiPieceKing::ShogiPieceKing()
{
	memcpy(ShogiPieceBase::m_MovableRange, this->m_MovableRange, sizeof(this->m_MovableRange));
}


/*=======================================*/
/*�@��̕`��ɕK�v�ȃ��\�[�X��Ԃ��֐�   */
/*=======================================*/
const char* ShogiPieceKing::GetResouce(MoveTrun id_) const
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
