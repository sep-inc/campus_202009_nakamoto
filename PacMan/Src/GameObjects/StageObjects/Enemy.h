#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"

namespace PacMan
{
	/*
		�G�l�~�[�N���X
	*/
	class Enemy : public StageCharacter
	{
	public:
		/*
			�R���X�g���N�^
		*/
		Enemy(Stage* stage_);


		/*
			�f�X�g���N�^
		*/
		~Enemy() {}

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
		// �t���[�������J�E���g����ϐ�
		int m_Timer;

	};
}


#endif