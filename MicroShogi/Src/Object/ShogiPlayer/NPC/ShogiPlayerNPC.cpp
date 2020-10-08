#include "ShogiPlayerNPC.h"
#include <stdlib.h>
#include <windows.h>

ShogiPlayerNPC::ShogiPlayerNPC(AttackTurn id_) :
	PlayerBase{ id_ }, m_Priority{ 1 }, m_piece_param{ nullptr }
{
	m_EnemyId = (m_attack_turn == AttackTurn::ATTACK_FIRST) ? AttackTurn::ATTACK_SECOND : AttackTurn::ATTACK_FIRST;
}

bool ShogiPlayerNPC::Update()
{
	// ボード情報取得
	
	m_piece_param = m_ref_shogi_board->GetPieceParam();
	m_Priority = 1;

	while (true)
	{
		SelectSource();
		
		if (SelectDest() == true)break;
		
	}

	m_ref_shogi_board->SetPiece(m_souce_pos, m_dest_pos, m_attack_turn);
	
	Sleep(1500);
	return true;
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
		m_PiecePos.clear();
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				// もし誰の駒なのかの情報があっていたら配列に追加する
				if (m_piece_param[y][x].m_attack_turn == m_attack_turn) {
					m_PiecePos.push_back(IVec2(x, y));
				}
			}
		}
		break;

	case 2:
		m_EnemyPiecePos.clear();
		// 相手の駒の位置を取得する
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				// もし誰の駒なのかの情報があっていたら配列に追加する
				if (m_piece_param[y][x].m_attack_turn == m_EnemyId) {
					m_EnemyPiecePos.push_back(IVec2(x, y));
				}
			}
		}
		break;

	default:
		break;
	}
	
	return true;
}


/*=========================*/
/*　移動先を選択する関数   */
/*=========================*/
bool ShogiPlayerNPC::SelectDest(bool* selected_)
{
	switch (m_Priority)
	{
	case 1:
	{
		// 敵の王の座標を取得
		IVec2 enemy_king_pos;
		bool find_king = false;
		// 自身の王の座標を取得
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				if (m_piece_param[y][x].m_piece_type == PieceType::PIECE_KING
					&& m_piece_param[y][x].m_attack_turn == m_EnemyId) {
					enemy_king_pos.m_X = x;
					enemy_king_pos.m_Y = y;
					find_king = true;
					break;
				}
			}
			if (find_king)break;
		}

		for (int i = 0; i < m_PiecePos.size(); ++i) {
			if (m_ref_shogi_board->CanMove(m_PiecePos[i], enemy_king_pos, m_attack_turn)) {
				m_souce_pos = m_PiecePos[i];
				m_dest_pos  = enemy_king_pos;
				return true;
			}
		}
	}
	break;
	case 2:
	{
	
		IVec2 king_pos(0, 0);
		bool find_king = false;
		// 自身の王の座標を取得
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				if (m_piece_param[y][x].m_piece_type == PieceType::PIECE_KING
					&& m_piece_param[y][x].m_attack_turn == m_attack_turn) {
					king_pos.m_X = x;
					king_pos.m_Y = y;
					find_king = true;
					break;
				}
			}
			if (find_king)break;
		}

		for (int i = 0; i < m_EnemyPiecePos.size(); ++i)
		{
			// もし敵が自身の王を取れるなら
			if (m_ref_shogi_board->CanMove(m_EnemyPiecePos[i], king_pos, m_EnemyId) == true) {
				// 自身の王がその敵を取れるかを調べる
				if (m_ref_shogi_board->CanMove(king_pos, m_EnemyPiecePos[i], m_attack_turn) == true) {
					// 取れるなら取る
					m_souce_pos = king_pos;
					m_dest_pos  = m_EnemyPiecePos[i];
					return true;
				}
				else {
					// 取れない場合ランダムに移動する
					for (int i = 0; i < 10; ++i) {
						// キングをX-> -1 ～ 1   Y-> -1 ～ 1  移動させる
						// 移動できない可能性を考え10回チャレンジする、それでも動けない場合は動かない
						IVec2 king_move{ king_pos.m_X + (rand() % 3 - 1), king_pos.m_Y + (rand() % 3 - 1) };
						if (m_ref_shogi_board->CanMove(king_pos, king_move, m_attack_turn) == true) {
							m_souce_pos = king_pos;
							m_dest_pos  = king_move;
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
		// 敵の駒でとれるものがあればとる
		for (int p = 0; p < m_PiecePos.size(); p++) {
			for (int e = 0; e < m_EnemyPiecePos.size(); e++) {
				
				if (m_ref_shogi_board->CanMove(m_PiecePos[p], m_EnemyPiecePos[e], m_attack_turn) == true)
				{
					m_souce_pos = m_PiecePos[p];
					m_dest_pos  = m_EnemyPiecePos[e];
					return true;
				}
			}
		}		
	}
	break;
	default:
	{
		IVec2 random_souce_pos = m_PiecePos[rand() % m_PiecePos.size()];
		IVec2 random_dest_pos(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);

		if (m_ref_shogi_board->CanMove(random_souce_pos, random_dest_pos, m_attack_turn) == true) {
			m_souce_pos = random_souce_pos;
			m_dest_pos = random_dest_pos;
			return true;
		}
	}
	break;
	}
	
	
	m_Priority++;
	return false;
}
