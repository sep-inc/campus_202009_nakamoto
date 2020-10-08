#include "PieceOfBoard.h"
#include "../Piece/Gold/ShogiPieceGold.h"
#include "../Piece/King/ShogiPieceKing.h"
#include "../Piece/Knight/ShogiPieceKnight.h"
#include "../Piece/Pawn/ShogiPiecePawn.h"


/*===================*/
/*　コンストラクタ   */
/*===================*/
PieceOfBoard::PieceOfBoard() :
	m_Piece{ nullptr }, m_WhosePiece{ AttackTurn::ATTACK_NONE }
{}


/*===================*/
/*　コンストラクタ   */
/*===================*/
PieceOfBoard::PieceOfBoard(PieceType piece_, AttackTurn id_):
	m_Piece{ nullptr }, m_WhosePiece{ id_ }
{
	switch (piece_)
	{
	case PieceType::PIECE_EMPTY:
		m_Piece = nullptr;
		break;
	case PieceType::PIECE_KING:
		m_Piece = new ShogiPieceKing;
		break;
	case PieceType::PIECE_GOLDGENERAL:
		m_Piece = new ShogiPieceGold;
		break;
	case PieceType::PIECE_KNIGHT:
		m_Piece = new ShogiPieceKnight;
		break;
	case PieceType::PIECE_PAWN:
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