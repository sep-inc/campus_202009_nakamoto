﻿#ifndef PLAYER_H_
#define PLAYER_H_

#include "ObjectBase.h"

/*
	プレイヤークラス
*/
class Player : public ObjectBase
{
	// プレイヤーのステップ項目
	enum class PlayerStep : unsigned char
	{
		STEP_INIT,		// 初期化ステップ
		STEP_UPDATE,	// 更新ステップ
		STEP_RELEASE,	// 解放ステップ
	};

public:
	// コンストラクタ
	Player() :
		ObjectBase(ObjectType::TYPE_PlAYER),
		m_CurrentStep(PlayerStep::STEP_INIT)
	{}

	// デストラクタ
	~Player(){}

	// ステップの更新関数
	void StepUpdate() override;

private:
	// どのマスに置くかを選ぶ関数
	void Select() override;

	// どのマスの横軸に置くかを決める関数
	__int8 SelectHorizontal() override;

	// どのマスの縦軸に置くかを決める関数
	__int8 SelectVertical() override;



	// 現在のステップを保存する変数
	PlayerStep m_CurrentStep;

};

#endif