#include "RunGame.h"
#include "../System/Input.h"
#include <iostream>

GameRunGame::GameRunGame():
	m_Player(nullptr),m_Stage (nullptr),m_CurrentStep(RunGameStep::STEP_INT)
{
	m_Stage  = new RunGame::RanGameStage();
	m_Player = new RunGame::RanPlayer(m_Stage);
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
		RunGame::g_GameEnd   = false;
		RunGame::g_GameClear = false;

		// 各オブジェクトの初期化
		if (m_Stage) m_Stage->Init();
		if (m_Player)m_Player->Init();

		// ステップを進める
		m_CurrentStep = RunGameStep::STEP_UPDATE;
		break;

	case GameRunGame::RunGameStep::STEP_UPDATE:
		
		// ゲームが終了していたらステップを進める
		if (RunGame::g_GameEnd) {
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

		m_IsEnd = true;

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
	if (RunGame::g_GameClear == true) {
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
		if (Input::GetKey() == KEY_ENTER) {
			return true;
		}

		// エスケープが押されたら
		if (Input::GetKey() == KEY_ESC) {
			return false;
		}
	}
}
