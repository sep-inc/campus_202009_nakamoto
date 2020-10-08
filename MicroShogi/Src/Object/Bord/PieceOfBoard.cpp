#include "PieceOfBoard.h"
#include "../Piece/Gold/ShogiPieceGold.h"
#include "../Piece/King/ShogiPieceKing.h"
#include "../Piece/Knight/ShogiPieceKnight.h"
#include "../Piece/Pawn/ShogiPiecePawn.h"


/*===================*/
/*　コンストラクタ   */
/*===================*/
PieceOfBoard::PieceOfBoard() :
	m_Piece{ nullptr }, m_WhosePiece{ MoveTrun::MOVE_NON }
{}


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