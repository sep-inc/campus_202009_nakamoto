#include "CharacterEnemy.h"
#include "../../../System/Drawer.h"
#include <vector>

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
	
	// ���g�̈ʒu����ړ��\�ȏꏊ��ۑ�����ϐ�
	IVec2 able_move[4];
	// �ړ��\�Ȑ���ۑ�����ϐ�
	int able_move_num = 0;
	//�@�ړ��ł�������𒲂ׂ�
	AbleMoveAround(m_Pos, able_move, &able_move_num);

	int random_num = rand() % able_move_num;

	// �ŏ��̈ړ�����������
	m_Direction = able_move[random_num] - m_Pos;
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

	AbleMoveAround(m_Pos, able_move, &able_move_num);

	// �����̐i��ł���x�N�g���̋t�̃x�N�g�����Z�o����
	IVec2 reverce_vec;
	reverce_vec.m_X = -m_Direction.m_X;
	reverce_vec.m_Y = -m_Direction.m_Y;
	
	std::vector<IVec2> new_able_move;
	// ���Ε����ɂ͂��������Ȃ��̂ŁA��₩��폜����
	for (int i = 0; i < able_move_num; ++i)
	{
		IVec2 vec = able_move[i] - m_Pos;
		if (vec == reverce_vec)continue;
		new_able_move.push_back(able_move[i]);
	}

	// �������ړ��\�Ȑ��Ŋ������]���ۑ�����
	int random_num = rand() % new_able_move.size();

	//�@�ړ�����
	m_RefStage->SetStage(m_Pos, new_able_move[random_num], this->GetObjectType());
	m_Direction = new_able_move[random_num] - m_Pos;
	m_Pos = new_able_move[random_num];
}

void PacMan::CharacterEnemy::AbleMoveAround(IVec2 pos_, IVec2* outVecArray_, int* ableMoveNum_)
{
	// ���g�̈ʒu����ړ��\�ȏꏊ��ۑ�����ϐ�
	IVec2 able_move[4];
	// �ړ��\�Ȑ���ۑ�����ϐ�
	int able_move_num = 0;

	// ���̈ړ�����W��ۑ����Ă����ϐ�
	IVec2  nextPos = pos_;

	// �E�Ɉړ��ł��邩�𒲂ׂ�
	nextPos.m_X++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ���Ɉړ��ł��邩�𒲂ׂ�
	nextPos = pos_;
	nextPos.m_X--;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ���Ɉړ��ł��邩�𒲂ׂ�
	nextPos = pos_;
	nextPos.m_Y++;
	if (m_RefStage->GetStageObject(nextPos) != ObjectType::TYPE_WALL) {
		able_move[able_move_num] = nextPos;
		able_move_num++;
	}

	// ��Ɉړ��ł��邩�𒲂ׂ�
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
