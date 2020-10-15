#include "ShogiPlayerPC.h"
#include "../../../../System/Input.h"
#include <stdio.h>

/*=========================*/
/*　    コンストラクタ     */
/*=========================*/
MicroShogi::ShogiPlayerPC::ShogiPlayerPC(AttackTurn id_) :
	PlayerBase{ id_ }, m_SelectCursor{ IVec2(0,0) }
{
	if (id_ == AttackTurn::ATTACK_FIRST) { m_Name = "先手"; }
	else { m_Name = "後手"; }
}

/*=========================*/
/*　移動元を選択する関数   */
/*=========================*/
bool MicroShogi::ShogiPlayerPC::SelectSource()
{
	printf("%sの番です\n", m_Name.c_str());
	printf("十字キーでカーソルの移動  Spaceで決定\n");
	printf("【移動させたい駒を選択してください】\n");

	IVec2 cursr_pos = m_SelectCursor.GetCursorPos();
	const int board_width_end  = BOARD_WIDTH  - 1;
	const int board_height_end = BOARD_HEIGHT - 1;
	
	int key = Input::GetKey();
	
	if (key == KEY_RIGHT)      { cursr_pos.m_X++; }
	else if (key == KEY_LEFT)  { cursr_pos.m_X--; }
	else if (key == KEY_DOWN)  { cursr_pos.m_Y++; }
	else if (key == KEY_UP)    { cursr_pos.m_Y--; }
	else if (key == KEY_SPACE) {
		m_souce_pos.m_X = m_SelectCursor.GetCursorPos().m_X;
		m_souce_pos.m_Y = m_SelectCursor.GetCursorPos().m_Y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 3 });
		printf("\r                         　　　           \r");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 2 });
		printf("\r                         　　　           \r");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 1 });
		printf("\r                            　　　        \r");

		return m_ref_shogi_board->IsAbleSelectPiece(m_souce_pos, m_attack_turn);
	}
	
	if (cursr_pos.m_X < 0)				  cursr_pos.m_X = 0;
	if (cursr_pos.m_X > board_width_end)  cursr_pos.m_X = board_width_end;
	if (cursr_pos.m_Y < 0)				  cursr_pos.m_Y = 0;
	if (cursr_pos.m_Y > board_height_end) cursr_pos.m_Y = board_height_end;

	m_SelectCursor.SetCursorPos(cursr_pos);

	m_ref_shogi_board->SetCursorPos(m_SelectCursor.GetCursorPos());

	return false;
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool MicroShogi::ShogiPlayerPC::SelectDest(bool* selected_)
{
	printf("%sの番です\n", m_Name.c_str());
	printf("十字キーでカーソルの移動  Spaceで決定\n");
	printf("移動元->横[%c],縦[%c]\n", 'A' + m_souce_pos.m_X, '1' + m_souce_pos.m_Y);
	printf("【移動させたい場所を選択してください】\n");

	IVec2 cursr_pos = m_SelectCursor.GetCursorPos();
	const int board_width_end  = BOARD_WIDTH  - 1;
	const int board_height_end = BOARD_HEIGHT - 1;

	int key = Input::GetKey();

	if (key == KEY_RIGHT)      { cursr_pos.m_X++; }
	else if (key == KEY_LEFT)  { cursr_pos.m_X--; }
	else if (key == KEY_DOWN)  { cursr_pos.m_Y++; }
	else if (key == KEY_UP)    { cursr_pos.m_Y--; }
	else if (key == KEY_SPACE) {

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 4 });
		printf("\r                         　　　           \r");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 3 });
		printf("\r                         　　　           \r");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 2 });
		printf("\r                            　　　        \r");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,BOARD_FRAME_HEIGHT + 1 });
		printf("\r                           　　　         \r");

		if (m_ref_shogi_board->IsAblePutOnTheBoard(m_souce_pos, m_SelectCursor.GetCursorPos(), m_attack_turn) == true) {
			
			return true;
		}
		if (selected_) *selected_ = true;
		return false;
	}

	if (cursr_pos.m_X < 0)				  cursr_pos.m_X = 0;
	if (cursr_pos.m_X > board_width_end)  cursr_pos.m_X = board_width_end;
	if (cursr_pos.m_Y < 0)				  cursr_pos.m_Y = 0;
	if (cursr_pos.m_Y > board_height_end) cursr_pos.m_Y = board_height_end;
	m_SelectCursor.SetCursorPos(cursr_pos);

	m_ref_shogi_board->SetCursorPos(m_SelectCursor.GetCursorPos());
	
	if (selected_) *selected_ = false;

	return false;
}
