#ifndef ENEMY_AI_DEFEND_H_
#define ENEMY_AI_DEFEND_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	class EnemyAIDeffend : public EnemyAIBase
	{
	public:
		static EnemyAIDeffend* GetInstance()
		{
			static EnemyAIDeffend instance;
			return &instance;
		}

		~EnemyAIDeffend(){}

		ActionStateList Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) override;

	private:
		EnemyAIDeffend() {}
		
	};


}

#endif