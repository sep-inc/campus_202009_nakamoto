#ifndef WALL_H_
#define WALL_H_

/****************************************************
	header
*****************************************************/
#include "ObjectType.h"

/****************************************************
	class
*****************************************************/

/*
	�ǃN���X
*/
class Wall
{
	// �ǂ̍X�V�X�e�b�v
	enum class WallStep
	{
		InitStep,		// �������X�e�b�v
		DrawStep,		// �`��X�e�b�v
		ReleaseStep,	// ����X�e�b�v
	};

public:
	/***************************************************************
		�R���X�g���N�^�[
	****************************************************************/
	Wall();

	/***************************************************************
		�R���X�g���N�^�[
	****************************************************************/
	~Wall()
	{}

	/***************************************************************
		�X�e�b�v���X�V����֐�
	****************************************************************/
	void StepUpdate();

	/***************************************************************
		�`��֐�
	****************************************************************/
	void Draw();

	/***************************************************************
		�Q�b�^�[�֐�
	****************************************************************/
	inline const __int8 GetMinX()  const { return m_MinX;   }
	inline const __int8 GetMaxX()  const { return m_MaxX;   }
	inline const __int8 GetMinY()  const { return m_MinY;   }
	inline const __int8 GetMaxY()  const { return m_MaxY;   }
	inline const __int8 GetWidth() const { return m_Width;  }
	inline const __int8 GetHeight()const { return m_Height; }

private:
	/***************************************************************
		�������֐�
	****************************************************************/
	void Initializ();

private:
	// ���[�̕�
	const __int8 m_MinX;

	// �E�[�̕�
	const __int8 m_MaxX;

	// ��̕�
	const __int8 m_MinY;

	// ���̕�
	const __int8 m_MaxY;

	// ����
	const __int8 m_Width;

	// �c��
	const __int8 m_Height;

	// �I�u�W�F�N�g�^�C�v
	const __int8 m_Type;

	// ���݂�STEP
	WallStep m_CurrentStep;

};


#endif