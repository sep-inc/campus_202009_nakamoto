#ifndef BALL_H_
#define BALL_H_

/****************************************************
	header
*****************************************************/
#include "ObjectType.h"


/****************************************************
	class
*****************************************************/
/*
	���N���X
*/
class Ball
{
	// �{�[���̍X�V�X�e�b�v
	enum class BallStep
	{
		InitStep,		// �������X�e�b�v
		DrawStep,		// �`��X�e�b�v
		ReleaseStep,	// ����X�e�b�v
	};

public:
	/***************************************************************
		�R���X�g���N�^�[
	****************************************************************/
	Ball();

	/***************************************************************
		�f�X�g���N�^�[
	****************************************************************/
	~Ball()
	{}
	
	/***************************************************************
		�X�e�b�v���X�V����֐�
	****************************************************************/
	void StepUpdate();

	/***************************************************************
		�`��֐�
	****************************************************************/
	void Draw();

private:


	/***************************************************************
		�������֐�
	****************************************************************/
	void Initializ();

	/***************************************************************
		�ړ��֐�
	****************************************************************/
	void Move();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	void CalcNextPos();

	/***************************************************************
		���Ɉړ�������W���ǂƓ������Ă��邩�𔻒肷��֐�
	****************************************************************/
	void HitWall();

	/***************************************************************
		���Ɉړ�������W���p�h���Ɠ������Ă��邩�𔻒肷��֐�
	****************************************************************/
	void HitPaddle();

	/***************************************************************
		���Ɉړ�������W���ǂƓ������Ă��邩�𔻒肷��֐�
	****************************************************************/
	void HitBlock();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitTopWall();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitBottomWall();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitRightWall();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitLeftWall();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitBlockTopOrBottom();

	/***************************************************************
		���Ɉړ�������W�����߂�֐�
	****************************************************************/
	bool HitBlockLeftOrRight();


private:
	// ���S�_���WX
	float m_CenterPosX;

	// ���S�_���WY
	float m_CenterPosY;

	// ���̒��S�_���WX
	float m_NextPosX;

	// ���̒��S�_���WY
	float m_NextPosY;

	// X���ړ��x�N�g��
	float m_MoveVecX;

	// Y���ړ��x�N�g��
	float m_MoveVecY;

	// ���a
	const float m_Radius;

	// ���x 1/60�t���[���̑��x
	const float m_Speed;

	// �I�u�W�F�N�g�̎��
	const __int8 m_Type;

	// �{�[���̌��݂�STEP��ۑ�����ϐ�
	BallStep m_CurrentStep;
};

#endif