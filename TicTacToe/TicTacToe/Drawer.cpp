#include "Drawer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// コンストラクタ
Drawer::Drawer()
{
	// フレーム初期化
	for (int y = GRID_FRAME_MIN_X; y < GRID_FRAME_HEIGHT; ++y) {
		for (int x = GRID_FRAME_MIN_Y; x < GRID_FRAME_WIDTH; ++x) {
			// 

			// xが奇数、yが1
			if (x % 2 == 1 && y == 1) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "┳ ");
			}

			// xが奇数、yがフレームの下段
			else if (x % 2 == 1 && y == GRID_FRAME_MAX_Y) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "┻ ");
			}

			// xが左端、yが奇数の時
			else if (x == 1 && y % 2 == 1) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "┣ ");
			}

			// xが右端、yが奇数の時
			else if (x == GRID_FRAME_MAX_X && y % 2 == 1) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "┫ ");
			}

			// xが偶数yが奇数なら
			else if (x % 2 == 0 && y % 2 == 1) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "━ ");
			}

			// xが奇数yが偶数なら
			else if (x % 2 == 1 && y % 2 == 0) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "┃ ");
			}

			// xもyも偶数なら空白
			else if (x % 2 == 0 && y % 2 == 0) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "  ");
			}

			// xもyも奇数なら
			else if (x % 2 == 1 && y % 2 == 1) {
				strcpy_s(m_BlankBuffer[y][x], CHAR_SIZE, "╋ ");
			}
		}

	}

	// 角
	strcpy_s(m_BlankBuffer[GRID_FRAME_MIN_Y][GRID_FRAME_MIN_X], CHAR_SIZE, "┏ ");
	strcpy_s(m_BlankBuffer[GRID_FRAME_MIN_Y][GRID_FRAME_MAX_X], CHAR_SIZE, "┓ ");
	strcpy_s(m_BlankBuffer[GRID_FRAME_MAX_Y][GRID_FRAME_MIN_X], CHAR_SIZE, "┗ ");
	strcpy_s(m_BlankBuffer[GRID_FRAME_MAX_Y][GRID_FRAME_MAX_X], CHAR_SIZE, "┛ ");


	// X軸に対するカウント
	__int8 count_x = 0;
	// Y軸に対するカウント
	__int8 count_y = 0;

	char buf[CHAR_SIZE] = { '\0' };

	for (int x = 0; x < GRID_FRAME_WIDTH; ++x)
	{
		if (x % 2 == 0 && x != 0)
		{
			buf[0] = 'A' + count_x;
			buf[1] = ' ';

			strcpy_s(m_BlankBuffer[0][x], CHAR_SIZE, buf);

			// カウントを進める
			count_x++;
		}
		else {
			strcpy_s(m_BlankBuffer[0][x], CHAR_SIZE, "　");
		}
	}


	for (int y = 0; y < GRID_FRAME_HEIGHT; ++y)
	{
		if (y % 2 == 0 && y != 0) {
			// バッファに文字コードAに対してカウントを足したものを代入する
			buf[0] = '1' + count_y;
			buf[1] = ' ';

			strcpy_s(m_BlankBuffer[y][0], CHAR_SIZE, buf);

			// カウントを進める
			count_y++;
		}
		else {
			strcpy_s(m_BlankBuffer[y][0], CHAR_SIZE, "　");
		}
	}


	// バッファのクリア
	memcpy(m_DrawBuffer, m_BlankBuffer, sizeof(m_BlankBuffer));
}

void Drawer::SetDrawBuffer(__int8 x_, __int8 y_, ObjectType type_)
{
	switch (type_)
	{
	case ObjectType::TYPE_PlAYER:
		
		strcpy_s(m_DrawBuffer[y_ * 2 + 2][x_ * 2 + 2], CHAR_SIZE, "●");

		break;
	case ObjectType::TYPE_ENEMY:

		strcpy_s(m_DrawBuffer[y_ * 2 + 2][x_ * 2 + 2], CHAR_SIZE, "×");

		break;
	default:
		break;
	}
}

void Drawer::ClearBuffer()
{
	system("cls");
	// バッファのクリア
	memcpy(m_DrawBuffer, m_BlankBuffer, sizeof(m_BlankBuffer));
}

void Drawer::DrawBuffer()
{
	// 描画
	for (int y = 0; y < GRID_FRAME_HEIGHT; ++y) {
		for (int x = 0; x < GRID_FRAME_WIDTH; ++x) {

			printf("%s", m_DrawBuffer[y][x]);

		}
		printf("\n");
	}
}
