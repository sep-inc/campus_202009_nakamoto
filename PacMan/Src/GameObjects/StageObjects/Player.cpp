#include "Player.h"
#include "../../System/Drawer.h"
#include "../../System/Input.h"
#include "../../Definition.h"
#include "../Stage.h"

using namespace PacMan;

PacMan::Player::Player(Stage* stage_) :
	StageCharacter{ stage_ }
{
}

void PacMan::Player::Init()
{
	this->SetPos(Vec2(PLAYER_INIT_POS_X, PLAYER_INIT_POS_Y));

}

void PacMan::Player::Update()
{

	this->Move();
	
}

void PacMan::Player::Draw()
{
	Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "�Z");
}

void PacMan::Player::Move()
{
	int key = Input::GetKey();

	// �L�[�����͂���Ă��Ȃ���Ή��̔���������ɕԂ�
	if (key == -1) return;

	Vec2 next_pos = m_Pos;
	// ��L�[�������ꂽ�Ƃ�
	if (key == KEY_UP)         next_pos.m_Y--;
	// ���L�[�������ꂽ�Ƃ�
	else if (key == KEY_DOWN)  next_pos.m_Y++;
	// ���L�[�������ꂽ�Ƃ�
	else if (key == KEY_LEFT)  next_pos.m_X--;
	// �E�L�[�������ꂽ�Ƃ�
	else if (key == KEY_RIGHT) next_pos.m_X++;
	// ����ȊO�̃L�[�������ꂽ��ړ����Ȃ��̂ŉ��̔���������ɕԂ�
	else return;

	// �ړ���ɕǂ��Ȃ�������ړ�����
	if (m_RefStage->GetStageObject(next_pos) != ObjectType::TYPE_WALL) {
		m_RefStage->SetStage(m_Pos, next_pos, this->GetObjectType());
		m_Pos = next_pos;
		m_RefStage->HitItem(m_Pos);
	}
}
