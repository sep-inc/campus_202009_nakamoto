#ifndef RUNGAME_H_
#define RUNGAME_H_
#include "Player.h"
#include "Stage.h"

/**
* @brief Run�Q�[���N���X
*/
class RunGame
{
	/**
	* @enum Enum
	* Run�Q�[���̃X�e�b�v
	*/
	enum class RunGameStep : unsigned char
	{
		STEP_INT,
		STEP_UPDATE,
		STEP_RELEASE,
	};

public:
	/**
	* @brief   �R���X�g���N�^
	* @details �K�v�ȏ�������������
	*/
	RunGame() :
		m_Player{ &m_Stage },
		m_CurrentStep{ RunGameStep::STEP_INT }
	{}

	/**
	* @brief   �f�X�g���N�^
	*/
	~RunGame(){}

	/**
	* @brief �@�X�V�֐�
	* @details 1�t���[���Ɉ�x�����Ă�
	*/
	void Update();

	/**
	* @brief   �`��֐�
	* @details �e�I�u�W�F�N�g�̕`����s��
	*/
	void Draw();

private:
	/**
	* @brief �@���ʂ��o�͂���֐�
	* @details �Q�[���I�����Ɍ��ʂ��Q�Ƃ��ďo�͂���
	*/
	void PrintResult();

	/**
	* @brief   �Q�[���I�����ɑ����邩�ǂ�����I������֐�
	* @return  bool ������Ȃ�true��Ԃ�
	*/
	bool SelectContinue();

private:
	//! �v���C���[�ϐ�
	Player m_Player;

	//! �X�e�[�W�ϐ�
	Stage m_Stage;
	
	//! ���݂̃X�e�b�v��ۑ�����ϐ�
	RunGameStep m_CurrentStep;
};

#endif