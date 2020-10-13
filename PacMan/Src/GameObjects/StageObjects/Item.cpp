#include "Item.h"
#include "../Stage.h"
#include "../../System/Drawer.h"

int Item::m_InstanceNum = 0;

Item::Item(Stage* stage_) :
	StageObject{ stage_ }, m_Id{ 0 }
{
	m_InstanceNum++;
	m_Id = m_InstanceNum;
}

void Item::Draw()
{
	switch (m_Id)
	{
	case 1:
		Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "１");
		break;
	case 2:
		Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "２");
		break;
	case 3:
		Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "３");
		break;
	case 4:
		Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "４");
		break;
	case 5:
		Drawer::GetInstance().SetDrawBuffer(m_Pos.m_X, m_Pos.m_Y, "５");
		break;
	default:
		break;
	}

	
}
