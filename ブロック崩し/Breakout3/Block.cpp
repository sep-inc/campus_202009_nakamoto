/****************************************************
	header
*****************************************************/
#include "Block.h"
#include "System.h"
#include "GlobalObject.h"

/***************************************************************
		�R���X�g���N�^�[
****************************************************************/
Block::Block():
	m_Width(BLOCK_WIDTH),
	m_Height(BLOCK_HEIGHT),
	m_Type(ObjectType::ObjectBlock),
	m_CurrentStep(BlockStep::InitStep)
{}

/***************************************************************
	�X�e�b�v���X�V����֐�
****************************************************************/
void Block::StepUpdate()
{
	// ���݂̃X�e�b�v���m�F����
	switch (m_CurrentStep)
	{
	case BlockStep::InitStep:
		// ���������s��
		this->Initializ();

		// ���������I�������X�e�b�v��i�߂�
		m_CurrentStep = BlockStep::DrawStep;

		break;


	case BlockStep::DrawStep:

		// �����Q�[���I�[�o�[�Ȃ�X�e�b�v��i�߂�
		if (g_IsGameOver) {
			m_CurrentStep = BlockStep::ReleaseStep;
			return;
		}

		// �`�揈��

		break;


	case BlockStep::ReleaseStep:

		break;

	default:
		break;
	}
}


/***************************************************************
	�������֐�
****************************************************************/
void Block::Initializ()
{
	m_IsDeath = false;
}


/***************************************************************
	�`��֐�
****************************************************************/
void Block::Draw()
{
	if (m_IsDeath == true) return;
	g_Drawer.WriteBuffer(m_PosX, m_PosY, m_Width, m_Height, m_Type);
}
