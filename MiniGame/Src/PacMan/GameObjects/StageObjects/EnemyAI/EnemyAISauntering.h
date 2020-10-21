#ifndef ENEMY_AI_SAUNTERING_H_
#define ENEMY_AI_SAUNTERING_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	class EnemyAISauntering : public EnemyAIBase
	{
	public:
		static EnemyAISauntering* GetInstance()
		{
			static EnemyAISauntering instance;
			return &instance;
		}

		~EnemyAISauntering(){}
		
		ActionStateList Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) override;
	private:
		EnemyAISauntering() :m_CurrentItemTotalNum{ ITEM_NUM }
		{}

		std::vector<IVec2> GetAbleMoveDirection(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

	private:
		int m_CurrentItemTotalNum;
		
	};
}


#endif