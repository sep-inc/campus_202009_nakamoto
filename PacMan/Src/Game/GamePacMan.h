#ifndef GAME_PACMAN_H_
#define GAME_PACMAN_H_

#include "../GameObjects/Stage.h"
#include "../GameObjects/StageObjects/EnemyArray.h"
#include "../GameObjects/StageObjects/Player.h"
#include "../Definition.h"

namespace PacMan
{
	/*
	パックマンのゲーム管理クラス
*/
	class GamePacMan
	{
		// ステップ
		enum class GamePacManStep : unsigned char
		{
			STEP_INIT,		// 初期化ステップ
			STEP_UPDATE,	// 更新ステップ
			STEP_RELEASE,	// 解放ステップ
		};

	public:
		/*
			コンストラクタ
		*/
		GamePacMan();

		/*
			デストラクタ
		*/
		~GamePacMan();

		/*
			更新関数
		*/
		void Update();

		/*
			描画関数
		*/
		void Draw();

	private:
		/*
			結果を出力する関数
		*/
		void PrintResult();

		/*
			続けるかどうかを選択し、結果を真偽で返す関数
			真：続ける
			偽：やめる
		*/
		bool SelectContinue();

	private:
		// ステージ
		Stage* m_Stage;
		// プレイヤー
		Player* m_Player;
		// エネミー
		EnemyArray* m_EnemyArray;
		// 現在のステップを保存する変数
		GamePacManStep m_CurrentStep;
		// ゲームをクリアしたかどうかを保存する変数
		bool m_GameClear;
	};
}

#endif