#include "Item.h"
#include "../Stage.h"
#include "../../System/Drawer.h"

using namespace PacMan;

int PacMan::Item::m_InstanceNum = 0;

/*
	コンストラクタ
*/
PacMan::Item::Item(PacMan::Stage* stage_) :
	StageObject{ stage_ }, m_Id{ 0 }
{
	// インスタンスが生成されるたびにカウントを1あげる
	m_InstanceNum++;
	// 現在のインスタンスの数をIDに設定する
	m_Id = m_InstanceNum;
}


/*
	デストラクタ
*/
PacMan::Item::~Item()
{
	// 消されるたびにカウントを減らす
	m_InstanceNum--;
}


/*
	描画関数
*/
void PacMan::Item::Draw()
{
	// Idによって描画クラスに送るリソースを変える
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
