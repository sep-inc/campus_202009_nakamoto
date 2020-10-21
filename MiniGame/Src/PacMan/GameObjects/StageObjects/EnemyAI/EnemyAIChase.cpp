#include "EnemyAIChase.h"

ActionStateList PacMan::EnemyAIChase::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// もし性格がAかBならプレイヤーに向かって進む、
	if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_A || enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_B)
	{
		// もし見失ったらアクションを徘徊にする
		if (Chase(enemyPos_, enemyParam_, stage_) == false) return ActionStateList::ACTION_SAUNTERING;
	}

	//// もし性格がBなら先を読んで行動する
	//else if (enemyParam_->m_Personality == EnemyPersonalityList::PERSONALITY_B) {
	//	// 一定フレームでアクションを徘徊にする
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
	// もし追跡リストがなくなるまで移動する
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