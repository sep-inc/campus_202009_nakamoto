#ifndef ENEMY_AI_SAUNTERING_H_
#define ENEMY_AI_SAUNTERING_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	/*
		�p�j��AI
	*/
	class EnemyAISauntering : public EnemyAIBase
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyAISauntering(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
		* �f�X�g���N�^
		*/
		~EnemyAISauntering(){}
		
		/*
			�X�V�֐�
			���ɍs�������Ԃ�Ԃ�
		*/
		ActionStateList Update() override;

		/*
			�������֐�
			AI���؂�ւ�������Ɉ�x�����Ă�
		*/
		void Init() override;

	private:

		/*
			�ړ��\�ȕ�����Ԃ��֐�
		*/
		std::vector<IVec2> GetAbleMoveDirection();

	private:
		/*
			���݂̃A�C�e���̐���ۑ�����ϐ�
		*/
		int m_CurrentItemTotalNum;
		
	};
}


#endif