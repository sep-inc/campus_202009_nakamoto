#include "RunGame.h"
#include "System.h"
#include <iostream>

/*=============================================*/
/*�@�@�@�@�@�@�@�@�@�X�V�֐�     �@�@�@�@�@�@�@*/
/*=============================================*/
void RunGame::Update()
{
	switch (m_CurrentStep)
	{
	case RunGame::RunGameStep::STEP_INT:
		// �������X�e�b�v
		g_GameEnd   = false;
		g_GameClear = false;

		m_Stage.Init();
		m_Player.Init();

		m_CurrentStep = RunGameStep::STEP_UPDATE;
		break;

	case RunGame::RunGameStep::STEP_UPDATE:
		
		// �Q�[�����I�����Ă�����X�e�b�v��i�߂�
		if (g_GameEnd) {
			m_CurrentStep = RunGameStep::STEP_RELEASE;
			return;
		}

		m_Player.Update();
		

		break;

	case RunGame::RunGameStep::STEP_RELEASE:
		// ���ʂ��o�͂���
		PrintResult();

		// �����邩�ǂ��������߂�
		if (SelectContinue() == true) {
			m_CurrentStep = RunGameStep::STEP_INT;

			return;
		}

		g_Quit = true;

		break;
	
	default:
		break;
	}
}

/*=============================================*/
/*�@�@�@�@�@�@�@�@�@�`��֐�     �@�@�@�@�@�@�@*/
/*=============================================*/
void RunGame::Draw()
{
	m_Player.Draw();
	m_Stage.Draw();
}

/*=============================================*/
/*�@�@�@�@�@���ʂ��o�͂���֐�     �@�@�@�@�@�@*/
/*=============================================*/
void RunGame::PrintResult()
{
	// �N���A�t���O���݂Č��ʂ��o�͂���
	if (g_GameClear == true) {
		std::cout << "�N���A!!" << std::endl;
	}
	else {
		std::cout << "���s!!" << std::endl;
	}
}

/*=============================================*/
/* �Q�[���I�����ɑ����邩�ǂ�����I������֐�  */
/*=============================================*/
bool RunGame::SelectContinue()
{
	std::cout << "�����܂����H"  << std::endl;
	std::cout << "������\tEnter" << std::endl;
	std::cout << "��߂�\tESC"   << std::endl;

	while (true)
	{
		// �G���^�[�L�[�������ꂽ��
		if (g_Input.GetKey() == 13) {
			return true;
		}

		// �G�X�P�[�v�������ꂽ��
		if (g_Input.GetKey() == 27) {
			return false;
		}
	}
}
