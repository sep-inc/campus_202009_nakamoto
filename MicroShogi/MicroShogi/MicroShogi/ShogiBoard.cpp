﻿#include "ShogiBoard.h"
#include "Drawer.h"
#include <string.h>

using SP = ShogiPiece;
using MT = MoveTrun;

// 初期化用の駒の初期位置を保存する変数
const PieceOfBoard ShogiBoard::m_BlankBoard[BOARD_HEIGHT][BOARD_WIDTH] =
{
	{{SP::PIECE_EMPTY, MT::MOVE_NON   },{SP::PIECE_KING, MT::MOVE_SECOND},{SP::PIECE_GOLD, MT::MOVE_SECOND},{SP::PIECE_KNIGHT,MT::MOVE_SECOND}},
	{{SP::PIECE_PAWN,  MT::MOVE_SECOND},{SP::PIECE_PAWN, MT::MOVE_SECOND},{SP::PIECE_PAWN, MT::MOVE_SECOND},{SP::PIECE_PAWN, MT::MOVE_SECOND }},
	{{SP::PIECE_EMPTY, MT::MOVE_NON   },{SP::PIECE_EMPTY,MT::MOVE_NON   },{SP::PIECE_EMPTY,MT::MOVE_NON   },{SP::PIECE_EMPTY,MT::MOVE_NON    }},
	{{SP::PIECE_PAWN,  MT::MOVE_FIRST },{SP::PIECE_PAWN, MT::MOVE_FIRST },{SP::PIECE_PAWN, MT::MOVE_FIRST },{SP::PIECE_PAWN, MT::MOVE_FIRST  }},
	{{SP::PIECE_KNIGHT,MT::MOVE_FIRST },{SP::PIECE_GOLD, MT::MOVE_FIRST },{SP::PIECE_KING, MT::MOVE_FIRST },{SP::PIECE_EMPTY,MT::MOVE_NON    }},
};

/*==================*/
/*　コンストラクタ  */
/*==================*/
ShogiBoard::ShogiBoard() :
	m_FirstBoard{}, m_SecondBoard{ nullptr }, m_KingWasTake{ false }
{
	// 先手のボードを初期化
	memcpy(&m_FirstBoard, m_BlankBoard, sizeof(m_BlankBoard));

	const int board_width_end  = BOARD_WIDTH  - 1;
	const int board_height_end = BOARD_HEIGHT - 1;

	// 後手のボードを変換して初期化
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			m_SecondBoard[board_height_end - y][board_width_end - x] = &m_FirstBoard[y][x];
		}
	}

#pragma region 描画用ボードの初期化

	// フレーム初期化
	for (int y = BOARD_FRAME_MIN_X; y < BOARD_FRAME_HEIGHT; ++y) {
		for (int x = BOARD_FRAME_MIN_Y; x < BOARD_FRAME_WIDTH; ++x) {
			// 

			// xが奇数、yが1
			if (x % 2 == 1 && y == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┳ ");
			}

			// xが奇数、yがフレームの下段
			else if (x % 2 == 1 && y == BOARD_FRAME_MAX_Y) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┻ ");
			}

			// xが左端、yが奇数の時
			else if (x == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┣ ");
			}

			// xが右端、yが奇数の時
			else if (x == BOARD_FRAME_MAX_X && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┫ ");
			}

			// xが偶数yが奇数なら
			else if (x % 2 == 0 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "━ ");
			}

			// xが奇数yが偶数なら
			else if (x % 2 == 1 && y % 2 == 0) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┃ ");
			}

			// xもyも偶数なら空白
			else if (x % 2 == 0 && y % 2 == 0) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "  ");
			}

			// xもyも奇数なら
			else if (x % 2 == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "╋ ");
			}
		}

	}

	// 角
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MIN_Y][BOARD_FRAME_MIN_X], CHAR_SIZE, "┏ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MIN_Y][BOARD_FRAME_MAX_X], CHAR_SIZE, "┓ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MAX_Y][BOARD_FRAME_MIN_X], CHAR_SIZE, "┗ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MAX_Y][BOARD_FRAME_MAX_X], CHAR_SIZE, "┛ ");


	// X軸に対するカウント
	__int8 count_x = 0;
	// Y軸に対するカウント
	__int8 count_y = 0;

	char buf[CHAR_SIZE] = { '\0' };

	for (int x = 0; x < BOARD_FRAME_WIDTH; ++x)
	{
		if (x % 2 == 0 && x != 0)
		{
			buf[0] = 'A' + count_x;
			buf[1] = ' ';

			strcpy_s(m_DrawBlankBoard[0][x], CHAR_SIZE, buf);

			// カウントを進める
			count_x++;
		}
		else {
			strcpy_s(m_DrawBlankBoard[0][x], CHAR_SIZE, "　");
		}
	}


	for (int y = 0; y < BOARD_FRAME_HEIGHT; ++y)
	{
		if (y % 2 == 0 && y != 0) {
			// バッファに文字コードAに対してカウントを足したものを代入する
			buf[0] = '1' + count_y;
			buf[1] = ' ';

			strcpy_s(m_DrawBlankBoard[y][0], CHAR_SIZE, buf);

			// カウントを進める
			count_y++;
		}
		else {
			strcpy_s(m_DrawBlankBoard[y][0], CHAR_SIZE, "　");
		}
	}

#pragma endregion

}


/*=================================================*/
/*　選択した駒が選択できるかどうかを判定する関数   */
/*=================================================*/
bool ShogiBoard::IsAbleSelectPiece(IVec2 pos_, MoveTrun id_)
{	
	const int board_width_unit  = BOARD_WIDTH  - 1;
	const int board_height_unit = BOARD_HEIGHT - 1;
	
	IVec2 select_source(0, 0);
	// 後手なら変換をかける
	if (id_ == MoveTrun::MOVE_FIRST) select_source = pos_;
	else {
		select_source.m_X = board_width_unit  - pos_.m_X;
		select_source.m_Y = board_height_unit - pos_.m_Y;
	}

	// もし選んだ駒が自分の駒以外なら選べない
	if (m_FirstBoard[select_source.m_Y][select_source.m_X].m_WhosePiece != id_) {
		return false;
	}	

	return true;
}


/*=================================================*/
/*　選択した場所に移動可能かどうかを判定する関数   */
/*=================================================*/
bool ShogiBoard::IsAblePutOnTheBoard(IVec2 moveSource_, IVec2 moveDest_, MoveTrun id_)
{
	const int board_width_end  = BOARD_WIDTH  - 1;
	const int board_height_end = BOARD_HEIGHT - 1;

	// 移動元を保存する変数
	IVec2 select_source(0, 0);
	// 移動先を保存する変数
	IVec2 select_dest(0, 0);

	if (id_ == MoveTrun::MOVE_FIRST) {
		select_source = moveSource_;
		select_dest   = moveDest_;
	}
	// 後手なら変換をかける
	else {
		select_source.m_X = board_width_end  - moveSource_.m_X;
		select_source.m_Y = board_height_end - moveSource_.m_Y;
		select_dest.m_X   = board_width_end  - moveDest_.m_X;
		select_dest.m_Y   = board_height_end - moveDest_.m_Y;
	}

	// 移動先が自分の駒なら移動しない
	if (m_FirstBoard[select_dest.m_Y][select_dest.m_X].m_WhosePiece == id_) return false;

	// 移動元から移動先へのベクトルを保存する変数
	IVec2 move_vec(0,0);

	if (id_ == MoveTrun::MOVE_FIRST) {
		move_vec.m_X = select_dest.m_X - select_source.m_X;
		move_vec.m_Y = select_dest.m_Y - select_source.m_Y;
	}
	else {
		// 後手ならベクトルを反転させる
		move_vec.m_X = select_source.m_X - select_dest.m_X;
		move_vec.m_Y = select_source.m_Y - select_dest.m_Y;
	}

	// 駒に移動できるかを問い合わせる
	if (m_FirstBoard[select_source.m_Y][select_source.m_X].m_Piece->IsAbleMove(move_vec) == false) return false;
	
	// 移動先が王なら王がとられたフラグをオンにする
	if (m_FirstBoard[select_dest.m_Y][select_dest.m_X].m_Piece != nullptr) {
		if (m_FirstBoard[select_dest.m_Y][select_dest.m_X].m_Piece->GetShogiPiece() == ShogiPiece::PIECE_KING) m_KingWasTake = true;
	}
	
	// 移動先に移動元情報を保存する
	m_FirstBoard[select_dest.m_Y][select_dest.m_X] = m_FirstBoard[select_source.m_Y][select_source.m_X];

	// 移動元情報をクリアする
	m_FirstBoard[select_source.m_Y][select_source.m_X].m_Piece      = nullptr;
	m_FirstBoard[select_source.m_Y][select_source.m_X].m_WhosePiece = MoveTrun::MOVE_NON;

	return true;
}


/*=========================================================*/
/*　 ボードを描画用文字列に変換しバッファにセットする関数  */
/*=========================================================*/
void ShogiBoard::Draw(MoveTrun id_)
{
	std::string draw_str;

	memcpy(m_DrawBoard, m_DrawBlankBoard, sizeof(m_DrawBlankBoard));
	
	// ボードの駒からリソースをもらい文字列を保存する
	if (id_ == MoveTrun::MOVE_FIRST) {
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				if (m_FirstBoard[y][x].m_Piece == nullptr) {
					strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], "　");
					continue;
				}
				strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], m_FirstBoard[y][x].m_Piece->GetResouce(m_FirstBoard[y][x].m_WhosePiece));
			}
		}
	}
	else {
		for (int y = 0; y < BOARD_HEIGHT; ++y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				if (m_SecondBoard[y][x]->m_Piece == nullptr) {
					strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], "　");
					continue;
				}
				strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], m_SecondBoard[y][x]->m_Piece->GetResouce(m_SecondBoard[y][x]->m_WhosePiece));
			}
		}
	}


	// string型に変換する
	for (int y = 0; y < BOARD_FRAME_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_FRAME_WIDTH; ++x) {
			draw_str += m_DrawBoard[y][x];
		}
		draw_str += "\n";
	}

	// 描画クラスのバッファに保存する
	Drawer::GetInstance().SetDrawBuffer(draw_str);
}