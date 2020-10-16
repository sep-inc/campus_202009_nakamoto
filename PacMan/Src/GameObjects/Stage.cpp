#include "Stage.h"
#include "../System/Drawer.h"
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
	m_Stage{ ObjectType::TYPE_EMPTY }, m_ItemArray{ nullptr }, m_IsGameOver{ false }
{
	memcpy(m_Stage, m_BlankStage, sizeof(m_BlankStage));

#ifdef ITEM_ON
	m_ItemArray = new ItemManager();
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
	m_Stage[PLAYER_INIT_POS_Y][PLAYER_INIT_POS_X] = ObjectType::TYPE_PLAYER;
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
			if (m_Stage[y][x] == ObjectType::TYPE_WALL)Drawer::GetInstance().SetDrawBuffer(x, y, "■");
			else { Drawer::GetInstance().SetDrawBuffer(x, y, "　"); }
		}

	}

	// アイテムの描画
	if (m_ItemArray)m_ItemArray->Draw();
}

void PacMan::Stage::SetRandomPlacementObject(StageObject* stageObject_)
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


/*
	アイテムと当たっているかを調べる関数
*/
bool PacMan::Stage::HitItem(Vec2 pos_)
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
void PacMan::Stage::SetStage(Vec2 moveSource_, Vec2 moveDest_, ObjectType type_)
{
	// 移動するオブジェクトがプレイヤーの時
	if (type_ == ObjectType::TYPE_PLAYER) {
		// 移動先にエネミーがいればゲームオーバー
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == ObjectType::TYPE_ENEMY) {
			m_IsGameOver = true;
		}
	}
	// 移動するオブジェクトがエネミーの時
	else if (type_ == ObjectType::TYPE_ENEMY) {
		// 移動先にプレイヤーがいればゲームオーバー
		if (m_Stage[moveDest_.m_Y][moveDest_.m_X] == ObjectType::TYPE_PLAYER) {
			m_IsGameOver = true;
		}
	}

	// 移動先に移動元を代入
	m_Stage[moveDest_.m_Y][moveDest_.m_X] = m_Stage[moveSource_.m_Y][moveSource_.m_X];
	// 移動元を空にする
	m_Stage[moveSource_.m_Y][moveSource_.m_X] = ObjectType::TYPE_EMPTY;
}


/*
	アイテムが空かどうかを返す関数
*/
bool PacMan::Stage::EmptyItem()
{
	if (!m_ItemArray) return false;

	// アイテムが空なら偽
	if (!m_ItemArray->Empty()) {
		return false;
	}

	// アイテムが空なら真
	return true;
}
