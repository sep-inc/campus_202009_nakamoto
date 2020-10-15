#ifndef SHOGIPIECEGOLD_H_
#define SHOGIPIECEGOLD_H_

#include "../ShogiPieceBase.h"

/**
* @brief 【駒】金クラス
*/
class ShogiPieceGold : public ShogiPieceBase
{
public:
	/**
	* @brief   コンストラクタ
	*/
	ShogiPieceGold();

	/**
	* @brief   デストラクタ
	*/
	~ShogiPieceGold(){}


	/**
	* @brief 自身の駒の情報を返す関数
	* @return  const ShogiPiece　自身の駒の種類
	*/
	inline const PieceType GetShogiPiece() const override { return PieceType::PIECE_GOLDGENERAL; }

	/**
	* @brief 駒の描画に必要なリソースを返す関数
	* @param[in] id_ 先手か後手の情報
	* @return  const char* 駒の描画用文字列が返る
	*/
	virtual const char* GetResouce(AttackTurn id_) const override;

private:
	//! 移動可能範囲を保存する変数
	static const bool m_MovableRangeDB[4][3];

};

#endif