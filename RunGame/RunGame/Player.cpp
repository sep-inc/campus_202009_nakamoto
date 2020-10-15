#include "Player.h"
#include "System.h"

/*============================*/
/*　　　　　更新関数        　*/
/*============================*/
void RunGame::Player::Update()
{
	switch (m_CurrentStep)
	{
	case Player::PlayerStep::STEP_INIT:
		// 初期化ステップ
		Init();
		m_CurrentStep = PlayerStep::STEP_UPDATE;
		
		break;
	case Player::PlayerStep::STEP_UPDATE:
	{
		if (g_GameEnd == true) { return; }

		// 更新ステップ
		m_Vertical = 0.f;

		// ジャンプ
		this->Jump();

		// 落下
		this->Fall();

		// 判定
		this->ChecHitBlock();

		// 現在の座標を保存する
		m_OldPos = m_Pos;

		// もしゴール地点まできたらクリア
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
/*　　　　  初期化関数     　*/
/*===========================*/
void RunGame::Player::Init()
{
	m_Pos          = Vec2(PLAYER_INIT_POS_X, 4.f);
	m_OldPos       = m_Pos;
	m_JumpVelocity = 0.f;
}


/*===============================*/
/*　　　　  描画関数関数     　  */
/*===============================*/
void RunGame::Player::Draw()
{
	if (m_RefStege)m_RefStege->SetStage(m_Pos);
}


/*===========================*/
/*　　　　ジャンプ関数     　*/
/*===========================*/
void RunGame::Player::Jump()
{
	if (m_OnGround && g_Input.GetKey(KeyList::R_KEY))
	{
		m_JumpVelocity = INITIAL_VELOCITY;
		m_OnGround     = false;
	}
}


/*==========================*/
/*　　　　   落下関数     　*/
/*==========================*/
void RunGame::Player::Fall()
{
	if (m_OnGround == false) {
		m_Vertical = (m_Pos.m_Y - m_OldPos.m_Y) - m_JumpVelocity;
		m_JumpVelocity -= GRAVITY;
	}

	m_Vertical += GRAVITY;

	if (m_Vertical > m_TerminalVelocity)m_Vertical = m_TerminalVelocity;
}


/*===============================================*/
/*　　　ブロックと当たっているかを調べる関数     */
/*===============================================*/
void RunGame::Player::ChecHitBlock()
{
	// 前の座標のプレイヤーの右の辺とブロックの左の辺が当たっているかを調べる
	if (m_RefStege->HitPlyaerAndBlockLeftEdge(m_OldPos, m_Width, m_Height) == true)
	{
		// 当たっていた場合死亡
		g_GameEnd = true;
	}
	else {
		m_Pos.m_X += m_Horizon;
	}


	Vec2 move_vertical_next_pos = m_Pos;
	move_vertical_next_pos.m_Y += m_Vertical;

	// 辺のどの座標に当たったかを受け取る変数
	float contact_pos;

	// プレイヤーの下の辺とブロックの上の辺が当たっているかを調べる
	if (m_RefStege->HitPlayerAndBlockTopEdge(move_vertical_next_pos, m_Width, m_Height, &contact_pos) == true)
	{
		// 当たっていた場合当たっていない場所まで位置を補正する
		m_Pos.m_Y = contact_pos - m_Height;
		m_OnGround = true;
	}
	else {
		// 当たっていなかったらプレイヤーのY軸を下げる
		m_Pos.m_Y += m_Vertical;
		m_OnGround = false;
	}
}
