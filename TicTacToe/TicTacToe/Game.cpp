#include "Game.h"
#include "GrobalObject.h"

// 各オブジェクトのステップ関数を呼び出す関数
void Game::Update()
{
	g_Player.StepUpdate();
	g_Enemy.StepUpdate();
	g_Grid.StepUpdate();
}
