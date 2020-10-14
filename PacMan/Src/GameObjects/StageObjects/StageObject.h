#ifndef STAGE_OBJECT_H_
#define STAGE_OBJECT_H_

#include "../../Utility/Vec2.h"
#include "../../Definition.h"
#include "../Stage.h"


namespace PacMan
{
	/*
		�X�e�[�W�ɔz�u����I�u�W�F�N�g�̊��N���X
	*/
	class StageObject
	{
	public:
		/*
			�R���X�g���N�^
		*/
		StageObject(Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		virtual ~StageObject() {}

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

		/*
			���g�̍��W���Z�b�g����֐�
		*/
		inline void SetPos(Vec2 vec_) { m_Pos = vec_; }

		/*
			���g�̍��W��Ԃ��֐�
		*/
		inline Vec2 GetPos()const { return m_Pos; }


	protected:
		// ���݂̍��W��ۑ�����ϐ�
		Vec2 m_Pos;

		// �X�e�[�W�N���X�ւ̃|�C���^�ϐ�
		Stage* m_RefStage;


	};
}


#endif