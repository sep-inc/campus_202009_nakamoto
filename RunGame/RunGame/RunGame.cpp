#include "RunGame.h"
#include "System.h"
#include <iostream>

GameRunGame::GameRunGame():
	m_Player(nullptr),m_Stage (nullptr),m_CurrentStep(RunGameStep::STEP_INT)
{
	m_Stage  = new RunGame::Stage();
	m_Player = new RunGame::Player(m_Stage);
}

GameRunGame::~GameRunGame()
{
	delete m_Player;
	delete m_Stage;
}

/*=============================================*/
/*　　　　　　　　　更新関数     　　　　　　　*/
/*=============================================*/
void GameRunGame::Update()
{
	switch (m_CurrentStep)
	{
	case GameRunGame::RunGameStep::STEP_INT:
		// 初期化ステップ

		// フラグを初期化
		g_GameEnd   = false;
		g_GameClear = false;

		// 各オブジェクトの初期化
		if (m_Stage) m_Stage->Init();
		if (m_Player)m_Player->Init();

		// ステップを進める
		m_CurrentStep = RunGameStep::STEP_UPDATE;
		break;

	case GameRunGame::RunGameStep::STEP_UPDATE:
		
		// ゲームが終了していたらステップを進める
		if (g_GameEnd) {
			m_CurrentStep = RunGameStep::STEP_RELEASE;
			return;
		}

		// 各オブジェクトの更新
		if (m_Player)m_Player->Update();
		

		break;

	case GameRunGame::RunGameStep::STEP_RELEASE:
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
void GameRunGame::Draw()
{
	// 各オブジェクトの描画
	if (m_Player)m_Player->Draw();
	if (m_Stage) m_Stage->Draw();
}

/*=============================================*/
/*　　　　　結果を出力する関数     　　　　　　*/
/*=============================================*/
void GameRunGame::PrintResult()
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
bool GameRunGame::SelectContinue()
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
