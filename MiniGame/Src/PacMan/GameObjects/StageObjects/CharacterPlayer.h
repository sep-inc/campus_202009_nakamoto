#ifndef PLAYER_H_
#define PLAYER_H_

#include "StageCharacter.h"

namespace PacMan
{
	/*
		�v���C���[�N���X
	*/
	class CharacterPlayer : public StageCharacter
	{
	public:
		/*
			�R���X�g���N�^
		*/
		CharacterPlayer(Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~CharacterPlayer() {}

		/*
			�������֐�
			�Q�[���J�n����1�x�Ă�
		*/
		void Init() override;

		/*
			�X�V�֐�
			1�t���[����1�x�Ă�
		*/
		void Update() override;

		/*
			�`��֐�
			�`��X�e�b�v����
			1�t���[��1�x�Ă�
		*/
		void Draw() override;

		// ���g�̃I�u�W�F�N�g�̎�ނ�Ԃ��֐�
		virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_PLAYER; }


	private:
		/*
			�ړ��֐�
		*/
		void Move();

	};
}


#endif