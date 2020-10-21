#ifndef ENEMY_AI_BASE_H_
#define ENEMY_AI_BASE_H_

#include "../../Stage.h"
#include "EnemyParamater.h"

namespace PacMan
{
	class EnemyAIBase
	{
	public:
		EnemyAIBase(){}

		virtual ~EnemyAIBase() {}

		virtual ActionStateList Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) = 0;

	protected:
		bool FoundPlayer(IVec2* enemyPos_, Stage* stage_,__int8 range_, IVec2* FoundPos_ = nullptr);
	};
}

#endif