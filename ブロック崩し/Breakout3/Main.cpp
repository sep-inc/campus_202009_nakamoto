#include "GlobalObject.h"
#include "Drawer.h"
#include "BlockArray.h"
#include "System.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	BlockArray block_array;

	/////////// �Q�[�����[�v ////////////
	while (!g_IsGameOver)
	{
		getchar();
		system("cls");


		// �I�u�W�F�N�g���ƂɃX�e�b�v�������s��
		g_Wall.StepUpdate();
		g_Paddle.StepUpdate();
		block_array.StepUpdate();
		g_Ball.StepUpdate();

		// �o�b�t�@�̃N���A
		g_Drawer.ClearBuffer();

		// �`�悷��I�u�W�F�N�g���o�b�t�@�ɓ`����
		g_Wall.Draw();
		g_Paddle.Draw();
		block_array.Draw();
		g_Ball.Draw();

		// �o�b�t�@�̕`��
		g_Drawer.DrawBuffer();
	}

	system("cls");
	printf("�Q�[���I�[�o�[\n");

	return 0;
}