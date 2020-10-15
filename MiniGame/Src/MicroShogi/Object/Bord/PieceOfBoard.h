#ifndef PIECEOFBOARD_H
#define PIECEOFBOARD_H
#include "../Piece/ShogiPieceBase.h"

/**
* @brief   ボードに置かれる駒の情報をまとめた構造体
*/
struct PieceOfBoard
{
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	PieceOfBoard();
	
	/**
	* @brief デストラクタ
	* @details 確保したピースのデータを解放する
	*/
	~PieceOfBoard();

	/**
	* @brief   引数付きコンストラクタ
	* @details 必要な情報を特定の情報で初期化する
	*/
	PieceOfBoard(PieceType piece_, AttackTurn id_);

	//! どの駒なのかを保存する変数
	ShogiPieceBase* m_Piece;
	
	//! 誰の駒なのかを保存する変数
	AttackTurn        m_WhosePiece;
};

#endif