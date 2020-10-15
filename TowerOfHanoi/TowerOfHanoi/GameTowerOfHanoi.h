#ifndef GAMETOWEROFHANOI_H_
#define GAMETOWEROFHANOI_H_

#include "Disk.h"

/**
* @brief    ゲームクラス
*/
class GameTowerOfHanoi
{
	/**
	* @enum Enum
	* ゲームのステップ
	*/
	enum class TowerOfHanoiStep : unsigned char
	{
		STEP_INIT,		// 初期化
		STEP_UPDATE,	// 更新
		STEP_RELEASE,	// 解放
	};

public:
	/**
	* @brief コストラクタ
	* @details 必要な変数を初期化する
	*/
	GameTowerOfHanoi():
		m_CurrentStep(TowerOfHanoiStep::STEP_INIT)
	{}

	/**
	* @brief デストラクタ
	*/
	~GameTowerOfHanoi(){}

	/**
	* @brief ゲームの更新を行う関数
	*/
	void Run();

	/**
	* @brief 　描画関数
	* @details ゲームオブジェクトの描画をおこなう関数
	*/
	void Draw();

	/**
	* @brief 続けるかどうかを決める関数
	* @return bool 続けるならtrueが返る
	* @details キー
	*/
	bool IsContinue();
	
private:
	//! ディスク
	Hanoi::Disk m_Disk;
	
	//! 現在のステップを保存する変数
	TowerOfHanoiStep m_CurrentStep;
};


#endif