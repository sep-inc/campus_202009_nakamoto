#include "GameScene.h"
#include "../MicroShogi/Game/ShogiGame.h"
#include "../PacMan/Game/GamePacMan.h"
#include "../RunGame/RunGame.h"
#include "../TicTacToe/TicTacToeGame.h"
#include "../TowerOfHanoi/GameTowerOfHanoi.h"
#include "../Tron/GameTron.h"
#include "../Utility/SafeDelete.h"

GameScene::GameScene(GameList game_) :
	m_Game{ nullptr }
{
	// 受け取ったゲームによってインスタンス化するゲームを返る
	switch (game_)
	{
	case GameList::GAME_MICRO_SHOGI:
		m_Game = new ShogiGame();
		break;
	case GameList::GAME_PACMAN:
		m_Game = new PacMan::GamePacMan();
		break;
	case GameList::GAME_RUNGAME:
		m_Game = new GameRunGame();
		break;
	case GameList::GAME_TICTACTOE:
		m_Game = new TicTacToeGame();
		break;
	case GameList::GAME_HANOI:
		m_Game = new GameTowerOfHanoi();
		break;
	case GameList::GAME_TRON:
		m_Game = new GameTron();
		break;
	default:
		break;
	}
}

GameScene::~GameScene()
{
	SAFE_DELETE(m_Game);
}

void GameScene::Update()
{
	if (!m_Game) return;
	m_Game->Update();

	if (m_Game->IsEnd() == true) {
		m_SceneEnd = true;
	}
}

void GameScene::Draw()
{
	if (m_Game)m_Game->Draw();
}
