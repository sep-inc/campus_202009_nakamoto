#include "GameTowerOfHanoi.h"
#include "Global.h"
#include "../System/Input.h"
#include <stdio.h>


/*=============================================*/
/*    　　　　　ゲームの更新関数     　　　　　*/
/*=============================================*/
void GameTowerOfHanoi::Update()
{
	// 現在のステップを参照する
	switch (m_CurrentStep)
	{
	case GameTowerOfHanoi::TowerOfHanoiStep::STEP_INIT:
		// 初期化

		m_Disk.Init();

		// ステップを進める
		m_CurrentStep = TowerOfHanoiStep::STEP_UPDATE;

		break;

	case GameTowerOfHanoi::TowerOfHanoiStep::STEP_UPDATE:
		// 更新

		// ゲームがクリアされていたらステップを進める
		if (g_GameClear == true) {
			m_CurrentStep = TowerOfHanoiStep::STEP_RELEASE;
			break;
		}

		// ディスクの更新
		m_Disk.StepUpdate();

		break;

	case GameTowerOfHanoi::TowerOfHanoiStep::STEP_RELEASE:
	
		// 解放

		// 続けるかどうかを選択させる
		if (this->IsContinue() == true) {
			break;
		}

		m_IsEnd = true;
		break;

	
	default:
		break;
	}
}


/*=============================================*/
/*	　　　　　　　　描画関数     　　　　　　　*/
/*=============================================*/
void GameTowerOfHanoi::Draw()
{
	m_Disk.Draw();
}

bool GameTowerOfHanoi::IsContinue()
{
	printf("クリア!!\n");
	printf("もう一度遊びますか?\n");
	printf("遊ぶ\t\treturn\n");
	printf("遊ばない\tesc\n");
	
	int key = Input::GetKey();
	// エンターキーが押されたら
	if (key == KEY_ENTER) {
		// クリアフラグをfalseにする
		g_GameClear = false;
		// ステップを始めに戻す
		m_CurrentStep = TowerOfHanoiStep::STEP_INIT;
		
		return true;
	}

	return false;
}
