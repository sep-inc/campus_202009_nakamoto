#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Game.h"

class GameController
{
enum class GameList
{
	GAME_MICRO_SHOGI,
	GAME_PACMAN,
	GAME_RUNGAME,
	GAME_TICTACTOE,
	GAME_HANOI,
	GAME_TRON,
	GAME_UNKNOWN,
};

enum class GameStep
{
	STEP_INIT,
	STEP_UPDATE,
	STEP_RELEASE,
};

public:
	GameController();

	~GameController();

	void Update();

	void Draw();

private:
	/*
		ƒQ[ƒ€‚ğ‘I‘ğ‚·‚é‚µ‚ÄƒQ[ƒ€‚Ìí—Ş‚ğ•Ô‚·
	*/
	GameList SelectGame();

private:
	Game* m_Game;

	GameStep m_CurrentStep;
	
};

#endif