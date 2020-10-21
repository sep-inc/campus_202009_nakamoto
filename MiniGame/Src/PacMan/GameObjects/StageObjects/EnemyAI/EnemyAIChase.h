#ifndef ENEMY_AI_CHASE_H_
#define ENEMY_AI_CHASE_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	class EnemyAIChase : public EnemyAIBase
	{
	public:
		static EnemyAIChase* GetInstance()
		{
			static EnemyAIChase instance;
			return &instance;
		}

		~EnemyAIChase() {}

		ActionStateList Update(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_) override;

	private:

		EnemyAIChase() {}

		/*
			���肷��
		*/
		void Forestall(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			�ǂ�������
		*/
		bool Chase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

	private:
		std::vector<IVec2> m_TraceList;

	};
}

#endif