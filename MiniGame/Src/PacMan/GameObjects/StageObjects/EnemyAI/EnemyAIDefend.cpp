#include "EnemyAIDefend.h"
#include "../../../../Utility/Calc.h"

ActionStateList PacMan::EnemyAIDeffend::Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_)
{
	// �����v���C���[�������ꍇ�A���ɍs���s����ǂ�������ɂ���
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
	// �����ǐՃ��X�g���Ȃ��Ȃ�܂ňړ�����
	if (!enemyParam_->m_TraceList.empty()) {
		enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
		enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));
		
		if (enemyParam_->m_TraceList.empty()) return true;
		else return false;
	}

	// �����_���ŃA�C�e���̈ʒu���擾����
	IVec2 item_pos = stage_->GetRandomItemPos();
	stage_->FindShortestPath(&enemyParam_->m_TraceList, *enemyPos_, item_pos);
	
	enemyParam_->m_Direction = enemyParam_->m_TraceList.front() - *enemyPos_;
	enemyParam_->m_TraceList.erase(std::begin(enemyParam_->m_TraceList));

	return false;
}
