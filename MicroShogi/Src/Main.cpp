#include "System/Drawer.h"
#include "Game/ShogiGame.h"
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void CallbackSingnalControl(int sig) {
	if (sig == SIGINT) {

		exit(1);
	}
}

int main()
{
	signal(SIGINT, CallbackSingnalControl);


	// 乱数生成
	srand((unsigned int)time(NULL));


	while (true)
	{
		// ゲームの更新
		ShogiGame::GetInstance().Update();
		
		// バッファのクリア
		Drawer::GetInstance().ClearBuffer();

		// ゲームの描画
		ShogiGame::GetInstance().Draw();

		// バッファの描画
		Drawer::GetInstance().DrawBuffer();

	}


	return 0;
}