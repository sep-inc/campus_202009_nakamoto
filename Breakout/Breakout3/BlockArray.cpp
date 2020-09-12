/****************************************************
	header
*****************************************************/
#include "BlockArray.h"
#include "GlobalObject.h"

/****************************************************
�u���b�N�z��̏�����
*****************************************************/
BlockArray::BlockArray()
{
	// ���W��������
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			g_Block[y][x].SetPosX(x + BLOCK_INIT_X);
			g_Block[y][x].SetPosY(y + BLOCK_INIT_Y);
		}
	}
}

/****************************************************
�u���b�N�z��̍X�V
*****************************************************/
void BlockArray::StepUpdate()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {

			if (g_Block[y][x].IsDeath() == true) continue;

			g_Block[y][x].StepUpdate();
		}
	}

	if (AllBlocksBroken() == true)
	{
		g_IsGameOver = true;
	}
}


/****************************************************
	�u���b�N�̕`��
*****************************************************/
void BlockArray::Draw()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			g_Block[y][x].Draw();
		}
	}
}


/****************************************************
	�S�Ẵu���b�N�����Ă��邩�𔻒肷��֐�
*****************************************************/
bool BlockArray::AllBlocksBroken()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			// 1�ł������Ă�����False��Ԃ�
			if (g_Block[y][x].IsDeath() == false)
			{
				return false;
			}
		}
	}

	return true;
}
