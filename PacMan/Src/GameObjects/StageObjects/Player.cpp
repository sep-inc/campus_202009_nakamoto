#include "Player.h"
#include "../../System/Drawer.h"
#include "../../System/Input.h"
#include "../../Definition.h"
#include "../Stage.h"


Player::Player(Stage* stage_) :
	StageObject{ stage_ }
{
}

void Player::Init()
{
	this->SetPos(Vec2(PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y));
}

void Player::Update()
{
	int key = Input::GetKey();

	if (key == -1) return;

	Vec2 next_pos = m_Pos;
	if (key == KEY_UP)         next_pos.m_Y--;
	else if (key == KEY_DOWN)  next_pos.m_Y++;
	else if (key == KEY_LEFT)  next_pos.m_X--;
	else if (key == KEY_RIGHT) next_pos.m_X++;
	else return;

	if (m_RefStage->GetStageObject(next_pos) != ObjectType::TYPE_WALL) {
		m_Pos = next_pos;
	}
	
}

void Player::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "ÅZ");
}
