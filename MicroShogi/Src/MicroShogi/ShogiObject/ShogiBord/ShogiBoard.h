#ifndef SHOGI_BOARD_H_
#define SHOGI_BOARD_H_

#include "../ShogiPiece/ShogiPieceBase.h"
#include "PieceOfBoard.h"
#include "../Definition.h"

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
	bool IsAbleSelectPiece(IVec2 pos_, MoveTrun id_);

	/**
	* @brief     選択した場所に移動可能かどうかを判定する関数
	* @param[in] moveSource_    移動元座標
	* @param[in] moveDest_  　　移動先座標
	* @param[in] id_　　　　　　先手か後手かの情報
	* @return  bool移動可能ならtrueを返し移動する
	*/
	bool IsAblePutOnTheBoard(IVec2 moveSource_, IVec2 moveDest_, MoveTrun id_);
	
	/**
	* @brief     　　王がとられたかどうかを返す関数
	* @return  bool　王がとられていたらtrueを返す
	*/
	inline bool KingWasTake() const { return m_KingWasTake; }

	/**
	* @brief     ボードを描画用文字列に変換しバッファにセットする関数
	* @param[in] id_  先手か後手かの情報
	*/
	void Draw();

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
	
};

#endif