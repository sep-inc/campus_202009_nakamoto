#ifndef SHOGI_PLAYER_PC_H_
#define SHOGI_PLAYER_PC_H_

#include "../ShogiPlayerBase.h"
#include <string>

/**
* @brief 【棋士】PCクラス
*/
class ShogiPlayerPC : public ShogiPlayerBase
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiPlayerPC(ShogiBoard* board_, MoveTrun id_);

	/**
	* @brief   デストラクタ
	*/
	~ShogiPlayerPC() {}

private:
	/**
	* @brief   移動元を選択する関数
	* @return  bool 選択可能ならtrueを返す
	*/
	bool SelectSource() override;

	/**
	* @brief   移動元を選択する関数
	* @return  bool 選択可能ならtrueを返す
	*/
	bool SelectDest() override;

private:
	//! 先手か後手かを文字列で保存する変数
	std::string m_Name;

};


#endif