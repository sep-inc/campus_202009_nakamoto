#include "GameTron.h"
#include "System.h"
#include <stdio.h>

void GameTron::Update()
{
	// 現在のステップを確認
	switch (m_CurrentStep)
	{
	case GameTron::GameTronStep::STEP_INIT:
		// 初期化ステップ
		
		m_Stage.Init();

#ifdef PLAYER_ON
		m_Player.Init();
#endif

#ifdef ENEMY_ON
		m_Enemy.Init();
#endif

		g_IsGameEnd = false;

		m_CurrentStep = GameTronStep::STEP_UPDATE;

		break;
	case GameTron::GameTronStep::STEP_UPDATE:
		// 更新ステップ

		// プレイヤーの更新
#ifdef PLAYER_ON
		m_Player.Update();
#endif

		// エネミーの更新
#ifdef ENEMY_ON
		m_Enemy.Update();
#endif

		// もし勝敗が決まっていたら次のステップへ
		if (g_IsGameEnd) m_CurrentStep = GameTronStep::STEP_RELEASE;


		break;
	case GameTron::GameTronStep::STEP_RELEASE:
		// 解放ステップ

		// 結果を出力する
		PrintResult();

		// 続けるかどうかを選ばせる
		if (IsContinue() == true) {
			// 続けるならステップを1に
			m_CurrentStep = GameTronStep::STEP_INIT;
			return;
		}

		// 終了なら終了フラグをtrueにする
		g_Quit = true;

		break;
	default:
		break;
	}
}

void GameTron::Draw()
{
	m_Stage.Draw();
}

void GameTron::PrintResult()
{
	// プレイヤーが死んでいたら敵の勝ち
	if (m_Player.IsDeath() == true) {
		printf("敵の勝ち！");
	}
	// エネミーが死んでいたらプレイヤーの勝ち
	else
	{
		printf("あなたの勝ち！");
	}

}

bool GameTron::IsContinue()
{
	printf("ゲームを続けますか？\n");
	printf("続ける -> ENTER\n");
	printf("やめる -> ESC\n");

	while (true)
	{
		int key = g_Input.GetKey();

		// もしエンターキーが押されたら
		if (key == 13)return true;
		// もしエスケープキーが押されたら
		else if (key == 27)break;
	}

	return false;
}
