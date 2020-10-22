#include "EnemyAIChase.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIChase::EnemyAIChase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ , enemyParam_ ,stage_ }
{
}

ActionStateList PacMan::EnemyAIChase::Update()
{
	// もし性格がAかCならプレイヤーに向かって進む、
	if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_A || m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_C)
	{
		// もし見失ったらアクションを徘徊にする
		if (Chase() == false) return ActionStateList::ACTION_SAUNTERING;
	}
	// もし性格がBなら先を読んで行動する
	else if (m_EnemyParam->m_Personality == EnemyPersonalityList::PERSONALITY_B) {
		// 一定フレームでアクションを徘徊にする
		if (Forestall() == false) return ActionStateList::ACTION_SAUNTERING;

	}
	

	return ActionStateList::ACTION_CHASE;
}

/*
	先回りで追いかける
*/
bool PacMan::EnemyAIChase::Forestall()
{
	// もしプレイヤーがいた場合,追いかける
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {
		m_PlayerOldPos = player_pos;

		player_pos = player_pos - *m_RefEnemyPos;
		if (player_pos.m_X != 0)player_pos.m_X /= Calc::Abs(player_pos.m_X);
		if (player_pos.m_Y != 0)player_pos.m_Y /= Calc::Abs(player_pos.m_Y);

		m_EnemyParam->m_TraceList.clear();
		m_EnemyParam->m_Direction = (*m_RefEnemyPos + player_pos) - *m_RefEnemyPos;
		return true;
	}
	else if (m_PlayerOldPos.m_X == -1 || m_PlayerOldPos.m_Y == -1) return false;
	else {
		
		// もし追跡リストがなくなるまで移動する
		if (!m_EnemyParam->m_TraceList.empty()) {
			m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
			m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
			return true;
		}

		// もし、見失ったら、プレイヤーの移動した方向を検索する
		if (FoundPlayer(&m_PlayerOldPos, m_RefStage, 11, &player_pos) == false) { return false; }


		while (true)
		{
			// プレイヤーの移動ベクトルを算出
			IVec2 player_vec = player_pos - m_PlayerOldPos;
			if (player_vec.m_X != 0)player_vec.m_X /= Calc::Abs(player_vec.m_X);
			if (player_vec.m_Y != 0)player_vec.m_Y /= Calc::Abs(player_vec.m_Y);
			IVec2 left_direction{ player_vec.m_Y, -player_vec.m_X };


			IVec2 move_vec;
			int able_move_num = 0;

			// 向いている方向にすすめるか
			if (m_RefStage->GetStageObject(player_pos + player_vec) != ObjectType::TYPE_WALL) {
				
				move_vec = (player_pos + player_vec) - player_pos;

				able_move_num++;
			}

			// 向いている方向に対して左に進めるか
			if (m_RefStage->GetStageObject(player_pos + left_direction) != ObjectType::TYPE_WALL) {
				move_vec = (player_pos + player_vec) - player_pos;

				able_move_num++;
			}

			// 向いている方向に対して右にすすめるか
			if (m_RefStage->GetStageObject(player_pos - left_direction) != ObjectType::TYPE_WALL) {
				move_vec = (player_pos + player_vec) - player_pos;

				able_move_num++;
			}

			if (able_move_num > 1) { break; }
			m_PlayerOldPos = player_pos;
			player_pos = player_pos + move_vec;
		}

		m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, player_pos);
		if (m_EnemyParam->m_TraceList.empty())return false;
		
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
	}

	return true;
}

/*
	追いかける
*/
bool PacMan::EnemyAIChase::Chase()
{
	// もし追跡リストがなくなるまで移動する
	if (!m_EnemyParam->m_TraceList.empty()) {
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
		return true;
	}

	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == false) return false;

	m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, player_pos);
	if (m_EnemyParam->m_TraceList.empty())return false;

	m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
	m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
	return true;
}

void PacMan::EnemyAIChase::Init()
{
	m_PlayerOldPos.m_X = -1;
	m_PlayerOldPos.m_Y = -1;
}
