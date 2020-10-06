#include "ShogiPlayerPC.h"
#include "../../../System/Input.h"
#include <stdio.h>

/*=========================*/
/*　移動元を選択する関数   */
/*=========================*/
bool ShogiPlayerPC::SelectSource()
{
	printf("十字キーで選択\n");
	printf("【移動元の入力】\n");

	IVec2 select_unit(0, 0);

	while (true)
	{
		COORD cursor_pos{ select_unit.m_X * 4 + 4, select_unit.m_Y * 2 + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
		int key = Input::GetKey();

		if (key == 77)      { select_unit.m_X++; }
		else if (key == 75) { select_unit.m_X--; }
		else if (key == 80) { select_unit.m_Y++; }
		else if (key == 72) { select_unit.m_Y--; }
		else if (key == 32) {
			m_MoveSource.m_X = select_unit.m_X;
			m_MoveSource.m_Y = select_unit.m_Y;
			break;
		}

		if (select_unit.m_X < 0) select_unit.m_X = 0;
		if (select_unit.m_X > 3) select_unit.m_X = 3;
		if (select_unit.m_Y < 0) select_unit.m_Y = 0;
		if (select_unit.m_Y > 4) select_unit.m_Y = 4;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 1 });
	return m_RefBoard->IsAbleSelectPiece(m_MoveSource, m_Id);
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool ShogiPlayerPC::SelectDest()
{
	printf("十字キーで選択\n");
	printf("移動元->横[%c],縦[%c]\n", 'A' + m_MoveSource.m_X, '1' + m_MoveSource.m_Y);
	printf("【移動先の入力】\n");
	IVec2 select_unit{ 0,0 };

	while (true)
	{
		COORD cursor_pos{ select_unit.m_X * 4 + 4, select_unit.m_Y * 2 + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
		int key = Input::GetKey();

		if (key == 77) { select_unit.m_X++; }
		else if (key == 75) { select_unit.m_X--; }
		else if (key == 80) { select_unit.m_Y++; }
		else if (key == 72) { select_unit.m_Y--; }
		else if (key == 32) {
			break;
		}

		if (select_unit.m_X < 0) select_unit.m_X = 0;
		if (select_unit.m_X > 3) select_unit.m_X = 3;
		if (select_unit.m_Y < 0) select_unit.m_Y = 0;
		if (select_unit.m_Y > 4) select_unit.m_Y = 4;
	}


	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 3 });
	printf("\r                                    \r");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 2 });
	printf("\r                                    \r");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 1 });
	printf("\r                                    \r");
	return m_RefBoard->IsAblePutOnTheBoard(m_MoveSource, select_unit, m_Id);
}
