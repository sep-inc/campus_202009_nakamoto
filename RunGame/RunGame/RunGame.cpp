#include "RunGame.h"
#include "System.h"
#include <iostream>

/*=============================================*/
/*　　　　　　　　　更新関数     　　　　　　　*/
/*=============================================*/
void RunGame::Update()
{
	switch (m_CurrentStep)
	{
	case RunGame::RunGameStep::STEP_INT:
		// 初期化ステップ
		g_GameEnd   = false;
		g_GameClear = false;

		m_Stage.Init();
		m_Player.Init();

		m_CurrentStep = RunGameStep::STEP_UPDATE;
		break;

	case RunGame::RunGameStep::STEP_UPDATE:
		
		// ゲームが終了していたらステップを進める
		if (g_GameEnd) {
			m_CurrentStep = RunGameStep::STEP_RELEASE;
			return;
		}

		m_Player.Update();
		

		break;

	case RunGame::RunGameStep::STEP_RELEASE:
		// 結果を出力する
		PrintResult();

		// 続けるかどうかを決める
		if (SelectContinue() == true) {
			m_CurrentStep = RunGameStep::STEP_INT;

			return;
		}

		g_Quit = true;

		break;
	
	default:
		break;
	}
}

/*=============================================*/
/*　　　　　　　　　描画関数     　　　　　　　*/
/*=============================================*/
void RunGame::Draw()
{
	m_Player.Draw();
	m_Stage.Draw();
}

/*=============================================*/
/*　　　　　結果を出力する関数     　　　　　　*/
/*=============================================*/
void RunGame::PrintResult()
{
	// クリアフラグをみて結果を出力する
	if (g_GameClear == true) {
		std::cout << "クリア!!" << std::endl;
	}
	else {
		std::cout << "失敗!!" << std::endl;
	}
}

/*=============================================*/
/* ゲーム終了時に続けるかどうかを選択する関数  */
/*=============================================*/
bool RunGame::SelectContinue()
{
	std::cout << "続けますか？"  << std::endl;
	std::cout << "続ける\tEnter" << std::endl;
	std::cout << "やめる\tESC"   << std::endl;

	while (true)
	{
		// エンターキーが押されたら
		if (g_Input.GetKey() == 13) {
			return true;
		}

		// エスケープが押されたら
		if (g_Input.GetKey() == 27) {
			return false;
		}
	}
}
