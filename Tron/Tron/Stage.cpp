#include "Stage.h"
#include "System.h"
#include <string.h>


void Tron::Stage::Init()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
}

void Tron::Stage::SetStage(__int8 x_, __int8 y_, ObjectType type_)
{
	m_Stage[y_ + 1][x_ + 1] = type_;
}

void Tron::Stage::Draw()
{
	char str[MAP_HEIGHT * MAP_WIDTH * 3] = { "\0" };

	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			switch (m_Stage[y][x])
			{
			case ObjectType::TYPE_EMPTY:
				strcat_s(str, "  ");
				break;

			case ObjectType::TYPE_PLAYRE:
				strcat_s(str, "■");
				break;

			case ObjectType::TYPE_ENEMY:
				strcat_s(str, "□");
				break;

			case ObjectType::TYPE_WALL:
				strcat_s(str, "〇");
				break;

			default:
				break;
			}
		}
		strcat_s(str, "\n");
	}

	// 描画クラスに渡す
	g_Drawer.SetDrawBuffer(str);
}
