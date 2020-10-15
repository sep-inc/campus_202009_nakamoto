#ifndef GAME_PACMAN_H_
#define GAME_PACMAN_H_

#include "../GameObjects/Stage.h"
#include "../GameObjects/StageObjects/EnemyArray.h"
#include "../GameObjects/StageObjects/CharacterPlayer.h"
#include "../PacManDefinition.h"
#include "../../Game.h"

namespace PacMan
{
	/*
	�p�b�N�}���̃Q�[���Ǘ��N���X
*/
	class GamePacMan : public Game
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
		void Update() override;

		/*
			�`��֐�
		*/
		void Draw() override;

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
		CharacterPlayer* m_Player;
		// �G�l�~�[
		EnemyArray* m_EnemyArray;
		// ���݂̃X�e�b�v��ۑ�����ϐ�
		GamePacManStep m_CurrentStep;
		// �Q�[�����N���A�������ǂ�����ۑ�����ϐ�
		bool m_GameClear;
	};
}

#endif