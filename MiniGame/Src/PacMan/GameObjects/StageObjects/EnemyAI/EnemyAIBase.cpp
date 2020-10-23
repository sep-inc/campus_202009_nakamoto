#include "EnemyAIBase.h"


PacMan::EnemyAIBase::EnemyAIBase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) :
	m_RefEnemyPos{ enemyPos_ }, m_EnemyParam{ enemyParam_ }, m_RefStage{ stage_ }
{
}



bool PacMan::EnemyAIBase::FoundPlayer(IVec2* enemyPos_, Stage* stage_, __int8 range_, IVec2* FoundPos_)
{
	/*
		それぞれの方向にプレイヤーがいるかを調べる、
		ブロックがあった場合はその方向は検索を中止する
	*/

	for (int i = 0; i < range_; i++) {
		IVec2 up = IVec2(enemyPos_->m_X, enemyPos_->m_Y - i);
		if (stage_->GetStageObject(up) == ObjectType::TYPE_WALL) break;
		else if (stage_->GetStageObject(up) == ObjectType::TYPE_PLAYER) {
			if (FoundPos_)*FoundPos_ = up;
			return true;
		}
	}

	for (int i = 0; i < range_; i++) {
		IVec2 down = IVec2(enemyPos_->m_X, enemyPos_->m_Y + i);
		if (stage_->GetStageObject(down) == ObjectType::TYPE_WALL) break;
		else if (stage_->GetStageObject(down) == ObjectType::TYPE_PLAYER) {
			if (FoundPos_)*FoundPos_ = down;
			return true;
		}
	}

	for (int i = 0; i < range_; i++) {
		IVec2 left = IVec2(enemyPos_->m_X + i, enemyPos_->m_Y);

		if (stage_->GetStageObject(left) == ObjectType::TYPE_WALL) break;
		else if (stage_->GetStageObject(left) == ObjectType::TYPE_PLAYER) {
			if (FoundPos_)*FoundPos_ = left;
			return true;
		}
	}

	for (int i = 0; i < range_; i++) {
		IVec2 right = IVec2(enemyPos_->m_X - i, enemyPos_->m_Y);
		if (stage_->GetStageObject(right) == ObjectType::TYPE_WALL) break;
		else if (stage_->GetStageObject(right) == ObjectType::TYPE_PLAYER) {
			if (FoundPos_)*FoundPos_ = right;
			return true;
		}
	}

	return false;
}