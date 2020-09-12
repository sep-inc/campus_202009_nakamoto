#include "GlobalObject.h"
#include "Drawer.h"
#include "BlockArray.h"
#include "System.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	BlockArray block_array;

	/////////// ゲームループ ////////////
	while (!g_IsGameOver)
	{
		getchar();
		system("cls");


		// オブジェクトごとにステップ処理を行う
		g_Wall.StepUpdate();
		g_Paddle.StepUpdate();
		block_array.StepUpdate();
		g_Ball.StepUpdate();

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// 描画するオブジェクトをバッファに伝える
		g_Wall.Draw();
		g_Paddle.Draw();
		block_array.Draw();
		g_Ball.Draw();

		// バッファの描画
		g_Drawer.DrawBuffer();
	}

	system("cls");
	printf("ゲームオーバー\n");

	return 0;
}