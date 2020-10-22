#include "CharacterEnemy.h"
#include "../../../System/Drawer.h"
#include <vector>

/*
	�R���X�g���N�^
*/
PacMan::CharacterEnemy::CharacterEnemy(Stage* stage_, int speed_, EnemyPersonalityList personality_) :
	StageCharacter{ stage_ }, m_AI{ &m_Pos, &m_Param, stage_ }, m_Timer{ 0 }
{
	m_Param.m_Personality = personality_;
	m_Param.m_Speed = speed_;

}


/*
	�������֐�
*/
void PacMan::CharacterEnemy::Init()
{
	m_Timer = 0;
	m_Param.m_TraceList.clear();
	m_Param.m_Direction.m_X = 0;
	m_Param.m_Direction.m_Y = 0;
	m_RefStage->SetRandomPlacementObject(this);
}


/*
	�X�V�֐�
*/
void PacMan::CharacterEnemy::Update()
{
	m_Timer++;

	if (m_Timer % m_Param.m_Speed == 0) {

		// AI�ňړ��������l����
		m_AI.Update();

		// �ړ�����
		Move();
	}
}


/*
	�`��֐�
*/
void PacMan::CharacterEnemy::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "��");
}


/*
	�ړ��֐�
*/
void PacMan::CharacterEnemy::Move()
{
	if (m_RefStage->GetStageObject(m_Pos + m_Param.m_Direction) == ObjectType::TYPE_WALL
		|| m_RefStage->GetStageObject(m_Pos + m_Param.m_Direction) == ObjectType::TYPE_ENEMY) {
		return;
	}
	m_RefStage->SetStage(m_Pos, m_Pos + m_Param.m_Direction, this->GetObjectType());
	m_Pos = m_Pos + m_Param.m_Direction;
}