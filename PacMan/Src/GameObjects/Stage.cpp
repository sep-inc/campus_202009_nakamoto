#include "Stage.h"
#include "../System/Drawer.h"
#include <string.h>
#include <vector>

const int Stage::m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH] =
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

Stage::Stage()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
	m_Stage[PLAYER_INIT_POS_Y][PLAYER_INIT_POS_X] = ObjectType::TYPE_PLAYER;

}

void Stage::Draw()
{
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == ObjectType::TYPE_WALL)Drawer::GetInstance().SetDrawBuffer(x, y, "■");
			else { Drawer::GetInstance().SetDrawBuffer(x, y, "　"); }
		}

	}
}

void Stage::SetRandomPlacementObject(StageObject* stageObject_)
{
	// 配置可能な場所を探す
	std::vector<Vec2> able_placement;
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == ObjectType::TYPE_EMPTY) {
				able_placement.push_back(Vec2(x, y));
			}
		}
	}

	// 配列のどれを選ぶかをランダムに選ぶ
	int random_num = rand() % able_placement.size();

	stageObject_->SetPos(able_placement[random_num]);
	m_Stage[able_placement[random_num].m_Y][able_placement[random_num].m_X] = stageObject_->GetObjectType();
}
