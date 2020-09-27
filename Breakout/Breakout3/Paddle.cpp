/****************************************************
	header
*****************************************************/
#include "Paddle.h"
#include "System.h"
#include "GlobalObject.h"

/****************************************************
	コンストラクタ
*****************************************************/
Paddle::Paddle():
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_NextPosX(0.0f),
	m_MoveVecX(0.0f),
	m_Speed(PADDLE_SPEED),
	m_Width(PADDLE_WIDTH),
	m_Height(PADDLE_HEIGHT),
	m_Type(ObjectType::ObjectPaddle),
	m_CurrentStep(PaddleStep::InitStep)
{}

/***************************************************************
	ステップを更新する関数
****************************************************************/
void Paddle::StepUpdate()
{
	// 現在のステップを確認する
	switch (m_CurrentStep)
	{
	case PaddleStep::InitStep:
		// 初期化を行う
		this->Initializ();

		// 初期化が終わったらステップを進める
		m_CurrentStep = PaddleStep::DrawStep;

		break;


	case PaddleStep::DrawStep:
		// 次の座標を計算する
		this->CalcNextPos();

		// 壁との当たり判定を行う
		this->HitWall();

		// 移動処理
		this->Move();

		// もしゲームオーバーならステップを進める
		if (g_IsGameOver) {
			m_CurrentStep = PaddleStep::ReleaseStep;
			return;
		}

		// 描画処理
		//this->Draw();

		break;


	case PaddleStep::ReleaseStep:
		break;

	default:
		break;
	}
}

/***************************************************************
	初期化関数
****************************************************************/
void Paddle::Initializ()
{
	m_PosX     = PADDLE_INIT_X;
	m_PosY     = PADDLE_INIT_Y;
	m_NextPosX = 0.0f;
	m_MoveVecX = 1.0f;
}

/***************************************************************
	描画関数
****************************************************************/
void Paddle::Draw()
{
	g_Drawer.WriteBuffer(m_PosX, m_PosY, m_Width, m_Height, m_Type);
}

/***************************************************************
	移動関数
****************************************************************/
void Paddle::Move()
{
	m_PosX += m_MoveVecX * m_Speed;
}

/***************************************************************
	次に移動する座標を求める関数
****************************************************************/
void Paddle::CalcNextPos()
{
	m_NextPosX = m_PosX + m_MoveVecX * m_Speed;
}

/***************************************************************
	次に移動する座標が壁と当たっているかを判定する関数
****************************************************************/
void Paddle::HitWall()
{
	// もし左右の壁に当たったら
	if (HitRightWall() || HitLeftWall())
	{
		// 移動ベクトルを反転
		m_MoveVecX *= -1;
	}
}

/***************************************************************
	右壁と当たっているかを判定する関数
****************************************************************/
bool Paddle::HitRightWall()
{
	// 右の壁に当たったら
	if (m_NextPosX + m_Width > STAGE_MAX_X)
	{
		return true;
	}

	return false;
}


/***************************************************************
	左壁と当たっているかを判定する関数
****************************************************************/
bool Paddle::HitLeftWall()
{
	// 左の壁に当たったら
	if (m_NextPosX <= STAGE_MIN_X)
	{
		return true;
	}

	return false;
}
