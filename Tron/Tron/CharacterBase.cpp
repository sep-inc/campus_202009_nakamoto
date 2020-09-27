#include "CharacterBase.h"

void CharacterBase::Move()
{
	switch (m_Direction)
	{
	case Direction::DIRECTION_UP:
		m_PosY--;
		break;
	case Direction::DIRECTION_DOWN:
		m_PosY++;
		break;
	case Direction::DIRECTION_LEFT:
		m_PosX--;
		break;
	case Direction::DIRECTION_RIGHT:
		m_PosX++;
		break;
	default:
		break;
	}
}

void CharacterBase::SendToStage()
{
	m_RefStage->SetStage(m_PosX, m_PosY, m_Type);
}
