#ifndef ENEMY_H_
#define ENEMY_H_

#include "CharacterBase.h"

/**
* @brief エネミークラス
*/
class Enemy : public CharacterBase
{
	/**
	* @enum Enum
	* エネミーのステップ
	*/
	enum class EnemyStep
	{
		STEP_INIT,
		STEP_UPDATE,
	};
public:
	/**
	* @brief コンストラクタ
	* @param[in] stage_　ステージクラスのアドレス
	*/
	Enemy(Stage* stage_) :
		CharacterBase      { stage_, ObjectType::TYPE_ENEMY },
		m_MovableDirectionNum{ 0 },
		m_MovableDirection   { Direction ::DIRECTION_DOWN},
		m_CurrentStep      { EnemyStep::STEP_INIT }
	{}

	/**
	* @brief デストラクタ
	*/
	~Enemy(){}

	/**
	* @brief   初期化関数
	* @details ゲームの初期化時に1度だけ呼ぶ
	*/
	void Init() override;

	/**
	* @brief 　更新関数
	* @details 1フレームに一度だけ呼ぶ
	*/
	void Update() override;

private:
	/**
	* @brief   どの方向に移動できるかを調べる関数
	* @details m_MovableDirectionに移動できる方向をindex[0]から保存していく
	* @details 移動可能数をm_MovableDirectionNumに保存する
	*/
	void SerchDirecttion();

	/**
	* @brief 　移動方向を決める関数関数
	* @details 移動可能な向きが保存されている配列を参照し、ランダムで移動方向を選ぶ
	*/
	void DecideDirection() override;

private:
	//! 移動可能な向きの数を保存する変数
	int m_MovableDirectionNum;

	//! 移動可能な向きを保存する変数
	Direction m_MovableDirection[4];

	//! 現在のステップを保存する変数
	EnemyStep m_CurrentStep;

};

#endif