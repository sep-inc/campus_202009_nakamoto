#include "TicTacToeGame.h"
#include "GrobalObject.h"
#include "GlobalSystem.h"
#include <stdio.h>
#include <conio.h>

// 各オブジェクトのステップ関数を呼び出す関数
void TicTacToeGame::Update()
{
	switch (m_CurrentStep)
	{
	case TicTacToeGame::TicTacToeGameStep::STEP_INIT:
		// 初期化

		g_IsGameOver = false;
		g_WhosWon    = ObjectType::TYPE_EMPTY;
		g_WhosTurn   = ObjectType::TYPE_PlAYER;
		m_Player.Init();
		m_Enemy.Init();
		g_Grid.Init();
		
		m_CurrentStep = TicTacToeGame::TicTacToeGameStep::STEP_UPDATE;
		m_TurnCount = 0;

		break;
	case TicTacToeGame::TicTacToeGameStep::STEP_UPDATE:

		// 決着がついていたらステップを進める
		if (g_IsGameOver) m_CurrentStep = TicTacToeGame::TicTacToeGameStep::STEP_RELEASE;

		// ターンを進める
		m_TurnCount++;
		
		// ターン数が奇数ならプレイヤーの更新を行う
		if (m_TurnCount % 2 == 1) {
			m_Player.StepUpdate();
		}
		// 奇数ならエネミーの更新を行う
		else {
			m_Enemy.StepUpdate();
		}		
		
		break;

	case TicTacToeGame::TicTacToeGameStep::STEP_RELEASE:

		this->Announce();

		break;
	default:
		break;
	}
}

void TicTacToeGame::Draw()
{
	g_Grid.Draw();
}


// 勝敗を表示し、続けるかどうかを決める関数
void TicTacToeGame::Announce()
{
	switch (g_WhosWon)
	{
	case ObjectType::TYPE_PlAYER:
		printf("プレイヤーの勝利！！\n");
		break;

	case ObjectType::TYPE_ENEMY:
		printf("エネミーの勝利！！\n");
		break;

	case ObjectType::TYPE_EMPTY:
		printf("引き分け！！\n");
		break;

	default:
		break;
	}

	printf("続けますか？\n");
	printf("はい->\t\tReturnキー\n");
	printf("いいえ->\tESCキー\n");


	int key = _getch();
	if (key != 27) {
		m_CurrentStep = TicTacToeGame::TicTacToeGameStep::STEP_INIT;
	}
	else {
		g_Quit = true;
	}
}
