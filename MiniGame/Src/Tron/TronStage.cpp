#include "TronStage.h"
#include "../System/Drawer.h"
#include <string.h>


void Tron::TronStage::Init()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
}

void Tron::TronStage::SetStage(__int8 x_, __int8 y_, ObjectType type_)
{
	m_Stage[y_ + 1][x_ + 1] = type_;
}

void Tron::TronStage::Draw()
{
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			switch (m_Stage[y][x])
			{
			case ObjectType::TYPE_EMPTY:
				Drawer::GetInstance().SetDrawBuffer(x, y, "  ");
				break;

			case ObjectType::TYPE_PLAYRE:
				Drawer::GetInstance().SetDrawBuffer(x, y, "■");
				break;

			case ObjectType::TYPE_ENEMY:
				Drawer::GetInstance().SetDrawBuffer(x, y, "□");
				break;

			case ObjectType::TYPE_WALL:
				Drawer::GetInstance().SetDrawBuffer(x, y, "〇");
				break;

			default:
				break;
			}
		}
	}

}
