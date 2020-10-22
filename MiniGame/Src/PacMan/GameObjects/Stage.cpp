#include "Stage.h"
#include "../../System/Drawer.h"
#include <string.h>
#include <vector>


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
	m_Stage{ PacMan::ObjectType::TYPE_EMPTY }, m_ItemArray{ nullptr }, m_IsGameOver{ false }
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));

	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			m_CostTable[y][x] = !m_BlankStage[y][x];
		}
	}

	m_Ater.CreateGraph(m_CostTable);

#ifdef ITEM_ON
	m_ItemArray = new ItemArray();
#endif
}

/*
	�f�X�g���N�^
*/
PacMan::Stage::~Stage()
{
	SAFE_DELETE(m_ItemArray);
}


/*
	�������֐�
*/
void PacMan::Stage::Init()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
	// �v���C���[�̏����l�����͂��炩���ߌ��߂Ă���
	m_Stage[PLAYER_INIT_POS_Y][PLAYER_INIT_POS_X] = PacMan::ObjectType::TYPE_PLAYER;
	m_IsGameOver = false;

	if (m_ItemArray) {
		m_ItemArray->Init();
		for (int i = 0; i < ITEM_NUM; ++i) {
			SetRandomPlacementObject(m_ItemArray->GetItem(i));
		}
	}
}


/*
	�`��֐�
*/
void PacMan::Stage::Draw()
{
	// �X�e�[�W�`��
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == PacMan::ObjectType::TYPE_WALL)Drawer::GetInstance().SetDrawBuffer(x, y, "��");
			else { Drawer::GetInstance().SetDrawBuffer(x, y, "�@"); }
		}

	}

	// �A�C�e���̕`��
	if (m_ItemArray)m_ItemArray->Draw();
}

void PacMan::Stage::SetRandomPlacementObject(StageObject* stageObject_)
{
	// �z�u�\�ȏꏊ��T��
	std::vector<IVec2> able_placement;
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == PacMan::ObjectType::TYPE_EMPTY) {
				able_placement.push_back(IVec2(x, y));
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
bool PacMan::Stage::HitItem(IVec2 pos_)
{
	if (!m_ItemArray) return false;
	
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_ItemArray->GetItem(i)) {
			
			// �������Ă�����Delete����true��Ԃ�
			if (m_ItemArray->GetItem(i)->GetPos() == pos_) {
				m_ItemArray->Destory(i);
				return true;
			}

		}
	}

	return false;
}


/*
	�I�u�W�F�N�g�̈ړ���X�e�[�W�ɃZ�b�g����֐�
*/
void PacMan::Stage::SetStage(IVec2 moveSource_, IVec2 moveDest_, PacMan::ObjectType type_)
{
	// �ړ�����I�u�W�F�N�g���v���C���[�̎�
	if (type_ == PacMan::ObjectType::TYPE_PLAYER) {
		// �ړ���ɃG�l�~�[������΃Q�[���I�[�o�[
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == PacMan::ObjectType::TYPE_ENEMY) {
			m_IsGameOver = true;
		}
	}
	// �ړ�����I�u�W�F�N�g���G�l�~�[�̎�
	else if (type_ == PacMan::ObjectType::TYPE_ENEMY) {
		// �ړ���Ƀv���C���[������΃Q�[���I�[�o�[
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == PacMan::ObjectType::TYPE_PLAYER) {
			m_IsGameOver = true;
		}
	}

	// �ړ���Ɉړ�������
	m_Stage[moveDest_.m_Y][moveDest_.m_X] = m_Stage[moveSource_.m_Y][moveSource_.m_X];
	// �ړ�������ɂ���
	m_Stage[moveSource_.m_Y][moveSource_.m_X] = PacMan::ObjectType::TYPE_EMPTY;
}


/*
	�A�C�e�����󂩂ǂ�����Ԃ��֐�
*/
bool PacMan::Stage::EmptyItem()
{
	if (!m_ItemArray) return false;

	// �A�C�e�����󂶂�Ȃ��Ȃ�U
	if (!m_ItemArray->Empty()) {
		return false;
	}

	// �A�C�e������Ȃ�^
	return true;
}

int PacMan::Stage::ItemTotalNum() const
{
	if (!m_ItemArray) return 0;
	return m_ItemArray->GetItemTotalNum();
}

IVec2 PacMan::Stage::GetRandomItemPos()
{	
	while (true)
	{
		Item* item = m_ItemArray->GetItem(rand() % ITEM_NUM);
		if (!item)continue;
		else 
			return item->GetPos();
	}
}

bool PacMan::Stage::FindShortestPath(std::vector<IVec2>* traceList_, IVec2 sourcePos_, IVec2 destPos_)
{
	if (m_BlankStage[sourcePos_.m_Y][sourcePos_.m_X] == 1)return false;
	if (m_BlankStage[destPos_.m_Y][destPos_.m_X]     == 1)return false;

	std::list<Cell> tmp = m_Ater.GetShortestPath(Cell(sourcePos_.m_X, sourcePos_.m_Y), Cell(destPos_.m_X, destPos_.m_Y));
	
	tmp.pop_front();

	std::vector<IVec2> ret_trace_list;
	
	for (const Cell& v : tmp)
	{
		ret_trace_list.push_back(IVec2(v.m_X, v.m_Y));
	}

	*traceList_ = ret_trace_list;
	
	return true;
}
