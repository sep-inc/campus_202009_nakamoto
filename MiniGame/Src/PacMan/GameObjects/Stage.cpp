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
	コンストラクタ
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
	デストラクタ
*/
PacMan::Stage::~Stage()
{
	SAFE_DELETE(m_ItemArray);
}


/*
	初期化関数
*/
void PacMan::Stage::Init()
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));
	// プレイヤーの初期値だけはあらかじめ決めておく
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
	描画関数
*/
void PacMan::Stage::Draw()
{
	// ステージ描画
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == PacMan::ObjectType::TYPE_WALL)Drawer::GetInstance().SetDrawBuffer(x, y, "■");
			else { Drawer::GetInstance().SetDrawBuffer(x, y, "　"); }
		}

	}

	// アイテムの描画
	if (m_ItemArray)m_ItemArray->Draw();
}

void PacMan::Stage::SetRandomPlacementObject(StageObject* stageObject_)
{
	// 配置可能な場所を探す
	std::vector<IVec2> able_placement;
	for (int y = 0; y < STAGE_HEIGHT; ++y) {
		for (int x = 0; x < STAGE_WIDTH; ++x) {
			if (m_Stage[y][x] == PacMan::ObjectType::TYPE_EMPTY) {
				able_placement.push_back(IVec2(x, y));
			}
		}
	}

	// 配列のどれを選ぶかをランダムに選ぶ
	int random_num = rand() % able_placement.size();

	stageObject_->SetPos(able_placement[random_num]);
	m_Stage[able_placement[random_num].m_Y][able_placement[random_num].m_X] = stageObject_->GetObjectType();
}


/*
	アイテムと当たっているかを調べる関数
*/
bool PacMan::Stage::HitItem(IVec2 pos_)
{
	if (!m_ItemArray) return false;
	
	for (int i = 0; i < ITEM_NUM; ++i) {
		if (m_ItemArray->GetItem(i)) {
			
			// 当たっていたらDeleteしてtrueを返す
			if (m_ItemArray->GetItem(i)->GetPos() == pos_) {
				m_ItemArray->Destory(i);
				return true;
			}

		}
	}

	return false;
}


/*
	オブジェクトの移動後ステージにセットする関数
*/
void PacMan::Stage::SetStage(IVec2 moveSource_, IVec2 moveDest_, PacMan::ObjectType type_)
{
	// 移動するオブジェクトがプレイヤーの時
	if (type_ == PacMan::ObjectType::TYPE_PLAYER) {
		// 移動先にエネミーがいればゲームオーバー
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == PacMan::ObjectType::TYPE_ENEMY) {
			m_IsGameOver = true;
		}
	}
	// 移動するオブジェクトがエネミーの時
	else if (type_ == PacMan::ObjectType::TYPE_ENEMY) {
		// 移動先にプレイヤーがいればゲームオーバー
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == PacMan::ObjectType::TYPE_PLAYER) {
			m_IsGameOver = true;
		}
	}

	// 移動先に移動元を代入
	m_Stage[moveDest_.m_Y][moveDest_.m_X] = m_Stage[moveSource_.m_Y][moveSource_.m_X];
	// 移動元を空にする
	m_Stage[moveSource_.m_Y][moveSource_.m_X] = PacMan::ObjectType::TYPE_EMPTY;
}


/*
	アイテムが空かどうかを返す関数
*/
bool PacMan::Stage::EmptyItem()
{
	if (!m_ItemArray) return false;

	// アイテムが空じゃないなら偽
	if (!m_ItemArray->Empty()) {
		return false;
	}

	// アイテムが空なら真
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
