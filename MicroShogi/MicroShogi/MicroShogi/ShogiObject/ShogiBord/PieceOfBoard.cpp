#include "PieceOfBoard.h"
#include "../ShogiPiece/Gold/ShogiPieceGold.h"
#include "../ShogiPiece/King/ShogiPieceKing.h"
#include "../ShogiPiece/Knight/ShogiPieceKnight.h"
#include "../ShogiPiece/Pawn/ShogiPiecePawn.h"


/*===================*/
/*　コンストラクタ   */
/*===================*/
PieceOfBoard::PieceOfBoard(ShogiPiece piece_, MoveTrun id_):
	m_Piece{ nullptr }, m_WhosePiece{ id_ }
{
	switch (piece_)
	{
	case ShogiPiece::PIECE_EMPTY:
		m_Piece = nullptr;
		break;
	case ShogiPiece::PIECE_KING:
		m_Piece = new ShogiPieceKing;
		break;
	case ShogiPiece::PIECE_GOLD:
		m_Piece = new ShogiPieceGold;
		break;
	case ShogiPiece::PIECE_KNIGHT:
		m_Piece = new ShogiPieceKnight;
		break;
	case ShogiPiece::PIECE_PAWN:
		m_Piece = new ShogiPiecePawn;
		break;
	default:
		break;
	}
}

/*===================*/
/*　　デストラクタ   */
/*===================*/
PieceOfBoard::~PieceOfBoard()
{
	SAFE_DELETE(m_Piece);
}