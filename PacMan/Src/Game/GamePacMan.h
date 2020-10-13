#ifndef GAME_PACMAN_H_
#define GAME_PACMAN_H_

#include "../GameObjects/Stage.h"
#include "../Definition.h"

class GamePacMan
{
	enum class GamePacManStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
		STEP_RELEASE,
	};

public:
	GamePacMan();

	~GamePacMan(){}

	void Update();

	void Draw();

private:
	Stage*       m_Stage;
	StageObject* m_Player;
	StageObject* m_Enemy[ENEMY_NUM];
	StageObject* m_Item[ITEM_NUM];

	GamePacManStep m_CurrentStep;

};

#endif