#include "EnemyAISauntering.h"


ActionStateList PacMan::EnemyAISauntering::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// �ړ������������_���Ɍ��߂�
	std::vector<IVec2> able_direction = GetAbleMoveDirection(enemyPos_, enemyParam_, stage_);
	enemyParam_->m_Direction = able_direction[rand() % able_direction.size()];

	// �����v���C���[�������ꍇ�A���ɍs���s����ǂ�������ɂ���
	if (FoundPlayer(enemyPos_, stage_, 11) == true) {
		return ActionStateList::ACTION_CHASE;
	}

	// �������i������ł̎��A�v���C���[���A�C�e�����Ƃ����ꍇ�A���̍s�������ɂ���
	if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_C) {
		//if()
	}


	return ActionStateList::ACTION_SAUNTERING;
}


std::vector<IVec2> PacMan::EnemyAISauntering::GetAbleMoveDirection(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	std::vector<IVec2> ret_vec;

	// �[���x�N�g����������ړ��ł�������������_���ɑI��
	if (enemyParam_->m_Direction.Zero() == true)
	{
		IVec2 direction[4] = {
			{enemyPos_->m_X + 1, enemyPos_->m_Y},
			{enemyPos_->m_X - 1, enemyPos_->m_Y},
			{enemyPos_->m_X, enemyPos_->m_Y + 1},
			{enemyPos_->m_X, enemyPos_->m_Y - 1},
		};

		for (int i = 0; i < 4; ++i) {
			if (stage_->GetStageObject(direction[i]) != ObjectType::TYPE_WALL)
			{
				ret_vec.push_back(direction[i] - *enemyPos_);
			}
		}
	}
	else {

		IVec2 left_direction{ enemyParam_->m_Direction.m_Y, -enemyParam_->m_Direction.m_X };
		if (stage_->GetStageObject(*enemyPos_ + enemyParam_->m_Direction) != ObjectType::TYPE_WALL)   ret_vec.push_back(*enemyPos_ + enemyParam_->m_Direction - *enemyPos_);
		if (stage_->GetStageObject(*enemyPos_ + left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*enemyPos_ + left_direction - *enemyPos_);
		if (stage_->GetStageObject(*enemyPos_ - left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*enemyPos_ - left_direction - *enemyPos_);
	}

	return ret_vec;
}