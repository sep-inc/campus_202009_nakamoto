#ifndef SHOGIPLAYERNPC_H_
#define SHOGIPLAYERNPC_H_

#include "../ShogiPlayerBase.h"
#include <vector>

/**
* @brief 【棋士】NPCクラス
*/
class ShogiPlayerNPC : public ShogiPlayerBase
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiPlayerNPC(ShogiBoard* board_, MoveTrun id_);

	/**
	* @brief   デストラクタ
	*/
	~ShogiPlayerNPC(){}

private:
	/**
	* @brief   移動元を選択する関数
	* @return  bool 選択可能ならtrueを返す
	*/
	bool SelectSource() override;

	/**
	* @brief   移動先を選択する関数
	* @return  bool 選択可能ならtrueを返す
	*/
	bool SelectDest(bool* selected_ = nullptr) override;

private:
	//! 相手が先手か後手を保存する変数
	MoveTrun m_EnemyId;

	//! 自身の駒の座標を保存する変数
	std::vector<IVec2> m_PiecePos;
	
	//! 相手の駒の座標を保存する変数
	std::vector<IVec2> m_EnemyPiecePos;

	//! どの行動をするかの優先度
	__int8 m_Priority;
};

#endif