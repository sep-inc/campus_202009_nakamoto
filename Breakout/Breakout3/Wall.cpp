/****************************************************
	header
*****************************************************/
#include "Wall.h"
#include "System.h"
#include "GlobalObject.h"

/***************************************************************
	�R���X�g���N�^�[
****************************************************************/
Wall::Wall() :
	m_MinX(WALL_MIN_X),
	m_MaxX(WALL_MAX_X),
	m_MinY(WALL_MIN_Y),
	m_MaxY(WALL_MAX_Y),
	m_Width(WALL_WIDTH),
	m_Height(WALL_HEIGHT),
	m_Type(ObjectType::ObjectWall),
	m_CurrentStep(WallStep::InitStep)
{}

/***************************************************************
		�X�e�b�v���X�V����֐�
****************************************************************/
void Wall::StepUpdate()
{
	// ���݂̃X�e�b�v���m�F����
	switch (m_CurrentStep)
	{
	case WallStep::InitStep:
		// ���������s��
		this->Initializ();

		// ���������I�������X�e�b�v��i�߂�
		m_CurrentStep = WallStep::DrawStep;

		break;


	case WallStep::DrawStep:

		// �����Q�[���I�[�o�[�Ȃ�X�e�b�v��i�߂�
		if (g_IsGameOver) {
			m_CurrentStep = WallStep::ReleaseStep;
			return;
		}

		// �`�揈��
		break;


	case WallStep::ReleaseStep:
		break;

	default:
		break;
	}
}


/***************************************************************
		�������֐�
****************************************************************/
void Wall::Initializ()
{
	return;
}


/***************************************************************
	�`��֐�
****************************************************************/
void Wall::Draw()
{
}
