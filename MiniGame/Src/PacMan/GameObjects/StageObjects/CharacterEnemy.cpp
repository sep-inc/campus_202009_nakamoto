#include "CharacterEnemy.h"
#include "../../../System/Drawer.h"
#include <vector>

/*
	コンストラクタ
*/
PacMan::CharacterEnemy::CharacterEnemy(Stage* stage_) :
	StageCharacter{ stage_ }, m_AI{ &m_Pos, &m_Param, stage_ }, m_Timer{ 0 }
{
	m_Param.m_Personality = EnemyPersonalityList::PERSONALITY_A;
	m_Param.m_Speed = 15;

}


/*
	初期化関数
*/
void PacMan::CharacterEnemy::Init()
{
	m_Timer = 0;
	m_RefStage->SetRandomPlacementObject(this);

	
	
}


/*
	更新関数
*/
void PacMan::CharacterEnemy::Update()
{
	m_Timer++;

	if (m_Timer % m_Param.m_Speed == 0) {

		// AIで移動方向を考える
		m_AI.Update();

		// 移動する
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
	
	m_RefStage->SetStage(m_Pos, m_Pos + m_Param.m_Direction, this->GetObjectType());
	m_Pos = m_Pos + m_Param.m_Direction;
}