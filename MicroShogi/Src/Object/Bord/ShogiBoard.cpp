#include "ShogiBoard.h"
#include "../../System/Drawer.h"
#include <string.h>

using SP = PieceType;
using MT = AttackTurn;

// 初期化用の駒の初期位置を保存する変数
const PieceOfBoard ShogiBoard::m_BlankBoard[BOARD_HEIGHT][BOARD_WIDTH] =
{
	{{SP::PIECE_EMPTY, MT::ATTACK_NONE   },{SP::PIECE_KING, MT::ATTACK_SECOND},{SP::PIECE_GOLDGENERAL, MT::ATTACK_SECOND},{SP::PIECE_KNIGHT,MT::ATTACK_SECOND}},
	{{SP::PIECE_PAWN,  MT::ATTACK_SECOND},{SP::PIECE_PAWN, MT::ATTACK_SECOND},{SP::PIECE_PAWN, MT::ATTACK_SECOND},{SP::PIECE_PAWN, MT::ATTACK_SECOND }},
	{{SP::PIECE_EMPTY, MT::ATTACK_NONE   },{SP::PIECE_EMPTY,MT::ATTACK_NONE   },{SP::PIECE_EMPTY,MT::ATTACK_NONE   },{SP::PIECE_EMPTY,MT::ATTACK_NONE    }},
	{{SP::PIECE_PAWN,  MT::ATTACK_FIRST },{SP::PIECE_PAWN, MT::ATTACK_FIRST },{SP::PIECE_PAWN, MT::ATTACK_FIRST },{SP::PIECE_PAWN, MT::ATTACK_FIRST  }},
	{{SP::PIECE_KNIGHT,MT::ATTACK_FIRST },{SP::PIECE_GOLDGENERAL, MT::ATTACK_FIRST },{SP::PIECE_KING, MT::ATTACK_FIRST },{SP::PIECE_EMPTY,MT::ATTACK_NONE    }},
};

/*==================*/
/*　コンストラクタ  */
/*==================*/
ShogiBoard::ShogiBoard() :
	m_Board{}, m_KingWasTake{ false }, m_DrawBoard{ 0 }, m_SelectCursor{ 0,0 }
{
	// 先手のボードを初期化
	memcpy(&m_Board, m_BlankBoard, sizeof(m_BlankBoard));

	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			m_piece_param[y][x].m_attack_turn = m_Board[y][x].m_WhosePiece;
			if (m_Board[y][x].m_Piece == nullptr) {
				m_piece_param[y][x].m_piece_type = PieceType::PIECE_EMPTY;
			}
			else m_piece_param[y][x].m_piece_type  = m_Board[y][x].m_Piece->GetShogiPiece();
		}
	}

#pragma region 描画用ボードの初期化

	// フレーム初期化
	for (int y = BOARD_FRAME_MIN_X; y < BOARD_FRAME_HEIGHT; ++y) {
		for (int x = BOARD_FRAME_MIN_Y; x < BOARD_FRAME_WIDTH; ++x) {
			// 

			// xが奇数、yが1
			if (x % 2 == 1 && y == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┬ ");
			}

			// xが奇数、yがフレームの下段
			else if (x % 2 == 1 && y == BOARD_FRAME_MAX_Y) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┴ ");
			}

			// xが左端、yが奇数の時
			else if (x == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "├ ");
			}

			// xが右端、yが奇数の時
			else if (x == BOARD_FRAME_MAX_X && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┤ ");
			}

			// xが偶数yが奇数なら
			else if (x % 2 == 0 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "─ ");
			}

			// xが奇数yが偶数なら
			else if (x % 2 == 1 && y % 2 == 0) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "│ ");
			}

			// xもyも偶数なら空白
			else if (x % 2 == 0 && y % 2 == 0) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "  ");
			}

			// xもyも奇数なら
			else if (x % 2 == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankBoard[y][x], CHAR_SIZE, "┼ ");
			}
		}

	}

	// 角
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MIN_Y][BOARD_FRAME_MIN_X], CHAR_SIZE, "┌ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MIN_Y][BOARD_FRAME_MAX_X], CHAR_SIZE, "┐ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MAX_Y][BOARD_FRAME_MIN_X], CHAR_SIZE, "└ ");
	strcpy_s(m_DrawBlankBoard[BOARD_FRAME_MAX_Y][BOARD_FRAME_MAX_X], CHAR_SIZE, "┘ ");


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
bool ShogiBoard::IsAbleSelectPiece(IVec2 pos_, AttackTurn id_) const
{	
	// もし選んだ駒が自分の駒以外なら選べない
	if (m_Board[pos_.m_Y][pos_.m_X].m_WhosePiece != id_) {
		return false;
	}	

	return true;
}


/*=================================================*/
/*　選択した場所に移動可能かどうかを判定する関数   */
/*=================================================*/
bool ShogiBoard::IsAblePutOnTheBoard(IVec2 moveSource_, IVec2 moveDest_, AttackTurn id_)
{
	if (moveDest_.m_X < 0) return false;
	if (moveDest_.m_X >= BOARD_WIDTH) return false;
	if (moveDest_.m_Y < 0) return false;
	if (moveDest_.m_X >= BOARD_HEIGHT) return false;

	// 移動元を保存する変数
	IVec2 select_source = moveSource_;
	// 移動先を保存する変数
	IVec2 select_dest   = moveDest_;

	// 移動先が自分の駒なら移動しない
	if (m_Board[select_dest.m_Y][select_dest.m_X].m_WhosePiece == id_) return false;

	// 移動元から移動先へのベクトルを保存する変数
	IVec2 move_vec(0,0);
	move_vec.m_X = select_dest.m_X - select_source.m_X;
	move_vec.m_Y = select_dest.m_Y - select_source.m_Y;

	// 後手なら移動ベクトルを反転させる
	if (id_ == AttackTurn::ATTACK_SECOND) {
		move_vec.m_X = -move_vec.m_X;
		move_vec.m_Y = -move_vec.m_Y;
	}

	// 駒に移動できるかを問い合わせる
	if (m_Board[select_source.m_Y][select_source.m_X].m_Piece->IsAbleMove(move_vec) == false) return false;


	// 移動先が王なら王がとられたフラグをオンにする
	if (m_Board[select_dest.m_Y][select_dest.m_X].m_Piece != nullptr) {
		if (m_Board[select_dest.m_Y][select_dest.m_X].m_Piece->GetShogiPiece() == PieceType::PIECE_KING) m_KingWasTake = true;
	}
	
	// 移動先に移動元情報を保存する
	m_Board[select_dest.m_Y][select_dest.m_X]       = m_Board[select_source.m_Y][select_source.m_X];
	m_piece_param[select_dest.m_Y][select_dest.m_X] = m_piece_param[select_source.m_Y][select_source.m_X];

	// 移動元情報をクリアする
	m_Board[select_source.m_Y][select_source.m_X].m_Piece      = nullptr;
	m_Board[select_source.m_Y][select_source.m_X].m_WhosePiece = AttackTurn::ATTACK_NONE;

	m_piece_param[select_source.m_Y][select_source.m_X].m_piece_type  = PieceType::PIECE_EMPTY;
	m_piece_param[select_source.m_Y][select_source.m_X].m_attack_turn = AttackTurn::ATTACK_NONE;

	return true;
}

void ShogiBoard::GetPiecePos(std::vector<IVec2>* outPos_, AttackTurn id_)
{
	std::vector<IVec2> out_vec;

	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			// もし誰の駒なのかの情報があっていたら配列に追加する
			if (m_Board[y][x].m_WhosePiece == id_) {
				out_vec.push_back(IVec2(x, y));
			}
		}
	}

	*outPos_ = out_vec;
}

void ShogiBoard::GetPiecePos(IVec2* outPos_, PieceType piece_, AttackTurn id_)
{
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			// もしピースの種類と誰の駒なのかがあっていたら保存する
			if (m_Board[y][x].m_WhosePiece == id_ && m_Board[y][x].m_Piece->GetShogiPiece() == piece_) {
				outPos_->m_X = x;
				outPos_->m_Y = y;
				return;
			}
		}
	}
}


/*=========================================================*/
/*　 ボードを描画用文字列に変換しバッファにセットする関数  */
/*=========================================================*/
void ShogiBoard::Draw()
{
	std::string draw_str;

	memcpy(m_DrawBoard, m_DrawBlankBoard, sizeof(m_DrawBlankBoard));

	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			if (m_Board[y][x].m_Piece == nullptr) {
				strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], "　");
				continue;
			}
			strcpy_s(m_DrawBoard[y * 2 + 2][x * 2 + 2], m_Board[y][x].m_Piece->GetResouce(m_Board[y][x].m_WhosePiece));
		}
	}

	static int flush_count = 0;

	static bool is_flush = true;
	if (is_flush) {
		strcpy_s(m_DrawBoard[m_SelectCursor.m_Y * 2 + 2 + 1][m_SelectCursor.m_X * 2 + 2], "━ ");
		strcpy_s(m_DrawBoard[m_SelectCursor.m_Y * 2 + 2 - 1][m_SelectCursor.m_X * 2 + 2], "━ ");
		strcpy_s(m_DrawBoard[m_SelectCursor.m_Y * 2 + 2][m_SelectCursor.m_X * 2 + 2 + 1], "┃ ");
		strcpy_s(m_DrawBoard[m_SelectCursor.m_Y * 2 + 2][m_SelectCursor.m_X * 2 + 2 - 1], "┃ ");		
	}
	
	flush_count++;
	if (flush_count % CURSOR_FLASH_TIME == 0) {
		is_flush = !is_flush;
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

bool ShogiBoard::CanMove(IVec2 souce_, IVec2 dest_, AttackTurn turn_) const
{
	if (m_Board[souce_.m_Y][souce_.m_X].m_Piece == nullptr) {
		return false;
	}

	if (m_Board[dest_.m_Y][dest_.m_X].m_WhosePiece == turn_) {
		return false;
	}

	IVec2 move_vec(0, 0);
	move_vec.m_X = dest_.m_X - souce_.m_X;
	move_vec.m_Y = dest_.m_Y - souce_.m_Y;
	
	if (turn_ == AttackTurn::ATTACK_SECOND) {
		move_vec.m_X = -move_vec.m_X;
		move_vec.m_Y = -move_vec.m_Y;
	}

	return m_Board[souce_.m_Y][souce_.m_X].m_Piece->IsAbleMove(move_vec);
}

void ShogiBoard::SetPiece(IVec2 souce_, IVec2 dest_, AttackTurn turn_)
{
	// 移動先が王なら王がとられたフラグをオンにする
	if (m_Board[dest_.m_Y][dest_.m_X].m_Piece != nullptr) {
		if (m_Board[dest_.m_Y][dest_.m_X].m_Piece->GetShogiPiece() == PieceType::PIECE_KING) m_KingWasTake = true;
	}

	// 移動先に移動元情報を保存する
	m_Board[dest_.m_Y][dest_.m_X]       = m_Board[souce_.m_Y][souce_.m_X];
	m_piece_param[dest_.m_Y][dest_.m_X] = m_piece_param[souce_.m_Y][souce_.m_X];


	// 移動元情報をクリアする
	m_Board[souce_.m_Y][souce_.m_X].m_Piece      = nullptr;
	m_Board[souce_.m_Y][souce_.m_X].m_WhosePiece = AttackTurn::ATTACK_NONE;

	m_piece_param[souce_.m_Y][souce_.m_X].m_piece_type  = PieceType::PIECE_EMPTY;
	m_piece_param[souce_.m_Y][souce_.m_X].m_attack_turn = AttackTurn::ATTACK_NONE;

}
