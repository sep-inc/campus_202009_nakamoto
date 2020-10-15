#ifndef STAGE_OBJECT_H_
#define STAGE_OBJECT_H_

#include "../../../Utility/IVec2.h"
#include "../../PacManDefinition.h"


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
		StageObject();

		/*
			�f�X�g���N�^
		*/
		virtual ~StageObject() {}

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
		inline void SetPos(IVec2 vec_) { m_Pos = vec_; }

		/*
			���g�̍��W��Ԃ��֐�
		*/
		inline IVec2 GetPos()const { return m_Pos; }


	protected:
		// ���݂̍��W��ۑ�����ϐ�
		IVec2 m_Pos;


	};
}


#endif