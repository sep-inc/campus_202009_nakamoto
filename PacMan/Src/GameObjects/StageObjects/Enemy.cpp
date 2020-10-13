#include "Enemy.h"
#include "../../System/Drawer.h"
#include "../Stage.h"

Enemy::Enemy(Stage* stage_) :
	StageObject{ stage_ }
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	m_Timer++;

	if (m_Timer % 30 == 0) {
		Move();
	}
}

void Enemy::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "—");
}

void Enemy::Move()
{
	Vec2 able_move[4];
	int able_move_num = 0;
	
	Vec2 nextPos = m_Pos;
	nextPos.m_X++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	nextPos = m_Pos;
	nextPos.m_X--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	nextPos = m_Pos;
	nextPos.m_Y++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	nextPos = m_Pos;
	nextPos.m_Y--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}


	int random_num = rand() % able_move_num;

	m_Pos = able_move[random_num];
}
