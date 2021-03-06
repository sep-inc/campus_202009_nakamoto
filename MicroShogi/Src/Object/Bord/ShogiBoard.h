﻿#ifndef SHOGI_BOARD_H_
#define SHOGI_BOARD_H_

#include "../Piece/ShogiPieceBase.h"
#include "PieceOfBoard.h"
#include "../Definition.h"
#include "PieceParam.h"
#include <vector>

/**
* @brief ボードクラス
*/
class ShogiBoard
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiBoard();

	/**
	* @brief   デストラクタ
	*/
	~ShogiBoard(){}

	/**
	* @brief    選択した駒が選択できるかどうかを判定する関数
	* @param[in] pos_  移動したい駒の座標
	* @param[in] id_   先手か後手かの情報
	* @return  bool 選択可能ならtrueを返す
	*/
	bool IsAbleSelectPiece(IVec2 pos_, AttackTurn id_) const;

	/**
	* @brief     選択した場所に移動可能かどうかを判定する関数
	* @param[in] moveSource_    移動元座標
	* @param[in] moveDest_  　　移動先座標
	* @param[in] id_　　　　　　先手か後手かの情報
	* @param[in] isTake_　　　　移動可能状態の時に移動するかどうか
	* @return  bool移動可能ならtrueを返し移動する
	*/
	bool IsAblePutOnTheBoard(IVec2 moveSource_, IVec2 moveDest_, AttackTurn id_);

	/**
	* @brief     指定駒の座標をvectorに詰めて返す関数
	* @param[out] outPos_    駒の座標を受けとるvector
	* @param[in]  id_　　　　先手か後手かのどちら
	*/
	void GetPiecePos(std::vector<IVec2>* outPos_, AttackTurn id_);

	/**
	* @brief     指定した駒の座標を返す関数
	* @param[out] outPos_    駒の座標を返す
	* @param[in]  piece_  　 どの駒を返すか
	* @param[in]  id_　　　　先手か後手かのどちら
	*/
	void GetPiecePos(IVec2* outPos_, PieceType piece_, AttackTurn id_);


	/**
	* @brief     　　王がとられたかどうかを返す関数
	* @return  bool　王がとられていたらtrueを返す
	*/
	inline bool KingWasTake() const { return m_KingWasTake; }

	/**
	* @brief      指定した座標にカーソルを合わせる関数
	* @param[in]  pos_　カーソルの座標
	*/
	inline void SetCursorPos(IVec2 pos_) { m_SelectCursor = pos_; }

	/**
	* @brief     ボードを描画用文字列に変換しバッファにセットする関数
	* @param[in] id_  先手か後手かの情報
	*/
	void Draw();


	bool CanMove(IVec2 souce_, IVec2 dest_, AttackTurn turn_) const;
	void SetPiece(IVec2 souce_, IVec2 dest_, AttackTurn turn_);
	PieceParam(*GetPieceParam())[4]{ return m_piece_param; }

private:
	//! 初期化用の駒の初期位置を保存する変数
	static const PieceOfBoard m_BlankBoard[BOARD_HEIGHT][BOARD_WIDTH];

	//! 先攻のボード
	PieceOfBoard  m_Board[BOARD_HEIGHT][BOARD_WIDTH];
	
	//! キングが取られたかどうかを保存する変数
	bool m_KingWasTake;

	//! 描画用文字列の初期化用の駒の置かれてない空のボード変数
	char m_DrawBlankBoard[BOARD_FRAME_HEIGHT][BOARD_FRAME_WIDTH][CHAR_SIZE];
	
	//! ボードの描画用変数
	char m_DrawBoard[BOARD_FRAME_HEIGHT][BOARD_FRAME_WIDTH][CHAR_SIZE];

	//! カーソルがどこに置かれているかを保存する変数
	IVec2 m_SelectCursor;

	PieceParam m_piece_param[BOARD_HEIGHT][BOARD_WIDTH];

};

#endif