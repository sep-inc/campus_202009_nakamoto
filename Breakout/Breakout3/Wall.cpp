/****************************************************
	header
*****************************************************/
#include "Wall.h"
#include "System.h"
#include "GlobalObject.h"

/***************************************************************
	コンストラクター
****************************************************************/
Wall::Wall() :
	m_MinX(WALL_MIN_X),
	m_MaxX(WALL_MAX_X),
	m_MinY(WALL_MIN_Y),
	m_MaxY(WALL_MAX_Y),
	m_Width(WALL_WIDTH),
	m_Height(WALL_HEIGHT),
	m_Type(ObjectType::ObjectWall),
	m_CurrentStep(WallStep::InitStep)
{}

/***************************************************************
		ステップを更新する関数
****************************************************************/
void Wall::StepUpdate()
{
	// 現在のステップを確認する
	switch (m_CurrentStep)
	{
	case WallStep::InitStep:
		// 初期化を行う
		this->Initializ();

		// 初期化が終わったらステップを進める
		m_CurrentStep = WallStep::DrawStep;

		break;


	case WallStep::DrawStep:

		// もしゲームオーバーならステップを進める
		if (g_IsGameOver) {
			m_CurrentStep = WallStep::ReleaseStep;
			return;
		}

		// 描画処理
		break;


	case WallStep::ReleaseStep:
		break;

	default:
		break;
	}
}


/***************************************************************
		初期化関数
****************************************************************/
void Wall::Initializ()
{
	return;
}


/***************************************************************
	描画関数
****************************************************************/
void Wall::Draw()
{
}
