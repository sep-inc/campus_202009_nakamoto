#include "Src/System/Drawer.h"
#include "Src/Game/GamePacMan.h"
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <Windows.h>

// �t���[�����[�g
#define FPS 60.0

void CallbackSingnalControl(int sig) {
	if (sig == SIGINT) {

		exit(1);
	}
}

int main()
{
	signal(SIGINT, CallbackSingnalControl);

	// ��������
	srand((unsigned int)time(NULL));

	// ���g�����擾
	LARGE_INTEGER time_freq;
	QueryPerformanceFrequency(&time_freq);

	// 1�t���[���̂�����b��
	const double FRAME_TIME = 1.0 / FPS;
	double frame_time = 0.0;

	// �v���J�n����
	LARGE_INTEGER time_start;

	// �v�����ԏI������
	LARGE_INTEGER time_end;


	GamePacMan game;


	// �Q�[�����[�v
	while (true)
	{
		// �v���J�n���Ԃ̂��擾
		QueryPerformanceCounter(&time_start);

		game.Update();

		// �o�b�t�@�̃N���A
		Drawer::GetInstance().ClearBuffer();

		game.Draw();

		// �o�b�t�@�̕`��
		Drawer::GetInstance().DrawBuffer();

		/*
			�t���[�����[�g���䏈��
		*/
		// �v���I�����Ԃ��擾
		QueryPerformanceCounter(&time_end);
		// �I�����Ԃ���J�n���Ԉ��������̂����g���Ŋ���o�ߎ��Ԃ��o��
		frame_time = static_cast<double>(time_end.QuadPart - time_start.QuadPart) / static_cast<double>(time_freq.QuadPart);
		// �����������Ԃ�1�t���[���ɂ����鎞�Ԃ������Ȃ������ꍇ
		if (frame_time < FRAME_TIME)
		{
			// 1�t���[���ɂ����鎞�Ԃ���1�t���[���ɂ����������Ԃ������đҋ@����b�����Z�o
			// �Z�o�����b����1000��������ms�ɕϊ�
			DWORD sleep_time = static_cast<DWORD>((FRAME_TIME - frame_time) * 1000.0);

			// �ҋ@����
			Sleep(sleep_time);
		}

	}


	return 0;
}