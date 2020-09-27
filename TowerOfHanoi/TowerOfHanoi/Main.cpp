#include "GameTowerOfHanoi.h"
#include "System.h"
#include "Global.h"

int main()
{
	GameTowerOfHanoi game;

	while (!g_Quit)
	{
		game.Run();

		g_Drawer.ClearBuffer();

		game.Draw();

		g_Drawer.DrawBuffer();

	}
	
	
	return 0;
}