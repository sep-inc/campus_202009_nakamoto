#include "Stage.h"
#include "System.h"
#include "RunGame.h"
#include <signal.h>
#include <Windows.h>
#include <time.h>
#include <stdexcept>



/*============================*/
/*　　　　　  MAIN          　*/
/*============================*/
int main()
{
	clock_t start_frame_time = 0, frame_time = 0;

	// ゲームクラス
	RunGame game;
	
	while (!g_Quit && !g_Input.GetKey(KeyList::ESC_KEY))
	{
		start_frame_time = clock();

		// ゲームの更新
		game.Update();

		// バッファのクリア
		g_Drawer.ClearBuffer();

		// バッファに書き込む
		game.Draw();

		// バッファを描画する
		g_Drawer.DrawBuffer();	
		
		
		frame_time = clock() - start_frame_time;
		if (frame_time < 60) {
			Sleep(60 - frame_time);
		}
	}

	return 0;
}