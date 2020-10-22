#include "EnemyAIDefend.h"
#include "../../../../Utility/Calc.h"

PacMan::EnemyAIDeffend::EnemyAIDeffend(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	EnemyAIBase{ enemyPos_ ,enemyParam_, stage_ }
{
}


ActionStateList PacMan::EnemyAIDeffend::Update()
{
	// もしプレイヤーがいた場合、次に行う行動を追いかけるにする
	IVec2 hoge;
	if (FoundPlayer(m_RefEnemyPos, m_RefStage, 11, &hoge) == true) {
		hoge = hoge - *m_RefEnemyPos;
		if (hoge.m_X != 0)hoge.m_X /= Calc::Abs(hoge.m_X);
		if (hoge.m_Y != 0)hoge.m_Y /= Calc::Abs(hoge.m_Y);

		m_EnemyParam->m_Direction = (*m_RefEnemyPos + hoge) - *m_RefEnemyPos;
		m_EnemyParam->m_TraceList.clear();
		
		return ActionStateList::ACTION_CHASE;
	}

	
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
		
		if (m_EnemyParam->m_TraceList.empty()) {
			return true;
		}
		else return false;
	}

	// ランダムでアイテムの位置を取得する
	IVec2 item_pos = m_RefStage->GetRandomItemPos();
	m_RefStage->FindShortestPath(&m_EnemyParam->m_TraceList, *m_RefEnemyPos, item_pos);
	if (m_EnemyParam->m_TraceList.empty())return false;

	m_EnemyParam->m_Direction = m_EnemyParam->m_TraceList.front() - *m_RefEnemyPos;
	m_EnemyParam->m_TraceList.erase(std::begin(m_EnemyParam->m_TraceList));

	return false;
}
