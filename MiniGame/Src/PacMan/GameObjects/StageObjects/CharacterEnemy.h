#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageCharacter.h"

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
		CharacterEnemy(Stage* stage_);


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

		/*
			���g�̎���ňړ��ł�������Ɛ����������֐�
		*/
		void AbleMoveAround(IVec2 pos_, IVec2* outVecArray_, int* ableMoveNum_);

	private:
		// �t���[�������J�E���g����ϐ�
		int m_Timer;

		// ���݂̈ړ�������ۑ�����ϐ�
		IVec2 m_Direction;
		
	};
}


#endif