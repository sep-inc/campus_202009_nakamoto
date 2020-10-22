#include "EnemyAIDefend.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIDeffend::EnemyAIDeffend(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ ,enemyParam_, stage_ }
{
}


ActionStateList PacMan::EnemyAIDeffend::Update()
{
	// もしプレイヤーがいた場合、次に行う行動を追いかけるにする
	IVec2 player_pos;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &player_pos) == true) {
		IVec2 enemy_to_player_vec = player_pos - *m_RefEnemyPos;
		
		if (enemy_to_player_vec.m_X != 0)enemy_to_player_vec.m_X /= Calc::Abs(enemy_to_player_vec.m_X);
		if (enemy_to_player_vec.m_Y != 0)enemy_to_player_vec.m_Y /= Calc::Abs(enemy_to_player_vec.m_Y);

		m_EnemyParam->m_Direction = enemy_to_player_vec;
		m_EnemyParam->m_TraceList.clear();
		
		return ActionStateList::ACTION_CHASE;
	}

	// アイテムの位置まで到着したら徘徊に遷移	
	if (HeadForItemPosition() == true) {
		return ActionStateList::ACTION_SAUNTERING;
	}

	return ActionStateList::ACTION_DEFEND;
}


bool PacMan::EnemyAIDeffend::HeadForItemPosition()
{
	// もし追跡リストがなくなるまで移動する
	if (!m_EnemyParam->m_TraceList.empty()) {
		m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));
		
		// 移動後追跡リストがなかった場合、到着したので、trueを返す
		if (m_EnemyParam->m_TraceList.empty()) {
			return true;
		}
		else return false;
	}

	// ランダムでアイテムの位置を取得する
	IVec2 item_pos = m_RefStage->GetRandomItemPos();

	// アイテムの位置までの最短経路を算出
	m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, item_pos);
	if (m_EnemyParam->m_TraceList.empty())return false;

	// 移動方向を更新する
	m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
	m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));

	return false;
}
