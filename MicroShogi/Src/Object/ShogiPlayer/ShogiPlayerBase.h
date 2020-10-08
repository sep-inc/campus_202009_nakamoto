#ifndef ShogiPlayerBase_H_
#define ShogiPlayerBase_H_

#include "../Definition.h"
#include "../Bord/ShogiBoard.h"

/**
* @brief 棋士の基底クラス
*/
class ShogiPlayerBase
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiPlayerBase(ShogiBoard* board_, MoveTrun id_);

	/**
	* @brief   デストラクタ
	*/
	~ShogiPlayerBase(){}

	/**
	* @brief   更新関数
	*/
	bool Update();

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
	ShogiBoard* m_RefBoard;

	//! 自身が先手か後手を保存する変数
	const MoveTrun m_Id;

	//! 駒の移動元を保存する変数
	IVec2 m_MoveSource;

private:

	//! 移動元を選択したかどうかを保存する変数
	bool SelectedMoveSource;
};

#endif