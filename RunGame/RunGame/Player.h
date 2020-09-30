#ifndef PLYAER_H_
#define PLYAER_H_

#include "Vec2.h"
#include "Stage.h"
#include "Definition.h"

/**
* @brief �v���C���[�N���X
*/
class Player
{
	/**
	* @enum Enum
	* �v���C���[�̃X�e�b�v
	*/
	enum class PlayerStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
	};

public:
	/**
	* @brief   �R���X�g���N�^
	* @details �K�v�ȏ�������������
	*/
	Player(Stage* stage_) :
		m_TerminalVelocity{ 0.9f } ,
		m_Pos{ 0.f,0.f },
		m_OldPos{ 0.f,0.f },
		m_RefStege{ stage_ },
		m_Width{PLAYER_WIDTH},
		m_Height{PLAYER_HEIGHT},
		m_JumpVelocity{ 0.f },
		m_OnGround{ true },
		m_Horizon{ PLAYER_SPEED },
		m_Vertical{ 0.f },
		m_CurrentStep{ PlayerStep::STEP_INIT }
	{}

	/**
	* @brief   �f�X�g���N�^
	*/
	~Player(){}

	/**
	* @brief �@�X�V�֐�
	* @details 1�t���[���Ɉ�x�����Ă�
	*/
	void Update();

	/**
	* @brief   �������֐�
	* @details �Q�[���̏���������1�x�����Ă�
	*/
	void Init();

	/**
	* @brief   �`��֐��֐�
	* @details �X�e�[�W�̕`��̑O�ɌĂ�
	*/
	void Draw();
	
private:
	/**
	* @brief   �W�����v�֐�
	* @details �W�����v�̃g���K�[���Ǘ����Ă���
	*/
	void Jump();

	/**
	* @brief   �����֐�
	* @details �n�ʂɑ������Ă��Ȃ�����
	*/
	void Fall();

	/**
	* @brief   �u���b�N�Ɠ������Ă��邩�𒲂ׂ�֐�
	* @details X����Y���𕪂��āAX���œ������Ă����玀�S�AY���œ������Ă�����ʒu��␳����
	*/
	void ChecHitBlock();

private:
	//! �I�[���x��ۑ�����ϐ�
	const float m_TerminalVelocity;

	//! ���݂̃|�W�V������ۑ�����ϐ�
	Vec2 m_Pos;

	//! 1�t���[���O�̍��W��ۑ�����ϐ�
	Vec2 m_OldPos;

	//! ����
	__int8 m_Width;

	//! �c��
	__int8 m_Height;

	//! �W�����v���x
	float m_JumpVelocity;

	//! X���̈ړ�������ۑ�����ϐ�
	float m_Horizon;

	//! Y���̈ړ�������ۑ�����ϐ�
	float m_Vertical;

	//! �n�ʂɑ������Ă��邩��ۑ�����ϐ�
	bool m_OnGround;

	//! �X�e�[�W�̎Q�Ɨp�ϐ�
	Stage* m_RefStege;

	//! ���݂̃X�e�b�v��ۑ�����ϐ�
	PlayerStep m_CurrentStep;
};

#endif