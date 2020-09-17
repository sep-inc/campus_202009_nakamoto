#include "GrobalObject.h"
#include "TicTacToeGame.h"
#include "GlobalSystem.h"
#include <time.h>
#include <stdlib.h>

int main()
{
	// 乱数生成
	srand((unsigned int)time(NULL));

	TicTacToeGame game;

	while (!g_Quit)
	{

		// 各オブジェクトのステップ
		game.Update();

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// バッファに書き込む
		game.Draw();

		// バッファの描画
		g_Drawer.DrawBuffer();

	}


	return 0;
}