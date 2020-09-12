/****************************************************
	header
*****************************************************/
#include "Paddle.h"
#include "System.h"
#include "GlobalObject.h"

/****************************************************
	�R���X�g���N�^
*****************************************************/
Paddle::Paddle():
	m_Speed(PADDLE_SPEED),
	m_Width(PADDLE_WIDTH),
	m_Height(PADDLE_HEIGHT),
	m_Type(ObjectType::ObjectPaddle),
	m_CurrentStep(PaddleStep::InitStep)
{}

/***************************************************************
	�X�e�b�v���X�V����֐�
****************************************************************/
void Paddle::StepUpdate()
{
	// ���݂̃X�e�b�v���m�F����
	switch (m_CurrentStep)
	{
	case PaddleStep::InitStep:
		// ���������s��
		this->Initializ();

		// ���������I�������X�e�b�v��i�߂�
		m_CurrentStep = PaddleStep::DrawStep;

		break;


	case PaddleStep::DrawStep:
		// ���̍��W���v�Z����
		this->CalcNextPos();

		// �ǂƂ̓����蔻����s��
		this->HitWall();

		// �ړ�����
		this->Move();

		// �����Q�[���I�[�o�[�Ȃ�X�e�b�v��i�߂�
		if (g_IsGameOver) {
			m_CurrentStep = PaddleStep::ReleaseStep;
			return;
		}

		// �`�揈��
		//this->Draw();

		break;


	case PaddleStep::ReleaseStep:
		break;

	default:
		break;
	}
}

/***************************************************************
	�������֐�
****************************************************************/
void Paddle::Initializ()
{
	m_PosX     = PADDLE_INIT_X;
	m_PosY     = PADDLE_INIT_Y;
	m_NextPosX = 0.0f;
	m_MoveVecX = 1.0f;
}

/***************************************************************
	�`��֐�
****************************************************************/
void Paddle::Draw()
{
	g_Drawer.WriteBuffer(m_PosX, m_PosY, m_Width, m_Height, m_Type);
}

/***************************************************************
	�ړ��֐�
****************************************************************/
void Paddle::Move()
{
	m_PosX += m_MoveVecX * m_Speed;
}

/***************************************************************
	���Ɉړ�������W�����߂�֐�
****************************************************************/
void Paddle::CalcNextPos()
{
	m_NextPosX = m_PosX + m_MoveVecX * m_Speed;
}

/***************************************************************
	���Ɉړ�������W���ǂƓ������Ă��邩�𔻒肷��֐�
****************************************************************/
void Paddle::HitWall()
{
	// �������E�̕ǂɓ���������
	if (HitRightWall() || HitLeftWall())
	{
		// �ړ��x�N�g���𔽓]
		m_MoveVecX *= -1;
	}
}

/***************************************************************
	�E�ǂƓ������Ă��邩�𔻒肷��֐�
****************************************************************/
bool Paddle::HitRightWall()
{
	// �E�̕ǂɓ���������
	if (m_NextPosX + m_Width > STAGE_MAX_X)
	{
		return true;
	}

	return false;
}


/***************************************************************
	���ǂƓ������Ă��邩�𔻒肷��֐�
****************************************************************/
bool Paddle::HitLeftWall()
{
	// ���̕ǂɓ���������
	if (m_NextPosX <= STAGE_MIN_X)
	{
		return true;
	}

	return false;
}
