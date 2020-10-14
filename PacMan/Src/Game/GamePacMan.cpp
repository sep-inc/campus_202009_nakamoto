#include "GamePacMan.h"
#include "../GameObjects/StageObjects/Player.h"
#include "../GameObjects/StageObjects/Enemy.h"
#include "../GameObjects/StageObjects/Item.h"
#include "../System/Input.h"
#include <string>
#include <iostream>
#include <Windows.h>

using namespace PacMan;

/*
	コンストラクタ
*/
PacMan::GamePacMan::GamePacMan() :
	m_Stage{ nullptr }, m_Enemy{ nullptr }, m_CurrentStep{ GamePacManStep::STEP_INIT }, m_GameClear{ false }
{
	m_Stage = new Stage();

#ifdef PLAYER_ON
	m_Player = new Player(m_Stage);
#endif

#ifdef ENEMY_ON
	for (int i = 0; i < ENEMY_NUM; ++i) {
		m_Enemy[i] = new Enemy(m_Stage);
	}
#endif
}


/*
	デストラクタ
*/
PacMan::GamePacMan::~GamePacMan()
{
	SAFE_DELETE(m_Stage);
	SAFE_DELETE(m_Player);
	for (int i = 0; i < ENEMY_NUM; ++i) {
		SAFE_DELETE(m_Enemy[i]);
	}
}


/*
	更新関数
*/
void PacMan::GamePacMan::Update()
{
	// 現在のステップを参照
	switch (m_CurrentStep)
	{
	case GamePacMan::GamePacManStep::STEP_INIT:

		// ステージの初期化
		if (m_Stage) m_Stage->Init();
		// プレイヤーの初期化
		if (m_Player) m_Player->Init();
		// エネミーの初期化
		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (m_Enemy[i]) {
				m_Stage->SetRandomPlacementObject(m_Enemy[i]);
			}
		}

		// 次のステップへ進める
		m_CurrentStep = GamePacManStep::STEP_UPDATE;
		break;
	case GamePacMan::GamePacManStep::STEP_UPDATE:
		// 各オブジェクトの更新をおこなう
		if (m_Player) m_Player->Update();

		for (int i = 0; i < ENEMY_NUM; ++i) {
			if (m_Enemy[i]) m_Enemy[i]->Update();
		}

		// もしステージにアイテムがなくなったらステップを進める
		if (m_Stage->EmptyItem() == true) {
			
			m_CurrentStep = GamePacManStep::STEP_RELEASE;
			m_GameClear = true;
		}
		// もし敵とプレイヤーが当たっていたらステップを進める
		else if (m_Stage->HitPlayerAndEnemy() == true) {

			m_CurrentStep = GamePacManStep::STEP_RELEASE;
		}

		break;
	case GamePacMan::GamePacManStep::STEP_RELEASE:
		// 結果を出力
		PrintResult();
		// 続けるかどうかを選択
		if (SelectContinue() == true) {
			// 続けるなら初期化ステップへ
			m_CurrentStep = GamePacManStep::STEP_INIT;
			system("cls");
		}
		else {
			// 続けないならゲーム終了
			exit(0);
		}
		break;
	default:
		break;
	}
}


/*
	描画関数
*/
void PacMan::GamePacMan::Draw()
{
	std::cout << "十字キーで移動" << std::endl;

	// 各オブジェクトの描画
	m_Stage->Draw();

	if (m_Player) m_Player->Draw();

	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (m_Enemy[i]) m_Enemy[i]->Draw();
	}
}


/*
	結果を表示する関数
*/
void PacMan::GamePacMan::PrintResult()
{
	std::string str_result;

	str_result = m_GameClear ? "ゲームクリア!!" : "ゲームオーバー";

	std::cout << str_result << std::endl;
	
}


/*
	続けるかどうかを選択して返す関数
*/
bool PacMan::GamePacMan::SelectContinue()
{
	std::cout << "もう一度続けますか？" << std::endl;
	std::cout << "続ける	Enterキー" << std::endl;
	std::cout << "やめる	Escキー　" << std::endl;

	while (true)
	{
		int key = Input::GetKey();

		if (key == -1) continue;

		if (key == KEY_ENTER)return true;
		else if (key == KEY_ESC)return false;
	}
}
