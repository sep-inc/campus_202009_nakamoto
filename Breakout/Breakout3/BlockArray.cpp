/****************************************************
	header
*****************************************************/
#include "BlockArray.h"
#include "GlobalObject.h"

/****************************************************
ブロック配列の初期化
*****************************************************/
BlockArray::BlockArray()
{
	// 座標を初期化
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			g_Block[y][x].SetPosX(x + BLOCK_INIT_X);
			g_Block[y][x].SetPosY(y + BLOCK_INIT_Y);
		}
	}
}

/****************************************************
ブロック配列の更新
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
	ブロックの描画
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
	全てのブロックが壊れているかを判定する関数
*****************************************************/
bool BlockArray::AllBlocksBroken()
{
	for (int y = 0; y < BLOCK_NUM_Y; ++y) {
		for (int x = 0; x < BLOCK_NUM_X; ++x) {
			// 1つでも生きていたらFalseを返す
			if (g_Block[y][x].IsDeath() == false)
			{
				return false;
			}
		}
	}

	return true;
}
