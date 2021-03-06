﻿#ifndef GAMETRON_H_
#define GAMETRON_H_

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

// 単体テスト用
#define PLAYER_ON
#define ENEMY_ON


/**
* @brief   　ゲームクラス
*/
class GameTron
{
	/**
	* @enum Enum
	* ゲームのステップ
	*/
	enum class GameTronStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
		STEP_RELEASE,
	};

public:
	/**
	* @brief   コンストラクタ
	*/
	GameTron() :
		m_CurrentStep{ GameTronStep::STEP_INIT },
		m_Player     { &m_Stage },
		m_Enemy      { &m_Stage }
	{}

	/**
	* @brief   デストラクタ
	*/
	~GameTron(){}

	/**
	* @brief   更新関数
	* @details ステップ毎に応じた処理を行う
	*/
	void Update();

	/**
	* @brief   描画関数
	*/
	void Draw();

private:
	/**
	* @brief    結果を出力する関数
	* @details  どちらが死んでいるかを参照し結果を出力する
	*/
	void PrintResult();
	
	/**
	* @brief   ゲームを続けるかどうかを選択する関数
	* @return  bool 続けるならtrue 続けないならfalseを返す
	*/
	bool IsContinue();

private:
	//! プレイヤー変数
	Tron::CharacterPlayer m_Player;

	//! エネミー変数
	Tron::CharacterEnemy  m_Enemy;

	//! ステージ変数
	Tron::Stage           m_Stage;

	//! 現在のステップを保存する変数
	GameTronStep    m_CurrentStep;
};

#endif