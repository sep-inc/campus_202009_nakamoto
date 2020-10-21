#ifndef ENEMY_AI_CONTROLLER_H_
#define ENEMY_AI_CONTROLLER_H_

#include "EnemyAIBase.h"
#include "EnemyParamater.h"

namespace PacMan
{
	class EnemyAIController
	{
	public:
		EnemyAIController(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		~EnemyAIController(){}

		void Update();

	private:
		EnemyAIBase* m_AI;
		EnemyParameter* m_Parameter;
		IVec2* m_EnemyPos;
		Stage* m_RefStage;


		ActionStateList m_CurrentAction;

	};

}


#endif