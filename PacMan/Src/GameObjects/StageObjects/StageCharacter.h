#ifndef STAGE_CHARACTER_H_
#define STAGE_CHARACTER_H_

#include "StageObject.h"
#include "../Stage.h"

namespace PacMan
{
	/*
	�X�e�[�W�ɒu���L�����N�^�[�̋K��N���X
*/
	class StageCharacter : public StageObject
	{
	public:
		StageCharacter(Stage* stage_);

		virtual ~StageCharacter() {}

		/*
			�������֐�
		*/
		virtual void Init() = 0;

		/*
			�X�V�֐�
		*/
		virtual void Update() = 0;

		/*
			�`��֐�
		*/
		virtual void Draw() = 0;

		/*
			���g�̃I�u�W�F�N�g�̎�ނ�Ԃ��֐�
		*/
		virtual inline ObjectType GetObjectType() const = 0;

	protected:
		// �X�e�[�W�N���X�ւ̃|�C���^�ϐ�
		Stage* m_RefStage;

	};
}



#endif