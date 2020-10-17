#include "CharacterEnemy.h"
#include "../../../System/Drawer.h"
#include <vector>

/*
	コンストラクタ
*/
PacMan::CharacterEnemy::CharacterEnemy(Stage* stage_) :
	StageCharacter{ stage_ }, m_Timer{ 0 }
{
}


/*
	初期化関数
*/
void PacMan::CharacterEnemy::Init()
{
	m_Timer = 0;
	m_RefStage->SetRandomPlacementObject(this);
	
	// 自身の位置から移動可能な場所を保存する変数
	IVec2 able_move[4];
	// 移動可能な数を保存する変数
	int able_move_num = 0;
	//　移動できる方向を調べる
	AbleMoveAround(m_Pos, able_move, &able_move_num);

	int random_num = rand() % able_move_num;

	// 最初の移動方向を決定
	m_Direction = able_move[random_num] - m_Pos;
}


/*
	更新関数
*/
void PacMan::CharacterEnemy::Update()
{
	m_Timer++;

	if (m_Timer % ENEMY_SPEED == 0) {
		Move();
	}
}


/*
	描画関数
*/
void PacMan::CharacterEnemy::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "＠");
}


/*
	移動関数
*/
void PacMan::CharacterEnemy::Move()
{
	// 自身の位置から移動可能な場所を保存する変数
	IVec2 able_move[4];
	// 移動可能な数を保存する変数
	int able_move_num = 0;

	AbleMoveAround(m_Pos, able_move, &able_move_num);

	// 現座の進んでいるベクトルの逆のベクトルを算出する
	IVec2 reverce_vec;
	reverce_vec.m_X = -m_Direction.m_X;
	reverce_vec.m_Y = -m_Direction.m_Y;
	
	std::vector<IVec2> new_able_move;
	// 反対方向にはいきたくないので、候補から削除する
	for (int i = 0; i < able_move_num; ++i)
	{
		IVec2 vec = able_move[i] - m_Pos;
		if (vec == reverce_vec)continue;
		new_able_move.push_back(able_move[i]);
	}

	// 乱数を移動可能な数で割った余りを保存する
	int random_num = rand() % new_able_move.size();

	//　移動する
	m_RefStage->SetStage(m_Pos, new_able_move[random_num], this->GetObjectType());
	m_Direction = new_able_move[random_num] - m_Pos;
	m_Pos = new_able_move[random_num];
}

void PacMan::CharacterEnemy::AbleMoveAround(IVec2 pos_, IVec2* outVecArray_, int* ableMoveNum_)
{
	// 自身の位置から移動可能な場所を保存する変数
	IVec2 able_move[4];
	// 移動可能な数を保存する変数
	int able_move_num = 0;

	// 次の移動先座標を保存しておく変数
	IVec2  nextPos = pos_;

	// 右に移動できるかを調べる
	nextPos.m_X++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 左に移動できるかを調べる
	nextPos = pos_;
	nextPos.m_X--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 下に移動できるかを調べる
	nextPos = pos_;
	nextPos.m_Y++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// 上に移動できるかを調べる
	nextPos = pos_;
	nextPos.m_Y--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	for (int i = 0; i < able_move_num; ++i)
	{
		outVecArray_[i].m_X = able_move[i].m_X;
		outVecArray_[i].m_Y = able_move[i].m_Y;
	}
	*ableMoveNum_ = able_move_num;
}
