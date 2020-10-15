#include "CharacterTronPlayer.h"
#include "../System/Input.h"

void Tron::CharacterTronPlayer::Init()
{
	m_PosX    = 1;
	m_PosY    = TRON_STAGE_HEIGHT / 2;
	m_IsDeath = false;

	m_RefStage->SetStage(m_PosX, m_PosY, m_Type);
}

void Tron::CharacterTronPlayer::Update()
{
	// 現在のステップを確認
	switch (m_CurrentStep)
	{
	case CharacterTronPlayer::PlayerStep::STEP_INIT:
		// 初期化ステップ
		
		this->Init();
		m_CurrentStep = PlayerStep::STEP_UPDATE;

		break;
	case CharacterTronPlayer::PlayerStep::STEP_UPDATE:
		// 更新ステップ
		
		// 勝敗が決まっていた場合下の処理は行わない
		if (g_IsGameEnd) return;

		// どの方向に移動するかを選ぶ
		this->DecideDirection();

		// 方向が決まったので移動する
		this->Move();

		// 移動後オブジェクトと当たっているかを調べる
		if (this->CheckHitObject() == true)
		{
			// 当たっていた場合負け
			m_IsDeath   = true;
			g_IsGameEnd = true;
			return;
		}

		// ステージにプレイヤーの情報を送る
		this->SendToStage();

		break;
	default:
		break;
	}
}

void Tron::CharacterTronPlayer::DecideDirection()
{
	while (true)
	{
		int key = Input::GetKey();
		
		// 上キーが押されたら
		if (key == KEY_UP) {
			m_Direction = Direction::DIRECTION_UP;
			break;
		}

		// 下キーが押されたら
		else if (key == KEY_UP) {
			m_Direction = Direction::DIRECTION_DOWN;
			break;
		}

		// 左キーが押されたら
		else if (key == KEY_LEFT) {
			m_Direction = Direction::DIRECTION_LEFT;
			break;
		}

		// 右キーに押されたら
		else if (key == KEY_RIGHT) {
			m_Direction = Direction::DIRECTION_RIGHT;
			break;
		}

	}
}

bool Tron::CharacterTronPlayer::CheckHitObject()
{
	if (m_RefStage->GetStageObject(m_PosX, m_PosY) != ObjectType::TYPE_EMPTY) {
		return true;
	}

	return false;
}
