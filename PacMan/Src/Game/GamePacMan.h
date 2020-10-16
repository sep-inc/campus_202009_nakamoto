#ifndef GAME_PACMAN_H_
#define GAME_PACMAN_H_

#include "../GameObjects/Stage.h"
#include "../GameObjects/StageObjects/EnemyManager.h"
#include "../GameObjects/StageObjects/Player.h"
#include "../Definition.h"

namespace PacMan
{
	/*
	�p�b�N�}���̃Q�[���Ǘ��N���X
*/
	class GamePacMan
	{
		// �X�e�b�v
		enum class GamePacManStep : unsigned char
		{
			STEP_INIT,		// �������X�e�b�v
			STEP_UPDATE,	// �X�V�X�e�b�v
			STEP_RELEASE,	// ����X�e�b�v
		};

	public:
		/*
			�R���X�g���N�^
		*/
		GamePacMan();

		/*
			�f�X�g���N�^
		*/
		~GamePacMan();

		/*
			�X�V�֐�
		*/
		void Update();

		/*
			�`��֐�
		*/
		void Draw();

	private:
		/*
			���ʂ��o�͂���֐�
		*/
		void PrintResult();

		/*
			�����邩�ǂ�����I�����A���ʂ�^�U�ŕԂ��֐�
			�^�F������
			�U�F��߂�
		*/
		bool SelectContinue();

	private:
		// �X�e�[�W
		Stage* m_Stage;
		// �v���C���[
		Player* m_Player;
		// �G�l�~�[
		EnemyManager* m_EnemyArray;
		// ���݂̃X�e�b�v��ۑ�����ϐ�
		GamePacManStep m_CurrentStep;
		// �Q�[�����N���A�������ǂ�����ۑ�����ϐ�
		bool m_GameClear;
	};
}

#endif