#include "Stage.h"
#include "../System/Drawer.h"
#include "StageObjects/Item.h"
#include "StageObjects/StageObject.h"
#include <string.h>
#include <vector>

using namespace PacMan;

const int PacMan::Stage::m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,1,1,0,1,1,0,0,0,1},
	{1,0,1,0,1,0,0,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,1,0,0,0,1,0,1,0,1},
	{1,0,1,0,1,1,0,1,1,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1},
};


/*
	�R���X�g���N�^
*/
PacMan::Stage::Stage() :
	m_Stage{ ObjectType::TYPE_EMPTY }, m_Item{ nullptr }, m_IsGameOver{ false }
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
}

/*
	�f�X�g���N�^
*/
PacMan::Stage::~Stage()
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
}


/*
	�������֐�
*/
void PacMan::Stage::Init()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
	m_Stage[PLAYER_INIT_POS_Y][PLAYER_INIT_POS_X] = ObjectType::TYPE_PLAYER;
	m_IsGameOver = false;

#ifdef ITEM_ON
	for (int i = 0; i < ITEM_NUM; ++i) {
		SAFE_DELETE(m_Item[i]);
	}
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i] == nullptr) {
			m_Item[i] = new PacMan::Item(this);
		}
		this->SetRandomPlacementObject(m_Item[i]);
	}
#endif
}


/*
	�`��֐�
*/
void PacMan::Stage::Draw()
{
	// �X�e�[�W�`��
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == ObjectType::TYPE_WALL)Drawer::GetInstance().SetDrawBuffer(x, y, "��");
			else { Drawer::GetInstance().SetDrawBuffer(x, y, "�@"); }
		}

	}

	// �A�C�e���̕`��
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) {
			m_Item[i]->Draw();
		}
	}
}

void PacMan::Stage::SetRandomPlacementObject(StageObject* stageObject_)
{
	// �z�u�\�ȏꏊ��T��
	std::vector<Vec2> able_placement;
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == ObjectType::TYPE_EMPTY) {
				able_placement.push_back(Vec2(x, y));
			}
		}
	}

	// �z��̂ǂ��I�Ԃ��������_���ɑI��
	int random_num = rand() % able_placement.size();

	stageObject_->SetPos(able_placement[random_num]);
	m_Stage[able_placement[random_num].m_Y][able_placement[random_num].m_X] = stageObject_->GetObjectType();
}


/*
	�A�C�e���Ɠ������Ă��邩�𒲂ׂ�֐�
*/
bool PacMan::Stage::HitItem(Vec2 pos_)
{
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) {
			
			// �������Ă�����Delete����true��Ԃ�
			if (m_Item[i]->GetPos() == pos_) {
				SAFE_DELETE(m_Item[i]);
				return true;
			}

		}
	}

	return false;
}


/*
	�I�u�W�F�N�g�̈ړ���X�e�[�W�ɃZ�b�g����֐�
*/
void PacMan::Stage::SetStage(Vec2 moveSource_, Vec2 moveDest_, ObjectType type_)
{
	// �ړ�����I�u�W�F�N�g���v���C���[�̎�
	if (type_ == ObjectType::TYPE_PLAYER) {
		// �ړ���ɃG�l�~�[������΃Q�[���I�[�o�[
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == ObjectType::TYPE_ENEMY) {
			m_IsGameOver = true;
		}
	}
	// �ړ�����I�u�W�F�N�g���G�l�~�[�̎�
	else if (type_ == ObjectType::TYPE_ENEMY) {
		// �ړ���Ƀv���C���[������΃Q�[���I�[�o�[
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == ObjectType::TYPE_PLAYER) {
			m_IsGameOver = true;
		}
	}

	// �ړ���Ɉړ�������
	m_Stage[moveDest_.m_Y][moveDest_.m_X] = m_Stage[moveSource_.m_Y][moveSource_.m_X];
	// �ړ�������ɂ���
	m_Stage[moveSource_.m_Y][moveSource_.m_X] = ObjectType::TYPE_EMPTY;
}


/*
	�A�C�e�����󂩂ǂ�����Ԃ��֐�
*/
bool PacMan::Stage::EmptyItem()
{
#ifndef ITEM_ON
	return false;
#endif
	// ��ł��A�C�e�����c���Ă�����false��Ԃ�
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_Item[i]) return false;
	}

	return true;
}
