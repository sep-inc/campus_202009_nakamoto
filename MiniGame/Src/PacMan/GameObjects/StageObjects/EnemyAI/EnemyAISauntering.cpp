#include "EnemyAISauntering.h"


ActionStateList PacMan::EnemyAISauntering::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// 移動方向をランダムに決める
	std::vector<IVec2> able_direction = GetAbleMoveDirection(enemyPos_, enemyParam_, stage_);
	enemyParam_->m_Direction = able_direction[rand() % able_direction.size()];

	// もしプレイヤーがいた場合、次に行う行動を追いかけるにする
	if (FoundPlayer(enemyPos_, stage_, 11) == true) {
		return ActionStateList::ACTION_CHASE;
	}

	// もし性格が守備での時、プレイヤーがアイテムをとった場合、次の行動を守りにする
	if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_C) {
		//if()
	}


	return ActionStateList::ACTION_SAUNTERING;
}


std::vector<IVec2> PacMan::EnemyAISauntering::GetAbleMoveDirection(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	std::vector<IVec2> ret_vec;

	// ゼロベクトルだったら移動できる方向をランダムに選ぶ
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