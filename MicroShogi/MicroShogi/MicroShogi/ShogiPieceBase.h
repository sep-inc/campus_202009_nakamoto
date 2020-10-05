#ifndef SHOGIPIECEBASE_H_
#define SHOGIPIECEBASE_H_

#include "Definition.h"
#include "IVec2.h"

/**
* @brief 将棋の駒の基底クラス
*/
class ShogiPieceBase
{
public:
	/**
	* @brief   コンストラクタ
	*/
	ShogiPieceBase(){}

	/**
	* @brief   デストラクタ
	*/
	~ShogiPieceBase(){}

	/**
	* @brief 移動可能かどうかを判定する関数
	* @param[in] moveVec_ 駒の移動ベクトル
	* @return  bool 可能 : true   不可能 : false
	*/
	virtual bool IsAbleMove(IVec2 moveVec_) const = 0;

	/**
	* @brief 自身の駒の情報を返す関数
	* @return  const ShogiPiece　自身の駒の種類
	*/
	virtual inline const ShogiPiece GetShogiPiece() const = 0;

	/**
	* @brief 駒の描画に必要なリソースを返す関数
	* @param[in] id_ 先手か後手の情報
	* @return  const char* 駒の描画用文字列が返る
	*/
	virtual const char* GetResouce(MoveTrun id_) const = 0;

};

#endif