#include "EnemyAIDefend.h"
#include "../../../../Utility/Calc.h"

ActionStateList PacMan::EnemyAIDeffend::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// もしプレイヤーがいた場合、次に行う行動を追いかけるにする
	IVec2 hoge;
	if (FoundPlayer(enemyPos_, stage_, 11, &hoge) == true) {
		hoge = hoge - *enemyPos_;
		if (hoge.m_X != 0)hoge.m_X /= Calc::Abs(hoge.m_X);
		if (hoge.m_Y != 0)hoge.m_Y /= Calc::Abs(hoge.m_Y);

		enemyParam_->m_Direction = (*enemyPos_ + hoge) - *enemyPos_;
		enemyParam_->m_TraceList.clear();
		
		return ActionStateList::ACTION_CHASE;
	}

	
	if (HeadForItemPosition(enemyPos_, enemyParam_, stage_) == true) {
		return ActionStateList::ACTION_SAUNTERING;
	}

	return ActionStateList::ACTION_DEFEND;
}


bool PacMan::EnemyAIDeffend::HeadForItemPosition(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// もし追跡リストがなくなるまで移動する
	if (!enemyParam_->m_TraceList.empty()) {
		enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
		enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));
		
		if (enemyParam_->m_TraceList.empty()) return true;
		else return false;
	}

	// ランダムでアイテムの位置を取得する
	IVec2 item_pos = stage_->GetRandomItemPos();
	stage_->FindShortestPath(&enemyParam_->m_TraceList, *enemyPos_, item_pos);
	
	enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
	enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));

	return false;
}
