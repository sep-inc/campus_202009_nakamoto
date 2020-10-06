#include "ShogiPlayerPC.h"
#include "../../../System/Input.h"
#include <stdio.h>

/*=========================*/
/*　移動元を選択する関数   */
/*=========================*/
bool ShogiPlayerPC::SelectSource()
{
	printf("【移動元の入力】\n");

	while (true)
	{
		printf("横軸を入力してください\n");
		
		int key = Input::GetKey();

		if (key == 'a' || key == 'A')      { m_MoveSource.m_X = 0; break; }
		else if (key == 'b' || key == 'B') { m_MoveSource.m_X = 1; break; }
		else if (key == 'c' || key == 'C') { m_MoveSource.m_X = 2; break; }
		else if (key == 'd' || key == 'D') { m_MoveSource.m_X = 3; break; }
	}

	while (true)
	{
		printf("縦軸を入力してください\n");

		int key = Input::GetKey();

		if (key == '1')      {m_MoveSource.m_Y = 0;	break; }
		else if (key == '2') {m_MoveSource.m_Y = 1;	break; }
		else if (key == '3') {m_MoveSource.m_Y = 2;	break; }
		else if (key == '4') {m_MoveSource.m_Y = 3;	break; }
		else if (key == '5') {m_MoveSource.m_Y = 4;	break; }
	}

	return m_RefBoard->IsAbleSelectPiece(m_MoveSource, m_Id);
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool ShogiPlayerPC::SelectDest()
{
	printf("【移動先の入力】\n");
	IVec2 move_dest{ 0,0 };

	while (true)
	{
		printf("横軸を入力してください\n");

		int key = Input::GetKey();

		if (key == 'a' || key == 'A')      { move_dest.m_X = 0; break; }
		else if (key == 'b' || key == 'B') { move_dest.m_X = 1; break; }
		else if (key == 'c' || key == 'C') { move_dest.m_X = 2; break; }
		else if (key == 'd' || key == 'D') { move_dest.m_X = 3; break; }
	}

	while (true)
	{
		printf("縦軸を入力してください\n");

		int key = Input::GetKey();

		if (key == '1')      { move_dest.m_Y = 0;	break; }
		else if (key == '2') { move_dest.m_Y = 1;	break; }
		else if (key == '3') { move_dest.m_Y = 2;	break; }
		else if (key == '4') { move_dest.m_Y = 3;	break; }
		else if (key == '5') { move_dest.m_Y = 4;	break; }
	}

	return m_RefBoard->IsAblePutOnTheBoard(m_MoveSource, move_dest, m_Id);
}
