#ifndef SHOGIPIECEKING_H_
#define SHOGIPIECEKING_H_

#include "../ShogiPieceBase.h"

/**
* @brief 【駒】王クラス
*/
class ShogiPieceKing : public ShogiPieceBase
{
public:
	/**
	* @brief   コンストラクタ
	*/
	ShogiPieceKing();

	/**
	* @brief   デストラクタ
	*/
	~ShogiPieceKing() {}


	/**
	* @brief 自身の駒の情報を返す関数
	* @return  const ShogiPiece　自身の駒の種類
	*/
	inline const ShogiPiece GetShogiPiece() const override { return ShogiPiece::PIECE_KING; }

	/**
	* @brief 駒の描画に必要なリソースを返す関数
	* @param[in] id_ 先手か後手の情報
	* @return  const char* 駒の描画用文字列が返る
	*/
	virtual const char* GetResouce(MoveTrun id_) const override;

private:
	//! 移動可能範囲を保存する変数
	static const bool m_MovableRange[4][3];

};

#endif