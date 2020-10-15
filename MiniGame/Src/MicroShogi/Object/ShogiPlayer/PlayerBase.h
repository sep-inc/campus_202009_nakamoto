#ifndef ShogiPlayerBase_H_
#define ShogiPlayerBase_H_

#include "../Definition.h"
#include "../Bord/ShogiBoard.h"

namespace MicroShogi
{
	/**
	* @brief 棋士の基底クラス
	*/
	class PlayerBase
	{
	public:
		/**
		* @brief   コンストラクタ
		* @details 必要な情報を初期化する
		*/
		PlayerBase(AttackTurn id_);

		/**
		* @brief   デストラクタ
		*/
		~PlayerBase() {}

		/**
		* @brief   更新関数
		*/
		virtual bool Update();

		void SetBoard(ShogiBoard* board_) { m_ref_shogi_board = board_; }

	protected:
		/**
		* @brief   移動元を選択する関数
		* @return  bool 選択可能ならtrueを返す
		*/
		virtual bool SelectSource() = 0;

		/**
		* @brief   移動先を選択する関数
		* @return  bool 選択可能ならtrueを返す
		*/
		virtual bool SelectDest(bool* selected_ = nullptr) = 0;

	protected:
		//! ボードクラス参照用変数
		ShogiBoard* m_ref_shogi_board;

		//! 自身が先手か後手を保存する変数
		const AttackTurn m_attack_turn;

		//! 駒の移動元を保存する変数
		IVec2 m_souce_pos;

		//! 駒の移動先を保存する変数
		IVec2 m_dest_pos;

	private:

		//! 移動元を選択したかどうかを保存する変数
		bool SelectedMoveSource;
	};
}

#endif