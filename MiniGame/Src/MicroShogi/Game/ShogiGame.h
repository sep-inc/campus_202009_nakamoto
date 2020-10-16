#ifndef SHOGI_GAME_H_
#define SHOGI_GAME_H_

#include "../Object/Definition.h"
#include "../Scene/ShogiSceneBase.h"
#include "../../Game.h"

/**
* @brief 将棋ゲームを管理するクラス
*/
class ShogiGame : public Game
{
public:
	/**
* @brief   コンストラクタ
* @details 必要な情報を初期化する
*/
	ShogiGame();

	/**
	* @brief   コンストラクタ
	* @details 現在のシーンを解放する
	*/
	~ShogiGame();

	/**
	* @brief     シーンの切り替え関数
	* @param[in] scene_  切り替えるシーン
	*/
	void ChangeScene(ShogiSceneList scene_);

	/**
	* @brief   更新関数
	* @details 現在のシーンの描画関数を呼び出す
	*/
	void Update() override;

	/**
	* @brief   描画関数
	* @details 現在のシーンの描画関数を呼び出す
	*/
	void Draw() override;


private:
	//! 現在のシーンを保存する変数
	ShogiSceneBase* m_CurrentScene;

	//! 先手のプレイヤーを保存する変数
	ShogiPlayerType m_FirstMovePlayer;

	//! 後手のプレイヤーを保存する変数
	ShogiPlayerType m_SecondMovePlayer;

	//! 誰が勝利したかを保存する変数
	AttackTurn        m_WhoseWin;

	bool m_Continue;

};

#endif