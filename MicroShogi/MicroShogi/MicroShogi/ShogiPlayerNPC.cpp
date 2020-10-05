#include "ShogiPlayerNPC.h"
#include "Definition.h"
#include <stdlib.h>
#include <windows.h>

/*=========================*/
/*　移動元を選択する関数   */
/*=========================*/
bool ShogiPlayerNPC::SelectSource()
{
	// 乱数で移動元を選択する
	m_MoveSource.m_X = rand() % BOARD_WIDTH;
	m_MoveSource.m_Y = rand() % BOARD_HEIGHT;
	
	// ボードに選択できるかどうかを問い合わせた結果を返す
	return m_RefBoard->IsAbleSelectPiece(m_MoveSource, m_Id);
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool ShogiPlayerNPC::SelectDest()
{
	// 乱数で移動先を選択する
	IVec2 move_dest(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);

	// 移動できるかをボードに問い合わせる
	if (m_RefBoard->IsAblePutOnTheBoard(m_MoveSource, move_dest, m_Id) == true){
		// 移動できるなら少しスリープしてtrueを返す
		Sleep(3000);
		return true;
	}
	
	return false;
}
