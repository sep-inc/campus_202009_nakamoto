#include "Player.h"
#include "System.h"

/*============================*/
/*�@�@�@�@�@�X�V�֐�        �@*/
/*============================*/
void Player::Update()
{
	switch (m_CurrentStep)
	{
	case Player::PlayerStep::STEP_INIT:
		// �������X�e�b�v
		Init();
		m_CurrentStep = PlayerStep::STEP_UPDATE;
		
		break;
	case Player::PlayerStep::STEP_UPDATE:
	{
		if (g_GameEnd == true) { return; }

		// �X�V�X�e�b�v
		m_Vertical = 0.f;

		// �W�����v
		this->Jump();

		// ����
		this->Fall();

		// ����
		this->ChecHitBlock();

		// ���݂̍��W��ۑ�����
		m_OldPos = m_Pos;

		// �����S�[���n�_�܂ł�����N���A
		if (m_Pos.m_X >= GOAL_POS) {
			g_GameClear = true;
			g_GameEnd   = true;
		}

	}
		break;
	default:
		break;
	}
}


/*===========================*/
/*�@�@�@�@  �������֐�     �@*/
/*===========================*/
void Player::Init()
{
	m_Pos          = Vec2(PLAYER_INIT_POS_X, 4.f);
	m_OldPos       = m_Pos;
	m_JumpVelocity = 0.f;
}


/*===============================*/
/*�@�@�@�@  �`��֐��֐�     �@  */
/*===============================*/
void Player::Draw()
{
	m_RefStege->SetStage(m_Pos);
}


/*===========================*/
/*�@�@�@�@�W�����v�֐�     �@*/
/*===========================*/
void Player::Jump()
{
	if (m_OnGround && g_Input.GetKey(KeyList::R_KEY))
	{
		m_JumpVelocity = INITIAL_VELOCITY;
		m_OnGround     = false;
	}
}


/*==========================*/
/*�@�@�@�@   �����֐�     �@*/
/*==========================*/
void Player::Fall()
{
	if (m_OnGround == false) {
		m_Vertical = (m_Pos.m_Y - m_OldPos.m_Y) - m_JumpVelocity;
		m_JumpVelocity -= GRAVITY;
	}

	m_Vertical += GRAVITY;

	if (m_Vertical > m_TerminalVelocity)m_Vertical = m_TerminalVelocity;
}


/*===============================================*/
/*�@�@�@�u���b�N�Ɠ������Ă��邩�𒲂ׂ�֐�     */
/*===============================================*/
void Player::ChecHitBlock()
{
	// �O�̍��W�̃v���C���[�̉E�̕ӂƃu���b�N�̍��̕ӂ��������Ă��邩�𒲂ׂ�
	if (m_RefStege->HitPlyaerAndBlockLeftEdge(m_OldPos, m_Width, m_Height) == true)
	{
		// �������Ă����ꍇ���S
		g_GameEnd = true;
	}
	else {
		m_Pos.m_X += m_Horizon;
	}


	Vec2 move_vertical_next_pos = m_Pos;
	move_vertical_next_pos.m_Y += m_Vertical;

	// �ӂ̂ǂ̍��W�ɓ������������󂯎��ϐ�
	float contact_pos;

	// �v���C���[�̉��̕ӂƃu���b�N�̏�̕ӂ��������Ă��邩�𒲂ׂ�
	if (m_RefStege->HitPlayerAndBlockTopEdge(move_vertical_next_pos, m_Width, m_Height, &contact_pos) == true)
	{
		// �������Ă����ꍇ�������Ă��Ȃ��ꏊ�܂ňʒu��␳����
		m_Pos.m_Y = contact_pos - m_Height;
		m_OnGround = true;
	}
	else {
		// �������Ă��Ȃ�������v���C���[��Y����������
		m_Pos.m_Y += m_Vertical;
		m_OnGround = false;
	}
}
