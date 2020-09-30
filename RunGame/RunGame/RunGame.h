#ifndef RUNGAME_H_
#define RUNGAME_H_
#include "Player.h"
#include "Stage.h"

/**
* @brief Runゲームクラス
*/
class RunGame
{
	/**
	* @enum Enum
	* Runゲームのステップ
	*/
	enum class RunGameStep : unsigned char
	{
		STEP_INT,
		STEP_UPDATE,
		STEP_RELEASE,
	};

public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	RunGame() :
		m_CurrentStep{ RunGameStep::STEP_INT }
	{
		m_Stage  = new Stage();
		m_Player = new Player(m_Stage);
	}

	/**
	* @brief   デストラクタ
	*/
	~RunGame()
	{
		delete m_Player;
		delete m_Stage;
	}

	/**
	* @brief 　更新関数
	* @details 1フレームに一度だけ呼ぶ
	*/
	void Update();

	/**
	* @brief   描画関数
	* @details 各オブジェクトの描画を行う
	*/
	void Draw();

private:
	/**
	* @brief 　結果を出力する関数
	* @details ゲーム終了時に結果を参照して出力する
	*/
	void PrintResult();

	/**
	* @brief   ゲーム終了時に続けるかどうかを選択する関数
	* @return  bool 続けるならtrueを返す
	*/
	bool SelectContinue();

private:
	//! プレイヤー変数
	Player* m_Player;

	//! ステージ変数
	Stage* m_Stage;
	
	//! 現在のステップを保存する変数
	RunGameStep m_CurrentStep;
};

#endif