﻿#include "Enemy.h"
#include <stdlib.h>

void Tron::CharacterEnemy::Init()
{
	m_PosX    = STAGE_WIDTH - 2;
	m_PosY    = STAGE_HEIGHT / 2;
	m_IsDeath = false;

	m_RefStage->SetStage(m_PosX, m_PosY, m_Type);
}

void Tron::CharacterEnemy::Update()
{
	// 現在のステップを確認する
	switch (m_CurrentStep)
	{
	case CharacterEnemy::EnemyStep::STEP_INIT:
		// 初期化ステップ
		
		this->Init();
		m_CurrentStep = EnemyStep::STEP_UPDATE;

		break;
	case CharacterEnemy::EnemyStep::STEP_UPDATE:
		// 更新ステップ

		// 勝敗が決まっていた場合下の処理は行わない
		if (g_IsGameEnd) return;

		// どの方向に移動できるかを調べる
		this->SerchDirecttion();

		// もし移動できない場合敗北
		if (m_MovableDirectionNum == 0)
		{
			m_IsDeath   = true;
			g_IsGameEnd = true;
			return;
		}

		// 移動できる場合、どの方向に移動するかをランダムで選ぶ
		DecideDirection();

		// 選ばれた方向に移動する
		this->Move();

		// 移動後ステージにエネミーの情報を送る
		this->SendToStage();

		break;
	default:
		break;
	}
}

void Tron::CharacterEnemy::SerchDirecttion()
{
	m_MovableDirectionNum = 0;

	// 現在の座標から4方向のオブジェクトを調べて
	// 空だった場合配列に追加する

	// 右を調べる
	if (m_RefStage->GetStageObject(m_PosX + 1, m_PosY) == ObjectType::TYPE_EMPTY) {
		m_MovableDirection[m_MovableDirectionNum] = Direction::DIRECTION_RIGHT;
		m_MovableDirectionNum++;
	}
	// 左を調べる
	if (m_RefStage->GetStageObject(m_PosX - 1, m_PosY) == ObjectType::TYPE_EMPTY) {
		m_MovableDirection[m_MovableDirectionNum] = Direction::DIRECTION_LEFT;
		m_MovableDirectionNum++;
	}
	// 上を調べる
	if (m_RefStage->GetStageObject(m_PosX, m_PosY - 1) == ObjectType::TYPE_EMPTY) {
		m_MovableDirection[m_MovableDirectionNum] = Direction::DIRECTION_UP;
		m_MovableDirectionNum++;
	}
	// 下を調べる
	if (m_RefStage->GetStageObject(m_PosX, m_PosY + 1) == ObjectType::TYPE_EMPTY) {
		m_MovableDirection[m_MovableDirectionNum] = Direction::DIRECTION_DOWN;
		m_MovableDirectionNum++;
	}
}

void Tron::CharacterEnemy::DecideDirection()
{
	m_Direction = m_MovableDirection[rand() % m_MovableDirectionNum];
}
