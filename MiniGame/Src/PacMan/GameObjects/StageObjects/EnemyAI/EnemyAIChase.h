#ifndef ENEMY_AI_CHASE_H_
#define ENEMY_AI_CHASE_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	class EnemyAIChase : public EnemyAIBase
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyAIChase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~EnemyAIChase() {}

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
			���肷��֐�
			����������false��Ԃ�
		*/
		bool Forestall();

		/*
			�ǂ�������֐�
			����������false��Ԃ�
		*/
		bool Chase();

	private:
		// �v���C���[�̑O�̑O�̍��W��ۑ����Ă����ϐ�
		IVec2 m_PlayerOldPos;

	};
}

#endif