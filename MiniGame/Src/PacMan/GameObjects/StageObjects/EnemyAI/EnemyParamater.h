#ifndef ENEMY_ENEMY_PARAMETER_H_
#define ENEMY_ENEMY_PARAMETER_H_

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
};

struct EnemyParameter
{
	// �G�l�~�[�̍X�V���x
	int m_Speed;

	// ���݂̈ړ�������ۑ�����ϐ�
	IVec2 m_Direction;

	// �G�l�~�[�̐��i
	EnemyPersonalityList m_Personality;
};

#endif