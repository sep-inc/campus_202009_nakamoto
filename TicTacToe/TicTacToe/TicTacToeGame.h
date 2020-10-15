#ifndef TICTACTOEGAME_H_
#define TICTACTOEGAME_H_

#include "Player.h"
#include "Enemy.h"
#include "Grid.h"


// ゲーム更新管理クラス
class TicTacToeGame
{
	enum class TicTacToeGameStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
		STEP_RELEASE,
	};

public:
	// コンストラクタ
	TicTacToeGame():
		m_CurrentStep(TicTacToeGameStep::STEP_INIT),
		m_TurnCount(0)
	{}

	// デストラクタ
	~TicTacToeGame(){}

	// 各オブジェクトのステップ関数を呼び出す関数
	void Update();

	// バッファに書き込む関数
	void Draw();

private:
	// 勝敗を表示し、続けるかどうかを決める関数
	void Announce();


private:
	// プレイヤー
	TicTacToe::Player m_Player;

	// エネミー
	TicTacToe::Enemy m_Enemy;

	// 現在のステップ
	TicTacToeGameStep m_CurrentStep;

	// ターンをカウントする変数
	int m_TurnCount;

};

#endif