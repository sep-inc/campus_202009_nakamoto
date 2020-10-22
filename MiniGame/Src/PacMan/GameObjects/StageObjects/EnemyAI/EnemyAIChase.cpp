#include "EnemyAIChase.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIChase::EnemyAIChase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ , enemyParam_ ,stage_ }
{
}

ActionStateList PacMan::EnemyAIChase::Update()
{
	// �������i��A��C�Ȃ�v���C���[�Ɍ������Đi�ށA
	if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_A || m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_C)
	{
		// ��������������A�N�V������p�j�ɂ���
		if (Chase() == false) return ActionStateList::ACTION_SAUNTERING;
	}
	// �������i��B�Ȃ���ǂ�ōs������
	else if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_B) {
		// ���t���[���ŃA�N�V������p�j�ɂ���
		if (Forestall() == false) return ActionStateList::ACTION_SAUNTERING;

	}
	
	// �G���܂��������Ă��Ȃ��̂ŁA�ǂ��������Ԃ̂܂�
	return ActionStateList::ACTION_CHASE;
}

/*
	����Œǂ�������
*/
bool PacMan::EnemyAIChase::Forestall()
{
	// �����v���C���[�������ꍇ,�ǂ�������
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {

		// �����v���C���[���������ꍇ�ǐՃ��X�g���N���A����
		m_EnemyParam->m_TraceList.clear();
		// �v���C���[�̈ʒu��ۑ����Ă���
		m_PlayerOldPos = player_pos;

		// �v���C���[�̕������Z�o����
		IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
		if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
		if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

		m_EnemyParam->m_Direction = enemy_to_player_vec;
		return true;
	}
	// �v���C���[��������Ȃ������ꍇ����O�̃t���[���ł��������ĂȂ�������A���������̂�false��Ԃ�
	else if (m_PlayerOldPos.m_X == -1 || m_PlayerOldPos.m_Y == -1) return false;
	// �v���C���[��������Ȃ��������A�O�̃t���[���Ńv���C���[�������Ă����ꍇ
	else {
		
		// �����ǐՃ��X�g���Ȃ��Ȃ�܂ňړ�����
		if (!m_EnemyParam->m_TraceList.empty()) {
			m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
			m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
			return true;
		}

		// �����A����������A�v���C���[�̈ړ�������������������

		// �v���C���[�����������ʒu����A������Ƀv���C���[�����݂��邩�𒲂ׂ�
		// �������Ȃ������猩�������̂�false��Ԃ�
		if (FoundPlayer(&m_PlayerOldPos, m_RefStage, 11, &player_pos) == false) { return false; }


		// �����ꍇ�ړ��ł�������������ɂȂ�܂ňړ����������\������
		while (true)
		{
			// �v���C���[�̈ړ������������Z�o����
			IVec2 player_vec = player_pos - m_PlayerOldPos;
			if (player_vec.m_X != 0)player_vec.m_X /= Calc::Abs(player_vec.m_X);
			if (player_vec.m_Y != 0)player_vec.m_Y /= Calc::Abs(player_vec.m_Y);

			// �v���C���[�̈ړ����������ɑ΂��āA�������̃x�N�g�����Z�o����
			IVec2 left_direction{ player_vec.m_Y, -player_vec.m_X };



			// �v���C���[�̈ړ��\�ȕ����̐���ۑ�����ϐ�
			int able_move_num = 0;

			// �v���C���[�̎��Ɉړ�����ł��낤���W��ۑ�����ϐ�
			IVec2 player_next_pos;

			// �v���C���[�̎��Ɉړ�����ł��낤�ړ��x�N�g����ۑ�����ϐ�
			IVec2 move_vec;

			// �O�����Ɉړ��ł��邩�𒲂ׂ�
			player_next_pos = player_pos + player_vec;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				
				// �ړ��ł���ꍇ���̃x�N�g����ۑ�����
				move_vec = player_next_pos - player_pos;

				// �ړ��\���𑫂�
				able_move_num++;
			}

			// �������Ɉړ��ł��邩�𒲂ׂ�
			player_next_pos = player_pos + left_direction;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				// �ړ��ł��鐔��1�ȏ�Ȃ�break
				if (able_move_num >= 1)break;

				// �ړ��ł���ꍇ���̃x�N�g����ۑ�����
				move_vec = player_next_pos - player_pos;

				// �ړ��\���𑫂�
				able_move_num++;
			}

			// �����Ă�������ɑ΂��ĉE�ɂ����߂邩
			player_next_pos = player_pos - left_direction;
			if (m_RefStage->GetStageObject(player_next_pos) != ObjectType::TYPE_WALL) {
				// �ړ��ł��鐔��1�ȏ�Ȃ�break
				if (able_move_num >= 1)break;
				
				// �ړ��ł���ꍇ���̃x�N�g����ۑ�����
				move_vec = player_next_pos - player_pos;

				// �ړ��\���𑫂�
				able_move_num++;
			}

			// �ʒu���X�V����
			m_PlayerOldPos = player_pos;
			player_pos = player_pos + move_vec;
		}

		// �v���C���[�̈ړ�����ł��낤�ꏊ�ɍŒZ�o�H�ňړ�����
		m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, player_pos);

		
		if (m_EnemyParam->m_TraceList.empty())return false;
		
		// �ړ����������ۑ�����
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
	}

	return true;
}

/*
	�ǂ�������
*/
bool PacMan::EnemyAIChase::Chase()
{
	// �����ǐՃ��X�g���Ȃ��Ȃ�܂ňړ�����
	if (!m_EnemyParam->m_TraceList.empty()) {
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
		return true;
	}

	IVec2 player_pos;

	// ���g�̈ʒu����4�����̒�����Ƀv���C���[�����邩�𒲂ׂ�
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == false) return false;

	// �����ꍇ�A�G�ƃv���C���[�̃x�N�g�����Z�o����
	IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
	// �x�N�g����P�ʉ�����
	if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
	if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

	// ���Ɉړ�����������v���C���[�̕����ɃZ�b�g����
	m_EnemyParam->m_Direction = enemy_to_player_vec;
	return true;
}

void PacMan::EnemyAIChase::Init()
{
	m_PlayerOldPos.m_X = -1;
	m_PlayerOldPos.m_Y = -1;
}
