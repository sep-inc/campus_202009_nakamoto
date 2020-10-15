#ifndef GAME_PACMAN_H_
#define GAME_PACMAN_H_

#include "../GameObjects/Stage.h"
#include "../GameObjects/StageObjects/EnemyArray.h"
#include "../GameObjects/StageObjects/CharacterPlayer.h"
#include "../PacManDefinition.h"
#include "../../Game.h"

namespace PacMan
{
	/*
	パックマンのゲーム管理クラス
*/
	class GamePacMan : public Game
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
		void Update() override;

		/*
			描画関数
		*/
		void Draw() override;

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
		CharacterPlayer* m_Player;
		// エネミー
		EnemyArray* m_EnemyArray;
		// 現在のステップを保存する変数
		GamePacManStep m_CurrentStep;
		// ゲームをクリアしたかどうかを保存する変数
		bool m_GameClear;
	};
}

#endif