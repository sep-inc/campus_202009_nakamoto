#ifndef PLYAER_H_
#define PLYAER_H_

#include "Vec2.h"
#include "Stage.h"
#include "Definition.h"

/**
* @brief プレイヤークラス
*/
class Player
{
	/**
	* @enum Enum
	* プレイヤーのステップ
	*/
	enum class PlayerStep : unsigned char
	{
		STEP_INIT,
		STEP_UPDATE,
	};

public:
	/**
	* @brief   コンストラクタ
	* @details 必要な情報を初期化する
	*/
	Player(Stage* stage_) :
		m_TerminalVelocity{ 0.9f } ,
		m_Pos{ 0.f,0.f },
		m_OldPos{ 0.f,0.f },
		m_RefStege{ stage_ },
		m_Width{PLAYER_WIDTH},
		m_Height{PLAYER_HEIGHT},
		m_JumpVelocity{ 0.f },
		m_OnGround{ true },
		m_Horizon{ PLAYER_SPEED },
		m_Vertical{ 0.f },
		m_CurrentStep{ PlayerStep::STEP_INIT }
	{}

	/**
	* @brief   デストラクタ
	*/
	~Player(){}

	/**
	* @brief 　更新関数
	* @details 1フレームに一度だけ呼ぶ
	*/
	void Update();

	/**
	* @brief   初期化関数
	* @details ゲームの初期化時に1度だけ呼ぶ
	*/
	void Init();

	/**
	* @brief   描画関数関数
	* @details ステージの描画の前に呼ぶ
	*/
	void Draw();
	
private:
	/**
	* @brief   ジャンプ関数
	* @details ジャンプのトリガーを管理している
	*/
	void Jump();

	/**
	* @brief   落下関数
	* @details 地面に足がついていない時に
	*/
	void Fall();

	/**
	* @brief   ブロックと当たっているかを調べる関数
	* @details X軸とY軸を分けて、X軸で当たっていたら死亡、Y軸で当たっていたら位置を補正する
	*/
	void ChecHitBlock();

private:
	//! 終端速度を保存する変数
	const float m_TerminalVelocity;

	//! 現在のポジションを保存する変数
	Vec2 m_Pos;

	//! 1フレーム前の座標を保存する変数
	Vec2 m_OldPos;

	//! 横幅
	__int8 m_Width;

	//! 縦幅
	__int8 m_Height;

	//! ジャンプ速度
	float m_JumpVelocity;

	//! X軸の移動距離を保存する変数
	float m_Horizon;

	//! Y軸の移動距離を保存する変数
	float m_Vertical;

	//! 地面に足がついているかを保存する変数
	bool m_OnGround;

	//! ステージの参照用変数
	Stage* m_RefStege;

	//! 現在のステップを保存する変数
	PlayerStep m_CurrentStep;
};

#endif