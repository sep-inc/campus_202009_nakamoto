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
	bool SelectDest() override;

private:
	MoveTrun m_EnemyId;

	std::vector<IVec2> m_PiecePos;
	
	std::vector<IVec2> m_EnemyPiecePos;

	//! 
	__int8 m_Priority;
};

#endif