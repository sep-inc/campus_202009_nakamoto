/****************************************************
	header
*****************************************************/
#include "Ball.h"
#include "GlobalObject.h"
#include "Calculation.h"
#include "System.h"

#include <math.h>

/***************************************************************
		コンストラクター
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
	ステップを更新する関数
****************************************************************/
void Ball::StepUpdate()
{
	// 現在のステップを確認する
	switch (m_CurrentStep)
	{
	case BallStep::InitStep:
		// 初期化を行う
		this->Initializ();

		// 初期化が終わったらステップを進める
		m_CurrentStep = BallStep::DrawStep;

		break;


	case BallStep::DrawStep:
		// 次の座標を計算する
		this->CalcNextPos();

		// 壁との当たり判定を行う
		this->HitWall();

		// パドルとの当たり判定を行う
		this->HitPaddle();

		// ブロックとの当たり判定を行う
		this->HitBlock();
		
		// 移動処理
		this->Move();

		// もしゲームオーバーならステップを進める
		if (g_IsGameOver) {
			m_CurrentStep = BallStep::ReleaseStep;
			return;
		}

		// 描画処理
		//this->Draw();

		break;


	case BallStep::ReleaseStep:
		break;
		
	default:
		break;
	}
}


/***************************************************************
	初期化関数
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
	描画関数
****************************************************************/
void Ball::Draw()
{
	g_Drawer.WriteBuffer(m_CenterPosX, m_CenterPosY, m_Type);
}


/***************************************************************
	移動関数
****************************************************************/
void Ball::Move()
{
	m_CenterPosX += m_MoveVecX * m_Speed;
	m_CenterPosY -= m_MoveVecY * m_Speed;
}


/***************************************************************
	次に移動する座標を求める関数
****************************************************************/
void Ball::CalcNextPos()
{
	m_NextPosX = m_CenterPosX + m_MoveVecX * m_Speed;
	m_NextPosY = m_CenterPosY - m_MoveVecY * m_Speed;
}


/***************************************************************
	次に移動する座標が壁と当たっているかを判定する関数
****************************************************************/
void Ball::HitWall()
{
	// もし壁の左側に当たっているかもしくは右壁に当たっていたら
	// 移動ベクトルのX軸を反転させる
	if (HitLeftWall() || HitRightWall())
	{
		m_MoveVecX *= -1;
	}
	// もし壁の上側に当たっていたら
	// 移動ベクトルのY軸を反転させる
	else if (HitTopWall())
	{
		m_MoveVecY *= -1;
	}
	// もし壁の下側に当たっていたら
	// ゲームオーバーフラグをtrueにしてステップを進める
	else if (HitBottomWall())
	{
		g_IsGameOver = true;
		m_CurrentStep = BallStep::ReleaseStep;
	}
}


/***************************************************************
	次に移動する座標がパドルと当たっているかを判定する関数
****************************************************************/
void Ball::HitPaddle()
{
	// パドルを三つに分ける
	float paddle_x[3] = { 0,0,0 };
	float paddle_y[3] = { 0,0,0 };
	for (int i = 0; i < g_Paddle.GetWidth(); ++i) {
		paddle_x[i] = g_Paddle.GetPosX() + i;
		paddle_y[i] = g_Paddle.GetPosY();
	}

	// パドル一つの横幅
	__int8 paddle_width = g_Paddle.GetWidth() / 3;

	// 左パドル
	const __int8 paddle_left = 0;
	// 真ん中パドル
	const __int8 paddle_center = 1;
	// 右パドル
	const __int8 paddle_right = 2;


	// どのパドルに当たったかによってベクトルの方向を変える
	for (int i = 0; i < 3; ++i)
	{
		if ((g_Ball.m_NextPosX >= paddle_x[i]) && (g_Ball.m_NextPosX <= paddle_x[i] + paddle_width)
			&& (g_Ball.m_NextPosY >= paddle_y[i] - g_Ball.m_Radius) && (g_Ball.m_NextPosY <= paddle_y[i] + g_Paddle.GetHeight() + g_Ball.m_Radius == true))
		{
			// ボールのベクトルを取得
			float ball_vec_x = g_Ball.m_MoveVecX;
			float ball_vec_y = g_Ball.m_MoveVecY;

			switch (i)
			{
				// 左のパドルの時
			case paddle_left:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(110.0f)) - 0 * sinf(Calculation::ToRadian(110.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(110.0f)) + 0 * cosf(Calculation::ToRadian(110.0f));
				break;

				// 真ん中のパドルの時
			case paddle_center:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(90.0f)) - 0 * sinf(Calculation::ToRadian(90.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(90.0f)) + 0 * cosf(Calculation::ToRadian(90.0f));
				break;

				// 右のパドルの時
			case paddle_right:
				g_Ball.m_MoveVecX = 1 * cosf(Calculation::ToRadian(90.0f)) - 0 * sinf(Calculation::ToRadian(90.0f));
				g_Ball.m_MoveVecY = 1 * sinf(Calculation::ToRadian(90.0f)) + 0 * cosf(Calculation::ToRadian(90.0f));
				break;

			default:
				break;
			}

			// 1つでも当たったらfor分を抜ける
			break;
		}
	}

	return;
}


/***************************************************************
	次に移動する座標が壁と当たっているかを判定する関数
****************************************************************/
void Ball::HitBlock()
{
	// もしブロックの上か下にあたっていたらY軸ベクトルを反転させる
	if (HitBlockTopOrBottom())
	{
		m_MoveVecY *= -1;
	}
	// もしブロックの左右に当たっていたらX軸ベクトルを反転させる
	else if (HitBlockLeftOrRight())
	{
		m_MoveVecX *= -1;
	}

}


/***************************************************************
	壁の上側と当たっているかを判定する変数
****************************************************************/
bool Ball::HitTopWall()
{
	// 壁と当たっていたら
	if ((m_NextPosY - m_Radius) < (STAGE_MIN_Y))
	{
		return true;
	}

	return false;
}


/***************************************************************
	壁の下側と当たっているかを判定する変数
****************************************************************/
bool Ball::HitBottomWall()
{
	// 壁と当たっていたら
	if ((m_NextPosY + m_Radius) > (STAGE_MAX_Y))
	{
		return true;
	}

	return false;
}


/***************************************************************
	壁の右側と当たっているかを判定する変数
****************************************************************/
bool Ball::HitRightWall()
{
	// 壁と当たっていたら
	if ((m_NextPosX + m_Radius) >= (STAGE_MAX_X))
	{
		return true;
	}

	return false;
}


/***************************************************************
	壁の左側と当たっているかを判定する変数
****************************************************************/
bool Ball::HitLeftWall()
{
	// 壁と当たっていたら
	if ((m_NextPosX - m_Radius) < (STAGE_MIN_X))
	{
		return true;
	}

	return false;
}


/***************************************************************
	ブロックの上か下と当たっているかを判定する関数
****************************************************************/
bool Ball::HitBlockTopOrBottom()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			if (g_Block[y][x].IsDeath() == true) continue;

			if ((this->m_NextPosX >= g_Block[y][x].GetPosX()) && (this->m_NextPosX <= g_Block[y][x].GetPosX() + g_Block[y][x].GetWidth())
				&& (this->m_NextPosY >= g_Block[y][x].GetPosY() - this->m_Radius) && (this->m_NextPosY <= g_Block[y][x].GetPosY() + g_Block[y][x].GetHeight() + this->m_Radius))
			{
				// 当たっていたらブロックを消す
				g_Block[y][x].Dead();

				return true;
			}
		}
	}

	return false;
}


/***************************************************************
	ブロックの左か右と当たっているかを判定する関数
****************************************************************/
bool Ball::HitBlockLeftOrRight()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			if (g_Block[y][x].IsDeath() == true) continue;

			if ((this->m_NextPosX >= g_Block[y][x].GetPosX() - this->m_Radius) && (this->m_NextPosX <= g_Block[y][x].GetPosX() + g_Block[y][x].GetWidth() + this->m_Radius)
				&& (this->m_NextPosY >= g_Block[y][x].GetPosY()) && (this->m_NextPosY <= g_Block[y][x].GetPosY() + g_Block[y][x].GetHeight()))
			{
				// 当たっていたらブロックを消す
				g_Block[y][x].Dead();
				return true;
			}
		}
	}

	return false;
}
