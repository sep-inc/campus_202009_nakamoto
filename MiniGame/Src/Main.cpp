#include "System/Drawer.h"
#include "Scene/SceneManager.h"
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <Windows.h>

// フレームレート
#define FPS 60.0

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

	// 周波数を取得
	LARGE_INTEGER time_freq;
	QueryPerformanceFrequency(&time_freq);

	// 1フレームのかける秒数
	const double FRAME_TIME = 1.0 / FPS;
	double frame_time = 0.0;

	// 計測開始時の
	LARGE_INTEGER time_start;

	// 計測時間終了時の
	LARGE_INTEGER time_end;

	// 
	SceneManager scene_manager;


	// ゲームループ
	while (true)
	{
		// 計測開始時間のを取得
		QueryPerformanceCounter(&time_start);

		scene_manager.Update();

		// バッファのクリア
		Drawer::GetInstance().ClearBuffer();

		scene_manager.Draw();


		// バッファの描画
		Drawer::GetInstance().DrawBuffer();

		/*
			フレームレート制御処理
		*/
		// 計測終了時間を取得
		QueryPerformanceCounter(&time_end);
		// 終了時間から開始時間引いたものを周波数で割り経過時間を出す
		frame_time = static_cast<double>(time_end.QuadPart - time_start.QuadPart) / static_cast<double>(time_freq.QuadPart);
		// もし処理時間が1フレームにかける時間よりも少なかった場合
		if (frame_time < FRAME_TIME)
		{
			// 1フレームにかける時間から1フレームにかかった時間を引いて待機する秒数を算出
			// 算出した秒数に1000をかけてmsに変換
			DWORD sleep_time = static_cast<DWORD>((FRAME_TIME - frame_time) * 1000.0);

			// 待機する
			Sleep(sleep_time);
		}

	}


	return 0;
}