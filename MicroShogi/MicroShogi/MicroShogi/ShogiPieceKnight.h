#ifndef SHOGIPIECEKNIGHT_H_
#define SHOGIPIECEKNIGHT_H_

#include "ShogiPieceBase.h"

/**
* @brief 【駒】桂馬クラス
*/
class ShogiPieceKnight : public ShogiPieceBase
{
public:
	/**
	* @brief   コンストラクタ
	*/
	ShogiPieceKnight() {}

	/**
	* @brief   デストラクタ
	*/
	~ShogiPieceKnight() {}

	/**
	* @brief 移動可能かどうかを判定する関数
	* @param[in] moveVec_ 駒の移動ベクトル
	* @return  bool 可能 : true   不可能 : false
	*/
	bool IsAbleMove(IVec2 moveVec_) const override;

	/**
	* @brief 自身の駒の情報を返す関数
	* @return  const ShogiPiece　自身の駒の種類
	*/
	inline const ShogiPiece GetShogiPiece() const override { return ShogiPiece::PIECE_KNIGHT; }

	/**
	* @brief 駒の描画に必要なリソースを返す関数
	* @param[in] id_ 先手か後手の情報
	* @return  const char* 駒の描画用文字列が返る
	*/
	virtual const char* GetResouce(MoveTrun id_) const override;

private:
	//! 移動可能範囲を保存する変数
	static const bool m_MovableRange[3][3];

};

#endif