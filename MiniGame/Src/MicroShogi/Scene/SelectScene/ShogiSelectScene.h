#ifndef SHOGI_SELECT_SCENE_H_
#define SHOGI_SELECT_SCENE_H_

#include "../ShogiSceneBase.h"
#include "../../Object/Definition.h"

/**
* @brief 将棋のセレクトシーン
*/
class ShogiSelectScene : public ShogiSceneBase
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	ShogiSelectScene(ShogiPlayerType* first_, ShogiPlayerType* second_);

	/**
	* @brief   デストラクタ
	*/
	~ShogiSelectScene(){}
	
	/**
	* @brief   描画関数
	* @details セレクトシーンの更新処理を行う
	*/
	void Update() override;

	/**
	* @brief   描画関数
	* @details セレクトシーンの描画処理を行う
	*/
	void Draw() override;

private:
	/**
	* @brief 　PCかNPCを選択する関数
	* @param[out] player_ 選択された棋士の情報が返る
	*/
	void SelectPlayer(ShogiPlayerType* player_);

	/**
	* @brief   先手後手の棋士情報選択後、情報を確定させるかどうかを選択させる関数
	* @return  bool 確定ならtureを返す
	*/
	bool IsConfirm();

private:
	//! 先手のプレイヤーを保存する変数
	ShogiPlayerType* m_FirstMovePlayer;

	//! 後手のプレイヤーを保存する変数
	ShogiPlayerType* m_SecondMovePlayer;

};

#endif