#include "Enemy.h"
#include "GrobalObject.h"
#include <stdio.h>
#include <stdlib.h>

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

		// もしプレイヤーの番じゃなければ
		if (g_WhosTurn != ObjectType::TYPE_PlAYER) return;

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

// どのマスに置くかを選ぶ関数
void Enemy::Select()
{
	while (true)
	{
		// 横軸を選ぶ
		m_SelectX = SelectHorizontal();
		if (m_SelectX == -1) continue;

		// 縦軸を選ぶ
		m_SelectY = SelectVertical();
		if (m_SelectY == -1) continue;

		// 置けるかを調べる
		if (g_Grid.Select(m_SelectX, m_SelectY, m_ObjectType) == true) {
			m_Selected = true;
			break;
		}
	}
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
