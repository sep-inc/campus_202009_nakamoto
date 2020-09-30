#include "Stage.h"
#include "System.h"
#include "RunGame.h"

/*============================*/
/*　　　　　  MAIN          　*/
/*============================*/
int main()
{
	// ゲームクラス
	RunGame game;
	
	while (!g_Quit)
	{
		// ゲームの更新
		game.Update();

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// バッファに書き込む
		game.Draw();

		// バッファを描画する
		g_Drawer.DrawBuffer();		
	}

	return 0;
}