#include "GamePacMan.h"
#include "../../System/Input.h"
#include <string>
#include <iostream>
#include <Windows.h>

/*
	コンストラクタ
*/
PacMan::GamePacMan::GamePacMan() :
	m_Stage{ nullptr }, m_EnemyArray{ nullptr }, m_CurrentStep{ GamePacManStep::STEP_INIT }, m_GameClear{ false }
{
	m_Stage = new Stage();

#ifdef PLAYER_ON
	m_Player = new CharacterPlayer(m_Stage);
#endif

#ifdef ENEMY_ON
	m_EnemyArray = new EnemyArray(m_Stage);
#endif
}


/*
	デストラクタ
*/
PacMan::GamePacMan::~GamePacMan()
{
	SAFE_DELETE(m_Stage);
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_EnemyArray);
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
		if (m_EnemyArray)m_EnemyArray->Init();

		// 次のステップへ進める
		m_CurrentStep = GamePacManStep::STEP_UPDATE;
		break;
	case GamePacMan::GamePacManStep::STEP_UPDATE:
		// 各オブジェクトの更新をおこなう
		if (m_Player) m_Player->Update();

		if (m_EnemyArray)m_EnemyArray->Update();

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
			m_IsEnd = true;
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

	if (m_EnemyArray)m_EnemyArray->Draw();

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
