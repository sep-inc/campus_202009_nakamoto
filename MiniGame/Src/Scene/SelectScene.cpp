#include "SelectScene.h"
#include "../System/Drawer.h"
#include "../System/Input.h"
#include <iostream>

SelectScene::SelectScene(GameList* selectGame_) :
	m_SelectGame{ selectGame_ },
	m_DescriptionText{ "【ゲームを選択してください】\n 【十字キーで選択　　Enterキーで確定】\n" }
{
	m_BlankMenuListStr[(int)GameList::GAME_MICRO_SHOGI]  = "4マス将棋\n";
	m_BlankMenuListStr[(int)GameList::GAME_PACMAN]       = "パックマン\n";
	m_BlankMenuListStr[(int)GameList::GAME_RUNGAME]      = "ランゲーム\n";
	m_BlankMenuListStr[(int)GameList::GAME_TICTACTOE]    = "〇×ゲーム\n";
	m_BlankMenuListStr[(int)GameList::GAME_HANOI]		 = "ハノイ塔\n";
	m_BlankMenuListStr[(int)GameList::GAME_TRON]		 = "トロン\n";
	m_BlankMenuListStr[(int)GameList::GAME_UNKNOWN]      = "終了\n";

	for (int i = 0; i <= (int)GameList::GAME_NUM; ++i)
	{
		m_MenuListStr[i] = m_BlankMenuListStr[i];
	}

}

void SelectScene::Update()
{
	if (SelectGame(m_SelectGame) == true) {
		m_SceneEnd = true;
	}
}

void SelectScene::Draw()
{
	std::string draw_str = m_DescriptionText;
	
	for (const auto& str : m_MenuListStr)
	{
		draw_str += str;
	}
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
	Drawer::GetInstance().SetDrawBuffer(draw_str);	
}

bool SelectScene::SelectGame(GameList* game_)
{
	static int current_select_game = 0;
	
	const std::string arrow = "⇒";

	int key = Input::GetKey();

	if (key == KEY_UP) {
		m_MenuListStr[current_select_game] = m_BlankMenuListStr[current_select_game];
		current_select_game--;
		system("cls");
	}
	else if (key == KEY_DOWN) {
		m_MenuListStr[current_select_game] = m_BlankMenuListStr[current_select_game];
		current_select_game++;
		system("cls");
	}
	else if (key == KEY_ENTER) {
		*game_ = (GameList)current_select_game;
		return true;
	}

	if (current_select_game < 0) current_select_game = 0;
	else if (current_select_game > (int)GameList::GAME_UNKNOWN) current_select_game = (int)GameList::GAME_UNKNOWN;

	m_MenuListStr[current_select_game] = arrow + m_BlankMenuListStr[current_select_game];

	return false;
}
