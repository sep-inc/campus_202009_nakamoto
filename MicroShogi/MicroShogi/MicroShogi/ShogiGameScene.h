#ifndef SHOGI_GAME_SCENE_H_
#define SHOGI_GAME_SCENE_H_

#include "ShogiSceneBase.h"
#include "Definition.h"
#include "ShogiPlayerBase.h"
#include "ShogiBoard.h"

/**
* @brief 将棋のゲームシーンクラス
*/
class ShogiGameScene : public ShogiSceneBase
{
public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する、タイトルシーンで先手と後手を決めておく必要がある
	*/
	ShogiGameScene(const ShogiPlayerType* first_, const ShogiPlayerType* second_, MoveTrun* whoseWin_);

	/**
	* @brief   デストラクタ
	* @details ゲームシーンで確保したデータを解放する
	*/
	~ShogiGameScene();

	/**
	* @brief   更新関数
	* @details ゲームの更新
	*/
	void Update() override;

	/**
	* @brief   描画関数
	*/
	void Draw() override;

private:
	//! 棋士クラス[0->先手] [1->後手]
	ShogiPlayerBase* m_ShogiPlayer[2];

	//! ボード
	ShogiBoard* m_Board;

	//! どちらの番なのかを判定するためのカウント変数
	int m_TrunCount;

	//! 誰が勝利したかを保存する変数
	MoveTrun* m_WhoseWin;

};

#endif