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
			�R���X�g���N�^
		*/
		EnemyAIController(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~EnemyAIController();

		/*
			�X�V�֐�
		*/
		void Update();

	private:
		// AI�z��
		EnemyAIBase* m_AI[(int)ActionStateList::ACTION_NUM];
		// ���݂̍s����ۑ�����ϐ�
		ActionStateList m_CurrentAction;

	};

}


#endif