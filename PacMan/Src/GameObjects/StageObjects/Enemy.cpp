#include "Enemy.h"
#include "../../System/Drawer.h"
#include "../Stage.h"

/*
	コンストラクタ
*/
PacMan::Enemy::Enemy(PacMan::Stage* stage_) :
	StageObject{ stage_ }, m_Timer{ 0 }
{
}


/*
	初期化関数
*/
void PacMan::Enemy::Init()
{
	m_Timer = 0;
}


/*
	更新関数
*/
void PacMan::Enemy::Update()
{
	m_Timer++;

	if (m_Timer % ENEMY_SPEED == 0) {
		Move();
	}
}


/*
	描画関数
*/
void PacMan::Enemy::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "＠");
}


/*
	移動関数
*/
void PacMan::Enemy::Move()
{
	// 自身の位置から移動可能な場所を保存する変数
	Vec2 able_move[4];
	// 移動可能な数を保存する変数
	int able_move_num = 0;
	
	// 次の移動先座標を保存しておく変数
	Vec2 nextPos = m_Pos;

	// 右に移動できるかを調べる
	nextPos.m_X++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 左に移動できるかを調べる
	nextPos = m_Pos;
	nextPos.m_X--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 下に移動できるかを調べる
	nextPos = m_Pos;
	nextPos.m_Y++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 上に移動できるかを調べる
	nextPos = m_Pos;
	nextPos.m_Y--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 乱数を移動可能な数で割った余りを保存する
	int random_num = rand() % able_move_num;

	//　移動する
	m_RefStage->SetStage(m_Pos, able_move[random_num], this->GetObjectType());
	m_Pos = able_move[random_num];
}
