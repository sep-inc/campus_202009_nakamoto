/****************************************************
	header
*****************************************************/
#include "Ball.h"
#include "GlobalObject.h"
#include "Calculation.h"
#include "System.h"

#include <math.h>

/***************************************************************
		�R���X�g���N�^�[
****************************************************************/
Ball::Ball():
	m_CenterPosX(0.0f),
	m_CenterPosY(0.0f),
	m_MoveVecX(0.0f),
	m_MoveVecY(0.0f),
	m_NextPosX(0.0f),
	m_NextPosY(0.0f),
	m_Radius(BALL_RADIUS),
	m_Speed(BALL_SPEED),
	m_Type(ObjectType::ObjectBall),
	m_CurrentStep(BallStep::InitStep)
{}

/***************************************************************
	�X�e�b�v���X�V����֐�
****************************************************************/
void Ball::StepUpdate()
{
	// ���݂̃X�e�b�v���m�F����
	switch (m_CurrentStep)
	{
	case BallStep::InitStep:
		// ���������s��
		this->Initializ();

		// ���������I�������X�e�b�v��i�߂�
		m_CurrentStep = BallStep::DrawStep;

		break;


	case BallStep::DrawStep:
		// ���̍��W���v�Z����
		this->CalcNextPos();

		// �ǂƂ̓����蔻����s��
		this->HitWall();

		// �p�h���Ƃ̓����蔻����s��
		this->HitPaddle();

		// �u���b�N�Ƃ̓����蔻����s��
		this->HitBlock();
		
		// �ړ�����
		this->Move();

		// �����Q�[���I�[�o�[�Ȃ�X�e�b�v��i�߂�
		if (g_IsGameOver) {
			m_CurrentStep = BallStep::ReleaseStep;
			return;
		}

		// �`�揈��
		//this->Draw();

		break;


	case BallStep::ReleaseStep:
		break;
		
	default:
		break;
	}
}


/***************************************************************
	�������֐�
****************************************************************/
void Ball::Initializ()
{
	m_CenterPosX = BALL_INIT_POS_X;
	m_CenterPosY = BALL_INIT_POS_Y;
	m_NextPosX	 = 0.0f;
	m_NextPosY	 = 0.0f;
	m_MoveVecX   = 1 * cosf(Calculation::ToRadian(BALL_INIT_ANGLE)) - 0 * sinf(Calculation::ToRadian(BALL_INIT_ANGLE));
	m_MoveVecY   = 1 * sinf(Calculation::ToRadian(BALL_INIT_ANGLE)) + 0 * cosf(Calculation::ToRadian(BALL_INIT_ANGLE));
}


/***************************************************************
	�`��֐�
****************************************************************/
void Ball::Draw()
{
	g_Drawer.WriteBuffer(m_CenterPosX, m_CenterPosY, m_Type);
}


/***************************************************************
	�ړ��֐�
****************************************************************/
void Ball::Move()
{
	m_CenterPosX += m_MoveVecX * m_Speed;
	m_CenterPosY -= m_MoveVecY * m_Speed;
}


/***************************************************************
	���Ɉړ�������W�����߂�֐�
****************************************************************/
void Ball::CalcNextPos()
{
	m_NextPosX = m_CenterPosX + m_MoveVecX * m_Speed;
	m_NextPosY = m_CenterPosY - m_MoveVecY * m_Speed;
}


/***************************************************************
	���Ɉړ�������W���ǂƓ������Ă��邩�𔻒肷��֐�
****************************************************************/
void Ball::HitWall()
{
	// �����ǂ̍����ɓ������Ă��邩�������͉E�ǂɓ������Ă�����
	// �ړ��x�N�g����X���𔽓]������
	if (HitLeftWall() || HitRightWall())
	{
		m_MoveVecX *= -1;
	}
	// �����ǂ̏㑤�ɓ������Ă�����
	// �ړ��x�N�g����Y���𔽓]������
	else if (HitTopWall())
	{
		m_MoveVecY *= -1;
	}
	// �����ǂ̉����ɓ������Ă�����
	// �Q�[���I�[�o�[�t���O��true�ɂ��ăX�e�b�v��i�߂�
	else if (HitBottomWall())
	{
		g_IsGameOver = true;
		m_CurrentStep = BallStep::ReleaseStep;
	}
}


/***************************************************************
	���Ɉړ�������W���p�h���Ɠ������Ă��邩�𔻒肷��֐�
****************************************************************/
void Ball::HitPaddle()
{
	// �p�h�����O�ɕ�����
	float paddle_x[3] = { 0,0,0 };
	float paddle_y[3] = { 0,0,0 };
	for (int i = 0; i < g_Paddle.GetWidth(); ++i) {
		paddle_x[i] = g_Paddle.GetPosX() + i;
		paddle_y[i] = g_Paddle.GetPosY();
	}

	// �p�h����̉���
	__int8 paddle_width = g_Paddle.GetWidth() / 3;

	// ���p�h��
	const __int8 paddle_left = 0;
	// �^�񒆃p�h��
	const __int8 paddle_center = 1;
	// �E�p�h��
	const __int8 paddle_right = 2;


	// �ǂ̃p�h���ɓ����������ɂ���ăx�N�g���̕�����ς���
	for (int i = 0; i < 3; ++i)
	{
		if ((g_Ball.m_NextPosX >= paddle_x[i]) && (g_Ball.m_NextPosX <= paddle_x[i] + paddle_width)
			&& (g_Ball.m_NextPosY >= paddle_y[i] - g_Ball.m_Radius) && (g_Ball.m_NextPosY <= paddle_y[i] + g_Paddle.GetHeight() + g_Ball.m_Radius == true))
		{
			// �{�[���̃x�N�g�����擾
			float ball_vec_x = g_Ball.m_MoveVecX;
			float ball_vec_y = g_Ball.m_MoveVecY;

			switch (i)
			{
				// ���̃p�h���̎�
			case paddle_left:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(110.0f)) - 0 * sinf(Calculation::ToRadian(110.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(110.0f)) + 0 * cosf(Calculation::ToRadian(110.0f));
				break;

				// �^�񒆂̃p�h���̎�
			case paddle_center:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(90.0f)) - 0 * sinf(Calculation::ToRadian(90.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(90.0f)) + 0 * cosf(Calculation::ToRadian(90.0f));
				break;

				// �E�̃p�h���̎�
			case paddle_right:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(90.0f)) - 0 * sinf(Calculation::ToRadian(90.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(90.0f)) + 0 * cosf(Calculation::ToRadian(90.0f));
				break;

			default:
				break;
			}

			// 1�ł�����������for���𔲂���
			break;
		}
	}

	return;
}


/***************************************************************
	���Ɉړ�������W���ǂƓ������Ă��邩�𔻒肷��֐�
****************************************************************/
void Ball::HitBlock()
{
	// �����u���b�N�̏ォ���ɂ������Ă�����Y���x�N�g���𔽓]������
	if (HitBlockTopOrBottom())
	{
		m_MoveVecY *= -1;
	}
	// �����u���b�N�̍��E�ɓ������Ă�����X���x�N�g���𔽓]������
	else if (HitBlockLeftOrRight())
	{
		m_MoveVecX *= -1;
	}

}


/***************************************************************
	�ǂ̏㑤�Ɠ������Ă��邩�𔻒肷��ϐ�
****************************************************************/
bool Ball::HitTopWall()
{
	// �ǂƓ������Ă�����
	if ((m_NextPosY - m_Radius) < (STAGE_MIN_Y))
	{
		return true;
	}

	return false;
}


/***************************************************************
	�ǂ̉����Ɠ������Ă��邩�𔻒肷��ϐ�
****************************************************************/
bool Ball::HitBottomWall()
{
	// �ǂƓ������Ă�����
	if ((m_NextPosY + m_Radius) > (STAGE_MAX_Y))
	{
		return true;
	}

	return false;
}


/***************************************************************
	�ǂ̉E���Ɠ������Ă��邩�𔻒肷��ϐ�
****************************************************************/
bool Ball::HitRightWall()
{
	// �ǂƓ������Ă�����
	if ((m_NextPosX + m_Radius) >= (STAGE_MAX_X))
	{
		return true;
	}

	return false;
}


/***************************************************************
	�ǂ̍����Ɠ������Ă��邩�𔻒肷��ϐ�
****************************************************************/
bool Ball::HitLeftWall()
{
	// �ǂƓ������Ă�����
	if ((m_NextPosX - m_Radius) < (STAGE_MIN_X))
	{
		return true;
	}

	return false;
}


/***************************************************************
	�u���b�N�̏ォ���Ɠ������Ă��邩�𔻒肷��֐�
****************************************************************/
bool Ball::HitBlockTopOrBottom()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			if (g_Block[y][x].IsDeath() == true) continue;

			if ((this->m_NextPosX >= g_Block[y][x].GetPosX()) && (this->m_NextPosX <= g_Block[y][x].GetPosX() + g_Block[y][x].GetWidth())
				&& (this->m_NextPosY >= g_Block[y][x].GetPosY() - this->m_Radius) && (this->m_NextPosY <= g_Block[y][x].GetPosY() + g_Block[y][x].GetHeight() + this->m_Radius))
			{
				// �������Ă�����u���b�N������
				g_Block[y][x].Dead();

				return true;
			}
		}
	}

	return false;
}


/***************************************************************
	�u���b�N�̍����E�Ɠ������Ă��邩�𔻒肷��֐�
****************************************************************/
bool Ball::HitBlockLeftOrRight()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			if (g_Block[y][x].IsDeath() == true) continue;

			if ((this->m_NextPosX >= g_Block[y][x].GetPosX() - this->m_Radius) && (this->m_NextPosX <= g_Block[y][x].GetPosX() + g_Block[y][x].GetWidth() + this->m_Radius)
				&& (this->m_NextPosY >= g_Block[y][x].GetPosY()) && (this->m_NextPosY <= g_Block[y][x].GetPosY() + g_Block[y][x].GetHeight()))
			{
				// �������Ă�����u���b�N������
				g_Block[y][x].Dead();
				return true;
			}
		}
	}

	return false;
}
