#include "GamePacMan.h"
#include "../../System/Input.h"
#include <string>
#include <iostream>
#include <Windows.h>

/*
	�R���X�g���N�^
*/
PacMan::GamePacMan::GamePacMan() :
	m_Stage{ nullptr }, m_EnemyArray{ nullptr }, m_CurrentStep{ GamePacManStep::STEP_INIT }, m_GameClear{ false }
{
	m_Stage = new Stage();

#ifdef PLAYER_ON
	m_Player = new CharacterPlayer(m_Stage);
#endif

#ifdef ENEMY_ON
	m_EnemyArray = new EnemyArray(m_Stage);
#endif
}


/*
	�f�X�g���N�^
*/
PacMan::GamePacMan::~GamePacMan()
{
	SAFE_DELETE(m_Stage);
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_EnemyArray);
}


/*
	�X�V�֐�
*/
void PacMan::GamePacMan::Update()
{
	// ���݂̃X�e�b�v���Q��
	switch (m_CurrentStep)
	{
	case GamePacMan::GamePacManStep::STEP_INIT:

		// �X�e�[�W�̏�����
		if (m_Stage) m_Stage->Init();
		// �v���C���[�̏�����
		if (m_Player) m_Player->Init();
		// �G�l�~�[�̏�����
		if (m_EnemyArray)m_EnemyArray->Init();

		// ���̃X�e�b�v�֐i�߂�
		m_CurrentStep = GamePacManStep::STEP_UPDATE;
		break;
	case GamePacMan::GamePacManStep::STEP_UPDATE:
		// �e�I�u�W�F�N�g�̍X�V�������Ȃ�
		if (m_Player) m_Player->Update();

		if (m_EnemyArray)m_EnemyArray->Update();

		// �����X�e�[�W�ɃA�C�e�����Ȃ��Ȃ�����X�e�b�v��i�߂�
		if (m_Stage->EmptyItem() == true) {
			
			m_CurrentStep = GamePacManStep::STEP_RELEASE;
			m_GameClear = true;
		}
		// �����G�ƃv���C���[���������Ă�����X�e�b�v��i�߂�
		else if (m_Stage->HitPlayerAndEnemy() == true) {

			m_CurrentStep = GamePacManStep::STEP_RELEASE;
		}

		break;
	case GamePacMan::GamePacManStep::STEP_RELEASE:
		// ���ʂ��o��
		PrintResult();
		// �����邩�ǂ�����I��
		if (SelectContinue() == true) {
			// ������Ȃ珉�����X�e�b�v��
			m_CurrentStep = GamePacManStep::STEP_INIT;
			system("cls");
		}
		else {
			// �����Ȃ��Ȃ�Q�[���I��
			m_IsEnd = true;
			exit(0);
		}
		break;
	default:
		break;
	}
}


/*
	�`��֐�
*/
void PacMan::GamePacMan::Draw()
{
	std::cout << "�\���L�[�ňړ�" << std::endl;

	// �e�I�u�W�F�N�g�̕`��
	m_Stage->Draw();

	if (m_Player) m_Player->Draw();

	if (m_EnemyArray)m_EnemyArray->Draw();

}


/*
	���ʂ�\������֐�
*/
void PacMan::GamePacMan::PrintResult()
{
	std::string str_result;

	str_result = m_GameClear ? "�Q�[���N���A!!" : "�Q�[���I�[�o�[";

	std::cout << str_result << std::endl;
	
}


/*
	�����邩�ǂ�����I�����ĕԂ��֐�
*/
bool PacMan::GamePacMan::SelectContinue()
{
	std::cout << "������x�����܂����H" << std::endl;
	std::cout << "������	Enter�L�[" << std::endl;
	std::cout << "��߂�	Esc�L�[�@" << std::endl;

	while (true)
	{
		int key = Input::GetKey();

		if (key == -1) continue;

		if (key == KEY_ENTER)return true;
		else if (key == KEY_ESC)return false;
	}
}
