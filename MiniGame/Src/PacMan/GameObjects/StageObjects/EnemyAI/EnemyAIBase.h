#ifndef ENEMY_AI_BASE_H_
#define ENEMY_AI_BASE_H_

#include "../../Stage.h"
#include "EnemyParamater.h"

namespace PacMan
{
	/*
		�GAI�̊��N���X
	*/
	class EnemyAIBase
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyAIBase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		virtual ~EnemyAIBase() {}


		/*
			�X�V�֐�
			���ɍs�������Ԃ�Ԃ�
		*/
		virtual ActionStateList Update() = 0;

		/*
			�������֐�
		*/
		virtual void Init() {};

	protected:
		/*
			�v���C���[�����������ǂ�����Ԃ��֐�
		*/
		bool FoundPlayer(IVec2* enemyPos_, Stage* stage_,__int8 range_, IVec2* FoundPos_ = nullptr);


	protected:
		// �G�l�~�[�̈ʒu���
		IVec2* m_RefEnemyPos;
		// �G�l�~�[��parameter���
		EnemyParameter* m_EnemyParam;
		// �X�e�[�W�N���X�̎Q�Ɨp�ϐ�
		Stage* m_RefStage;
	};
}

#endif