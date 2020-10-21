#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"
#include "EnemyAI/EnemyParamater.h"
#include "EnemyAI/EnemyAIController.h"

namespace PacMan
{
	/*
		�G�l�~�[�N���X
	*/
	class CharacterEnemy : public StageCharacter
	{
	public:
		/*
			�R���X�g���N�^
		*/
		CharacterEnemy(Stage* stage_, int speed_, EnemyPersonalityList personality_);


		/*
			�f�X�g���N�^
		*/
		~CharacterEnemy() {}

		/*
			�������֐�
			�Q�[���J�n���Ɉ�x�����Ăяo��
		*/
		void Init() override;

		/*
			�X�V�֐�
		*/
		void Update() override;

		/*
			�`��֐�
			�`��N���X�̃o�b�t�@�ɃZ�b�g����
		*/
		void Draw() override;

		/*
			���g�̎�ނ�Ԃ��֐�
		*/
		virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_ENEMY; }


	private:
		/*
			�ړ��֐�
		*/
		void Move();

	private:

		int m_Timer;

		// �G�l�~�[�̃p�����[�^�[���܂Ƃ߂��\����
		EnemyParameter m_Param;

		EnemyAIController m_AI;
	};
}


#endif