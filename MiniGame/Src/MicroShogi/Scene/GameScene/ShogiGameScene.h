#ifndef SHOGI_GAME_SCENE_H_
#define SHOGI_GAME_SCENE_H_

#include "../ShogiSceneBase.h"
#include "../../Object/Definition.h"
#include "../../Object/ShogiPlayer/PlayerBase.h"
#include "../../Object/Bord/ShogiBoard.h"

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
	ShogiGameScene(const ShogiPlayerType* first_, const ShogiPlayerType* second_, AttackTurn* whoseWin_);

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

	inline const ShogiSceneList GetScene() const override { return ShogiSceneList::SCENE_GAME; }

private:
	//! 棋士クラス[0->先手] [1->後手]
	MicroShogi::PlayerBase* m_player[2];

	//! ボード
	ShogiBoard* m_board;

	//! どちらの番なのかを保存する変数
	AttackTurn CurrentTurn;

	//! 誰が勝利したかを保存する変数
	AttackTurn* m_WhoseWin;

};

#endif