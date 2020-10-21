#include "EnemyAIChase.h"

ActionStateList PacMan::EnemyAIChase::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// �������i��A��B�Ȃ�v���C���[�Ɍ������Đi�ށA
	if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_A || enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_B)
	{
		// ��������������A�N�V������p�j�ɂ���
		if (Chase(enemyPos_, enemyParam_, stage_) == false) return ActionStateList::ACTION_SAUNTERING;
	}

	//// �������i��B�Ȃ���ǂ�ōs������
	//else if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_B) {
	//	// ���t���[���ŃA�N�V������p�j�ɂ���
	//	
	//}
	//

	return ActionStateList::ACTION_CHASE;
}

void PacMan::EnemyAIChase::Forestall(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	
}

bool PacMan::EnemyAIChase::Chase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// �����ǐՃ��X�g���Ȃ��Ȃ�܂ňړ�����
	if (!enemyParam_->m_TraceList.empty()) {
		enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
		enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));
		return true;
	}

	IVec2 player_pos;
	if (FoundPlayer(enemyPos_, stage_, 11, &player_pos) == false) return false;

	stage_->FindShortestPath(&enemyParam_->m_TraceList, *enemyPos_, player_pos);
	enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
	enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));
}