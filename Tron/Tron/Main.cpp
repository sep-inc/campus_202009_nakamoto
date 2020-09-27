#include "GameTron.h"
#include "System.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	// 乱数の生成
	srand((unsigned int)time(NULL));

	// ゲームクラスのインスタンス
	GameTron game;
	
	while (!g_Quit)
	{
		// ゲームの更新
		game.Update();	

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// ゲームの描画
		game.Draw();

		// バッファの描画
		g_Drawer.DrawBuffer();
	}

	return 0;
}