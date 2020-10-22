#include "EnemyAIDefend.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIDeffend::EnemyAIDeffend(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ ,enemyParam_, stage_ }
{
}


ActionStateList PacMan::EnemyAIDeffend::Update()
{
	// �����v���C���[�������ꍇ�A���ɍs���s����ǂ�������ɂ���
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {
		IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
		
		if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
		if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

		m_EnemyParam->m_Direction = enemy_to_player_vec;
		m_EnemyParam->m_TraceList.clear();
		
		return ActionStateList::ACTION_CHASE;
	}

	// �A�C�e���̈ʒu�܂œ���������p�j�ɑJ��	
	if (HeadForItemPosition() == true) {
		return ActionStateList::ACTION_SAUNTERING;
	}

	return ActionStateList::ACTION_DEFEND;
}


bool PacMan::EnemyAIDeffend::HeadForItemPosition()
{
	// �����ǐՃ��X�g���Ȃ��Ȃ�܂ňړ�����
	if (!m_EnemyParam->m_TraceList.empty()) {
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
		
		// �ړ���ǐՃ��X�g���Ȃ������ꍇ�A���������̂ŁAtrue��Ԃ�
		if (m_EnemyParam->m_TraceList.empty()) {
			return true;
		}
		else return false;
	}

	// �����_���ŃA�C�e���̈ʒu���擾����
	IVec2 item_pos = m_RefStage->GetRandomItemPos();

	// �A�C�e���̈ʒu�܂ł̍ŒZ�o�H���Z�o
	m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, item_pos);
	if (m_EnemyParam->m_TraceList.empty())return false;

	// �ړ��������X�V����
	m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
	m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));

	return false;
}
