#include "Player.h"
#include "GrobalObject.h"
#include "GlobalSystem.h"
#include <stdio.h>


void TicTacToe::Player::StepUpdate()
{
	// 現在のステップを確認
	switch (m_CurrentStep)
	{
	case PlayerStep::STEP_INIT:

		this->Init();

		// ステップを進める
		m_CurrentStep = PlayerStep::STEP_UPDATE;
		// 初期化
		break;

	case PlayerStep::STEP_UPDATE:
		
		// ゲームが終了していたら
		if (g_IsGameOver) {
			// ステップを進める
			m_CurrentStep = PlayerStep::STEP_RELEASE;
			return;
		}

		// どこに置くのかを選ぶ
		this->Select();

		// 更新
		break;

	case PlayerStep::STEP_RELEASE:
		
		
		// 解放
		break;

	default:
		break;
	}
}


// 初期化関数
void TicTacToe::Player::Init()
{
	m_CurrentStep = PlayerStep::STEP_INIT;
}

// どのマスの横軸に置くかを決める関数
__int8 TicTacToe::Player::SelectHorizontal()
{
	printf("横軸を入力してください\n");
	printf("A  or  B  or  C\n");

	int key = g_Input.GetKey();

	if (key == 'a')		 return 0;
	else if (key == 'b') return 1;
	else if (key == 'c') return 2;

	return -1;
}

// どのマスの縦軸に置くかを決める関数
__int8 TicTacToe::Player::SelectVertical()
{
	printf("縦軸を入力してください\n");
	printf("1  or  2  or  3\n");

	int key = g_Input.GetKey();

	if (key == '1')		 return 0;
	else if (key == '2') return 1;
	else if (key == '3') return 2;

	return -1;
}
