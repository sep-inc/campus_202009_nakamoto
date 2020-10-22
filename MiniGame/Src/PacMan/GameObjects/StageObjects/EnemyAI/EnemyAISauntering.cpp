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
	// もしプレイヤーがいた場合、次に行う行動を追いかけるにする
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {
		player_pos = player_pos - *m_RefEnemyPos;
		if (player_pos.m_X != 0)player_pos.m_X /= Calc::Abs(player_pos.m_X);
		if (player_pos.m_Y != 0)player_pos.m_Y /= Calc::Abs(player_pos.m_Y);
		
		m_EnemyParam->m_Direction = (*m_RefEnemyPos + player_pos) - *m_RefEnemyPos;
		return ActionStateList::ACTION_CHASE;
	}

	// 移動方向をランダムに決める
	std::vector<IVec2> able_direction = GetAbleMoveDirection();
	m_EnemyParam->m_Direction = able_direction[rand() % able_direction.size()];


	// もし性格が守備での時、プレイヤーがアイテムをとった場合、次の行動を守りにする
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
	m_CurrentItemTotalNum = m_RefStage->ItemTotalNum();
}


std::vector<IVec2> PacMan::EnemyAISauntering::GetAbleMoveDirection()
{
	std::vector<IVec2> ret_vec;

	// ゼロベクトルだったら移動できる方向をランダムに選ぶ
	if (m_EnemyParam->m_Direction.Zero() == true)
	{
		
		IVec2 direction[4] = {
			{m_RefEnemyPos->m_X + 1, m_RefEnemyPos->m_Y},
			{m_RefEnemyPos->m_X - 1, m_RefEnemyPos->m_Y},
			{m_RefEnemyPos->m_X, m_RefEnemyPos->m_Y + 1},
			{m_RefEnemyPos->m_X, m_RefEnemyPos->m_Y - 1},
		};

		// 四方向で移動できる場所があれば候補に追加
		for (int i = 0; i < 4; ++i) {
			if (m_RefStage->GetStageObject(direction[i]) != ObjectType::TYPE_WALL)
			{
				ret_vec.push_back(direction[i] - *m_RefEnemyPos);
			}
		}
	}
	else {

		// 後退しないように前と右と左を追加
		IVec2 left_direction{ m_EnemyParam->m_Direction.m_Y, -m_EnemyParam->m_Direction.m_X };
		if (m_RefStage->GetStageObject(*m_RefEnemyPos + m_EnemyParam->m_Direction) != ObjectType::TYPE_WALL)   ret_vec.push_back(*m_RefEnemyPos + m_EnemyParam->m_Direction - *m_RefEnemyPos);
		if (m_RefStage->GetStageObject(*m_RefEnemyPos + left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*m_RefEnemyPos + left_direction - *m_RefEnemyPos);
		if (m_RefStage->GetStageObject(*m_RefEnemyPos - left_direction) != ObjectType::TYPE_WALL)ret_vec.push_back(*m_RefEnemyPos - left_direction - *m_RefEnemyPos);
	}

	return ret_vec;
}