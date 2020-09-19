#include "Enemy.h"
#include "GrobalObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ステップの更新関数
void Enemy::StepUpdate()
{
	// 現在のステップを確認
	switch (m_CurrentStep)
	{
	case EnemyStep::STEP_INIT:

		// ステップを進める
		m_CurrentStep = EnemyStep::STEP_UPDATE;
		// 初期化
		break;

	case EnemyStep::STEP_UPDATE:

		// ゲームが終了していたら
		if (g_IsGameOver) {
			// ステップを進める
			m_CurrentStep = EnemyStep::STEP_RELEASE;
			return;
		}

		// もしエネミーの番じゃなければ
		if (g_WhosTurn != ObjectType::TYPE_ENEMY) return;

		// もし前のフレームで選ばれたいた場合
		if (m_Selected == true) {
			m_Selected = false;
			g_WhosTurn = ObjectType::TYPE_PlAYER;
			return;
		}

		// どこに置くのかを選ぶ
		this->Select();

		// 更新
		break;

	case EnemyStep::STEP_RELEASE:
		// 解放
		break;

	default:
		break;
	}

}

// 初期化関数
void Enemy::Init()
{
	m_CurrentStep = EnemyStep::STEP_INIT;
	m_Selected = false;
}

// どのマスの横軸に置くかを決める関数
__int8 Enemy::SelectHorizontal()
{	
	return rand() % 3;
}

// どのマスの縦軸に置くかを決める関数
__int8 Enemy::SelectVertical()
{
	return rand() % 3;
}
