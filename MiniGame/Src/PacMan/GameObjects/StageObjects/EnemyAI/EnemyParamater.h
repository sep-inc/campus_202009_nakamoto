#ifndef ENEMY_ENEMY_PARAMETER_H_
#define ENEMY_ENEMY_PARAMETER_H_

#include "../../../../Utility/IVec2.h"
#include <vector>

enum class EnemyPersonalityList
{
	PERSONALITY_A,
	PERSONALITY_B,
	PERSONALITY_C,
};

enum class ActionStateList
{
	ACTION_SAUNTERING,	// �p�j
	ACTION_DEFEND,		// �A�C�e�������
	ACTION_CHASE,		// �ǂ�������

	ACTION_NUM,
};

struct EnemyParameter
{
	// �G�l�~�[�̍X�V���x
	int m_Speed;

	// ���݂̈ړ�������ۑ�����ϐ�
	IVec2 m_Direction;

	// �G�l�~�[�̐��i
	EnemyPersonalityList m_Personality;

	std::vector<IVec2> m_TraceList;
};

#endif