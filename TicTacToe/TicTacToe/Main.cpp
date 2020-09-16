#include "GrobalObject.h"
#include "Game.h"
#include "GlobalSystem.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	// 乱数生成
	srand((unsigned int)time(NULL));

	Game game;

	while (!g_IsGameOver)
	{

		// 各オブジェクトのステップ
		game.Update();

		system("cls");

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// バッファに書き込む
		g_Grid.Draw();

		// バッファの描画
		g_Drawer.DrawBuffer();

	}

	
	switch (g_WhosWon)
	{
	case ObjectType::TYPE_PlAYER:
		printf("プレイヤーの勝利！！\n");
		break;

	case ObjectType::TYPE_ENEMY:
		printf("エネミーの勝利！！\n");
		break;

	case ObjectType::TYPE_EMPTY:
		printf("引き分け！！\n");
		break;

	default:
		break;
	}


	return 0;
}