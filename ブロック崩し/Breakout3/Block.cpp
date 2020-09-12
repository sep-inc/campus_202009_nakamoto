/****************************************************
	header
*****************************************************/
#include "Block.h"
#include "System.h"
#include "GlobalObject.h"

/***************************************************************
		コンストラクター
****************************************************************/
Block::Block():
	m_Width(BLOCK_WIDTH),
	m_Height(BLOCK_HEIGHT),
	m_Type(ObjectType::ObjectBlock),
	m_CurrentStep(BlockStep::InitStep)
{}

/***************************************************************
	ステップを更新する関数
****************************************************************/
void Block::StepUpdate()
{
	// 現在のステップを確認する
	switch (m_CurrentStep)
	{
	case BlockStep::InitStep:
		// 初期化を行う
		this->Initializ();

		// 初期化が終わったらステップを進める
		m_CurrentStep = BlockStep::DrawStep;

		break;


	case BlockStep::DrawStep:

		// もしゲームオーバーならステップを進める
		if (g_IsGameOver) {
			m_CurrentStep = BlockStep::ReleaseStep;
			return;
		}

		// 描画処理

		break;


	case BlockStep::ReleaseStep:

		break;

	default:
		break;
	}
}


/***************************************************************
	初期化関数
****************************************************************/
void Block::Initializ()
{
	m_IsDeath = false;
}


/***************************************************************
	描画関数
****************************************************************/
void Block::Draw()
{
	if (m_IsDeath == true) return;
	g_Drawer.WriteBuffer(m_PosX, m_PosY, m_Width, m_Height, m_Type);
}
