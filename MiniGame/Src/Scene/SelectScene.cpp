#include "SelectScene.h"
#include "../System/Drawer.h"
#include "../System/Input.h"

#include <iostream>

SelectScene::SelectScene(GameList* selectGame_) :
	m_SelectGame{ selectGame_ }
{
}

void SelectScene::Update()
{
	if (SelectGame(m_SelectGame) == true) {
		m_SceneEnd = true;
	}
}

void SelectScene::Draw()
{
}

bool SelectScene::SelectGame(GameList* game_)
{
	int current_select_game = 0;
	system("cls");
	while (true)
	{
		std::string shogi_str = "4マス将棋\n";
		std::string pacman_str = "パックマン\n";
		std::string rungame_str = "ランゲーム\n";
		std::string tictactoe_str = "〇×ゲーム\n";
		std::string hanoi_str = "ハノイ塔\n";
		std::string tron_str = "トロン\n";
		std::string quit_str = "終了\n";
		int key = Input::GetKey();

		if (key == KEY_UP)	      current_select_game--;
		else if (key == KEY_DOWN) current_select_game++;
		else if (key == KEY_ENTER) break;

		if (current_select_game < 0) current_select_game = 0;
		else if (current_select_game > (int)GameList::GAME_UNKNOWN) current_select_game = (int)GameList::GAME_UNKNOWN;

		switch ((GameList)current_select_game)
		{
		case GameList::GAME_MICRO_SHOGI:
			shogi_str = "⇒" + shogi_str;
			break;
		case GameList::GAME_PACMAN:
			pacman_str = "⇒" + pacman_str;
			break;
		case GameList::GAME_RUNGAME:
			rungame_str = "⇒" + rungame_str;
			break;
		case GameList::GAME_TICTACTOE:
			tictactoe_str = "⇒" + tictactoe_str;
			break;
		case GameList::GAME_HANOI:
			hanoi_str = "⇒" + hanoi_str;
			break;
		case GameList::GAME_TRON:
			tron_str = "⇒" + tron_str;
			break;
		case GameList::GAME_UNKNOWN:
			quit_str = "⇒" + quit_str;
			break;
		default:
			break;
		}

		std::string menu;
		menu = shogi_str + pacman_str + rungame_str + tictactoe_str + hanoi_str + tron_str + quit_str;
		std::cout << "【ゲームを選択してください】" << std::endl;
		std::cout << "【十字キーで選択　　Enterキーで確定】" << std::endl;
		std::cout << menu << std::endl;

		if (key != -1) {

			system("cls");
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });

	}

	*game_ = (GameList)current_select_game;

	return true;
}
