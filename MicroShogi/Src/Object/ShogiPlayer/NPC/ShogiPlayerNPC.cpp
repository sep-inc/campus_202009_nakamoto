#include "ShogiPlayerNPC.h"
#include <stdlib.h>
#include <windows.h>

ShogiPlayerNPC::ShogiPlayerNPC(ShogiBoard* board_, MoveTrun id_) :
	ShogiPlayerBase{ board_, id_ }, m_Priority{ 1 }
{
	m_EnemyId = (m_Id == MoveTrun::MOVE_FIRST) ? MoveTrun::MOVE_SECOND : MoveTrun::MOVE_FIRST;
}

/*=========================*/
/*　移動元を選択する関数   */
/*=========================*/
bool ShogiPlayerNPC::SelectSource()
{
	switch (m_Priority)
	{
	case 1:
		// 自身の駒の位置を取得する
		m_RefBoard->GetPiecePos(&m_PiecePos, m_Id);
		return true;
		break;

	case 2:
		m_RefBoard->GetPiecePos(&m_EnemyPiecePos, m_EnemyId);
		return true;
		break;

	case 3:
		return true;
		break;

	default:
		break;
	}

	// 乱数で移動元を選択する
	m_MoveSource = m_PiecePos[rand() % m_PiecePos.size()];
	
	// ボードに選択できるかどうかを問い合わせた結果を返す
	return m_RefBoard->IsAbleSelectPiece(m_MoveSource, m_Id);
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool ShogiPlayerNPC::SelectDest()
{
	switch (m_Priority)
	{
	case 1:
	{
		// 敵の王の座標を取得
		IVec2 enemy_king_pos;
		m_RefBoard->GetPiecePos(&enemy_king_pos, ShogiPiece::PIECE_KING, m_EnemyId);

		for (int i = 0; i < m_PiecePos.size(); ++i) {
			if (m_RefBoard->IsAblePutOnTheBoard(m_PiecePos[i], enemy_king_pos, m_Id) == true) {
				Sleep(3000);
				return true;
			}
		}
	}
	break;
	case 2:
	{
		// 自身の王の座標を取得
		IVec2 king_pos;
		m_RefBoard->GetPiecePos(&king_pos, ShogiPiece::PIECE_KING, m_Id);

		for (int i = 0; i < m_EnemyPiecePos.size(); ++i) {
			// もし敵が自身の王を取れるなら
			if (m_RefBoard->IsAblePutOnTheBoard(m_EnemyPiecePos[i], king_pos, m_Id, false) == true) {
				// 自身の王がその敵を取れるかを調べ取れるなら取る
				if (m_RefBoard->IsAblePutOnTheBoard(king_pos, m_EnemyPiecePos[i], m_Id) == true) {
					m_Priority = 1;
					Sleep(3000);
					return true;
				}
				else {
					// 取れなかった場合ランダムに移動する
					for (int i = 0; i < 10; ++i) {
						// キングをX-> -1 ～ 1   Y-> -1 ～ 1  移動させる
						// 移動できない可能性を考え10回チャレンジする、それでも動けない場合は動かない
						IVec2 king_move{ king_pos.m_X + (rand() % 3 - 1), king_pos.m_Y + (rand() % 3 - 1) };
						if (m_RefBoard->IsAblePutOnTheBoard(king_pos, king_move, m_Id) == true) {
							m_Priority = 1;
							Sleep(3000);
							return true;
						}
					}
				}
			}
		}
	}
	break;
	case 3:
	{
		// 敵の駒とれるものがあればとる
		for (int p = 0; p < m_PiecePos.size(); ++p) {
			for (int e = 0; e < m_EnemyPiecePos.size(); ++e) {
				if (m_RefBoard->IsAblePutOnTheBoard(m_PiecePos[p], m_EnemyPiecePos[e], m_Id) == true)
				{
					m_Priority = 1;
					Sleep(3000);
					return true;
				}
			}
		}		
	}
	break;
	case 4:
	{
		if (m_RefBoard->IsAblePutOnTheBoard(m_MoveSource, IVec2(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT), m_Id) == true) {
			m_Priority = 1;
			Sleep(3000);
			return true;
		}
		return false;
	}
	break;
	default:
		break;
	}
	
	
	m_Priority++;
	return false;
}
