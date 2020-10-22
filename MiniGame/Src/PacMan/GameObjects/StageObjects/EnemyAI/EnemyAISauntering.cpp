#include "EnemyAISauntering.h"
#include "../../../../Utility/Calc.h"
#include <stdio.h>
#include <stdlib.h>

PacMan::EnemyAISauntering::EnemyAISauntering(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_,enemyParam_ , stage_ }, m_CurrentItemTotalNum{ 0 }
{
}

ActionStateList PacMan::EnemyAISauntering::Update()
{
	// �����v���C���[�������ꍇ�A���ɍs���s����ǂ�������ɂ���
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {
		IVec2 enemy_to_player_vec;
		enemy_to_player_vec = player_pos - *m_RefEnemyPos;
		if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
		if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);
		
		m_EnemyParam->m_Direction = enemy_to_player_vec;
		return ActionStateList::ACTION_CHASE;
	}

	// �ړ������������_���Ɍ��߂�
	std::vector<IVec2> able_direction = GetAbleMoveDirection();
	m_EnemyParam->m_Direction = able_direction[rand() % able_direction.size()];


	// �������i������̎��A�v���C���[���A�C�e�����Ƃ����ꍇ�A���̍s�������ɂ���
	if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_C) {

		int current_item_num = m_RefStage->ItemTotalNum();

		if (current_item_num != m_CurrentItemTotalNum) {

			m_CurrentItemTotalNum = current_item_num;
			return ActionStateList::ACTION_DEFEND;
		}
	}


	return ActionStateList::ACTION_SAUNTERING;
}

void PacMan::EnemyAISauntering::Init()
{
	// ���݂̃A�C�e���̐���ۑ�����
	m_CurrentItemTotalNum = m_RefStage->ItemTotalNum();
}


std::vector<IVec2> PacMan::EnemyAISauntering::GetAbleMoveDirection()
{
	std::vector<IVec2> ret_vec;

	// �[���x�N�g����������ړ��ł�������������_���ɑI��
	if (m_EnemyParam->m_Direction.Zero() == true)
	{
		
		IVec2 direction[4] = {
			{m_RefEnemyPos->m_X + 1, m_RefEnemyPos->m_Y},
			{m_RefEnemyPos->m_X - 1, m_RefEnemyPos->m_Y},
			{m_RefEnemyPos->m_X, m_RefEnemyPos->m_Y + 1},
			{m_RefEnemyPos->m_X, m_RefEnemyPos->m_Y - 1},
		};

		// �l�����ňړ��ł���ꏊ������Ό��ɒǉ�
		for (int i = 0; i < 4; ++i) {
			if (m_RefStage->GetStageObject(direction[i]) != ObjectType::TYPE_WALL)
			{
				ret_vec.push_back(direction[i] - *m_RefEnemyPos);
			}
		}
	}
	else {

		// �O�ƍ��ƉE�ɂ��ꂼ��ړ��ł��邩���׈ړ��ł���Ȃ���ɒǉ�
		IVec2 left_direction{ m_EnemyParam->m_Direction.m_Y, -m_EnemyParam->m_Direction.m_X };
		if (m_RefStage->GetStageObject(*m_RefEnemyPos + m_EnemyParam->m_Direction) != ObjectType::TYPE_WALL)   ret_vec.push_back(*m_RefEnemyPos + m_EnemyParam->m_Direction - *m_RefEnemyPos);
		if (m_RefStage->GetStageObject(*m_RefEnemyPos + left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*m_RefEnemyPos + left_direction - *m_RefEnemyPos);
		if (m_RefStage->GetStageObject(*m_RefEnemyPos - left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*m_RefEnemyPos - left_direction - *m_RefEnemyPos);
	}

	// �ǉ����I�������ʂ�Ԃ�
	return ret_vec;
}