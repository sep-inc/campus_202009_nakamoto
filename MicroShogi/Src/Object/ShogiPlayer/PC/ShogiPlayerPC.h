#ifndef SHOGI_PLAYER_PC_H_
#define SHOGI_PLAYER_PC_H_

#include "../PlayerBase.h"
#include "../../Cursor.h"
#include <string>

namespace MicroShogi
{
	/**
* @brief 【棋士】PCクラス
*/
	class ShogiPlayerPC : public PlayerBase
	{
	public:
		/**
		* @brief   コンストラクタ
		* @details 必要な情報を初期化する
		*/
		ShogiPlayerPC(AttackTurn id_);

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
		bool SelectDest(bool* selected_ = nullptr) override;

	private:
		//! 先手か後手かを文字列で保存する変数
		std::string m_Name;

		//! どこを選択しているかを保存する変数
		Cursor m_SelectCursor;

	};
}


#endif