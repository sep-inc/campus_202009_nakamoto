#include "GameController.h"
#include "System/Input.h"
#include "MicroShogi/Game/ShogiGame.h"
#include "PacMan/Game/GamePacMan.h"
#include "RunGame/RunGame.h"
#include "TicTacToe/TicTacToeGame.h"
#include "TowerOfHanoi/GameTowerOfHanoi.h"
#include "Tron/GameTron.h"
#include "Utility/SafeDelete.h"
#include <Windows.h>

#include <iostream>

GameController::GameController() :
	m_Game{ nullptr }, m_CurrentStep{ GameStep::STEP_INIT }
{
}

GameController::~GameController()
{
	SAFE_DELETE(m_Game);
}

void GameController::Update()
{
	switch (m_CurrentStep)
	{
	case GameController::GameStep::STEP_INIT:
	{
		GameList select_game = SelectGame();

		switch (select_game)
		{
		case GameController::GameList::GAME_MICRO_SHOGI:
			exit(1);
			break;
		case GameController::GameList::GAME_PACMAN:
			m_Game = new PacMan::GamePacMan();
			break;
		case GameController::GameList::GAME_RUNGAME:
			m_Game = new GameRunGame();
			break;
		case GameController::GameList::GAME_TICTACTOE:
			m_Game = new TicTacToeGame();
			break;
		case GameController::GameList::GAME_HANOI:
			m_Game = new GameTowerOfHanoi();
			break;
		case GameController::GameList::GAME_TRON:
			m_Game = new GameTron();
			break;
		case GameController::GameList::GAME_UNKNOWN:
			exit(1);
			break;
		default:
			break;
		}

		m_CurrentStep = GameStep::STEP_UPDATE;
	}

		break;
	case GameController::GameStep::STEP_UPDATE:
	{
		if (!m_Game)return;
		m_Game->Update();
		if (m_Game->IsEnd() == true) {
			// ゲームの開放

			//ステップをInitにする
			m_CurrentStep = GameStep::STEP_INIT;
		}

	}

		break;
	case GameController::GameStep::STEP_RELEASE:
		break;
	default:
		break;
	}
}

void GameController::Draw()
{
	if (m_Game)m_Game->Draw();
}

GameController::GameList GameController::SelectGame()
{
	// TODO バグ直し

	std::cout << "ゲームを選択してください" << std::endl;

	int current_select_game = 0;

	while (true)
	{
		std::string shogi_str = "	4マス将棋\n";
		std::string pacman_str = "	パックマン\n";
		std::string rungame_str = "	ランゲーム\n";
		std::string tictactoe_str = "	〇×ゲーム\n";
		std::string hanoi_str = "	ハノイ塔\n";
		std::string tron_str = "	トロン\n";
		std::string quit_str = "	終了\n";
		int key = Input::GetKey();

		if (key == KEY_UP)	      current_select_game--;
		else if (key == KEY_DOWN) current_select_game++;
		else if (key == KEY_ENTER) break;

		if (current_select_game < 0) current_select_game = 0;
		else if (current_select_game > (int)GameList::GAME_UNKNOWN) current_select_game = (int)GameList::GAME_UNKNOWN;

		switch ((GameList)current_select_game)
		{
		case GameController::GameList::GAME_MICRO_SHOGI:
			shogi_str = "→" + shogi_str;
			break;
		case GameController::GameList::GAME_PACMAN:
			pacman_str = "→" + pacman_str;
			break;
		case GameController::GameList::GAME_RUNGAME:
			rungame_str = "→" + rungame_str;
			break;
		case GameController::GameList::GAME_TICTACTOE:
			tictactoe_str = "→" + tictactoe_str;
			break;
		case GameController::GameList::GAME_HANOI:
			hanoi_str = "→" + hanoi_str;
			break;
		case GameController::GameList::GAME_TRON:
			tron_str = "→" + tron_str;
			break;
		case GameController::GameList::GAME_UNKNOWN:
			quit_str = "→" + quit_str;
			break;
		default:
			break;
		}

		std::string menu;
		menu = shogi_str + pacman_str + rungame_str + tictactoe_str + hanoi_str + tron_str + quit_str;
		std::cout << menu << std::endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,2 });
		
	}

	return (GameList)current_select_game;
}
