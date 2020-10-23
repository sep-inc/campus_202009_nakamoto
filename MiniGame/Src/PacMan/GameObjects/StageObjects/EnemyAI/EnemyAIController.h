#ifndef ENEMY_AI_CONTROLLER_H_
#define ENEMY_AI_CONTROLLER_H_

#include "EnemyAIBase.h"
#include "EnemyParamater.h"

namespace PacMan
{
	class EnemyAIController
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyAIController(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			デストラクタ
		*/
		~EnemyAIController();

		/*
			更新関数
		*/
		void Update();

	private:
		// AI配列
		EnemyAIBase* m_AI[(int)ActionStateList::ACTION_NUM];
		// 現在の行動を保存する変数
		ActionStateList m_CurrentAction;

	};

}


#endif