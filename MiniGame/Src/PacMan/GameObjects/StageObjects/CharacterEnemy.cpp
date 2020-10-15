#include "CharacterEnemy.h"
#include "../../../System/Drawer.h"

/*
	�R���X�g���N�^
*/
PacMan::CharacterEnemy::CharacterEnemy(Stage* stage_) :
	StageCharacter{ stage_ }, m_Timer{ 0 }
{
}


/*
	�������֐�
*/
void PacMan::CharacterEnemy::Init()
{
	m_Timer = 0;
	m_RefStage->SetRandomPlacementObject(this);
}


/*
	�X�V�֐�
*/
void PacMan::CharacterEnemy::Update()
{
	m_Timer++;

	if (m_Timer % ENEMY_SPEED == 0) {
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
	// ���g�̈ʒu����ړ��\�ȏꏊ��ۑ�����ϐ�
	IVec2 able_move[4];
	// �ړ��\�Ȑ���ۑ�����ϐ�
	int able_move_num = 0;
	
	// ���̈ړ�����W��ۑ����Ă����ϐ�
	IVec2  nextPos = m_Pos;

	// �E�Ɉړ��ł��邩�𒲂ׂ�
	nextPos.m_X++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ���Ɉړ��ł��邩�𒲂ׂ�
	nextPos = m_Pos;
	nextPos.m_X--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ���Ɉړ��ł��邩�𒲂ׂ�
	nextPos = m_Pos;
	nextPos.m_Y++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ��Ɉړ��ł��邩�𒲂ׂ�
	nextPos = m_Pos;
	nextPos.m_Y--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// �������ړ��\�Ȑ��Ŋ������]���ۑ�����
	int random_num = rand() % able_move_num;

	//�@�ړ�����
	m_RefStage->SetStage(m_Pos, able_move[random_num], this->GetObjectType());
	m_Pos = able_move[random_num];
}
