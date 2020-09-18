#include "Grid.h"
#include "GrobalObject.h"
#include "GlobalSystem.h"

/*
	どのマスに置くのかを決める関数
	成功したら保存してtrueを返す
	失敗したらfalseを返す
*/
bool Grid::Select(__int8 x_, __int8 y_, ObjectType type_)
{
	if (x_ < 0 || x_ > GRID_WIDTH) return false;
	if (y_ < 0 || y_ > GRID_HEIGHT) return false;

	// 空の場合
	if (m_Grid[y_][x_] == ObjectType::TYPE_EMPTY) {

		// 保存する
		m_Grid[y_][x_] = type_;

		// 置けたら判定を行う
		if (JudgmentWinner(type_) == true) {
			g_IsGameOver = true;
			g_WhosWon = type_;
		}
		if (DrawJudgment() == true) {
			g_IsGameOver = true;
			g_WhosWon = ObjectType::TYPE_EMPTY;
		}

		return true;
	}

	// 空じゃないならfalseを返す
	return false;
}


// 描画関数
// バッファに送る
void Grid::Draw()
{
	for (__int8 y = 0; y < GRID_HEIGHT; ++y) {
		for (__int8 x = 0; x < GRID_WIDTH; ++x) {
			
			g_Drawer.SetDrawBuffer(x, y, m_Grid[y][x]);
		}
	}
}


// 初期化関数
void Grid::Init()
{
	// 全て空で埋める
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			m_Grid[y][x] = ObjectType::TYPE_EMPTY;
		}
	}
}


bool Grid::JudgmentWinner(ObjectType type_)
{
	// 横軸を調べる
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		// 横軸全てが同じなら
		if (m_Grid[y][0] == type_
			&& m_Grid[y][1] == type_
			&& m_Grid[y][2] == type_)
		{
			return true;
		}
	};


	// 縦軸を調べる
	for (int x = 0; x < GRID_WIDTH; ++x) {
		// 横軸全てが同じなら
		if (m_Grid[0][x] == type_
			&& m_Grid[1][x] == type_
			&& m_Grid[2][x] == type_)
		{
			return true;
		}
	};


	// 斜めを調べる
	if (m_Grid[0][0] == type_
		&& m_Grid[1][1] == type_
		&& m_Grid[2][2] == type_)
	{
		return true;
	}
	else if (m_Grid[0][2] == type_
		&& m_Grid[1][1] == type_
		&& m_Grid[2][0] == type_)
	{
		return true;
	}


	return false;
}

// 引き分けかを調べる関数
bool Grid::DrawJudgment()
{
	// 横軸を調べる
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		// 横軸にプレイヤーがいたら
		if (m_Grid[y][0] == ObjectType::TYPE_PlAYER
			|| m_Grid[y][1] == ObjectType::TYPE_PlAYER
			|| m_Grid[y][2] == ObjectType::TYPE_PlAYER)
		{
			// 横軸にエネミーがいるか調べる
			if (m_Grid[y][0] == ObjectType::TYPE_PlAYER
				|| m_Grid[y][1] == ObjectType::TYPE_PlAYER
				|| m_Grid[y][2] == ObjectType::TYPE_PlAYER)
			{
			}
			else return false;
		}
		else return false;
	};


	// 縦軸を調べる
	for (int x = 0; x < GRID_WIDTH; ++x) {
		// 縦軸にプレイヤーがいたら
		if (m_Grid[0][x] == ObjectType::TYPE_PlAYER
			|| m_Grid[1][x] == ObjectType::TYPE_PlAYER
			|| m_Grid[2][x] == ObjectType::TYPE_PlAYER)
		{
			// 同じ軸にエネミーがいるか調べる
			if (m_Grid[0][x] == ObjectType::TYPE_PlAYER
				|| m_Grid[1][x] == ObjectType::TYPE_PlAYER
				|| m_Grid[2][x] == ObjectType::TYPE_PlAYER)
			{
			}
			else return false;
		}
		else return false;
	}


	// 斜めを調べる
	if (m_Grid[0][0] == ObjectType::TYPE_PlAYER
		|| m_Grid[1][1] == ObjectType::TYPE_PlAYER
		|| m_Grid[2][2] == ObjectType::TYPE_PlAYER)
	{
		if (m_Grid[0][0] == ObjectType::TYPE_ENEMY
			&& m_Grid[1][1] == ObjectType::TYPE_ENEMY
			&& m_Grid[2][2] == ObjectType::TYPE_ENEMY)
		{
		}
		else return false;
	}
	else return false;


	if (m_Grid[0][2] == ObjectType::TYPE_PlAYER
		|| m_Grid[1][1] == ObjectType::TYPE_PlAYER
		|| m_Grid[2][0] == ObjectType::TYPE_PlAYER)
	{
		if (m_Grid[0][2] == ObjectType::TYPE_ENEMY
			|| m_Grid[1][1] == ObjectType::TYPE_ENEMY
			|| m_Grid[2][0] == ObjectType::TYPE_ENEMY)
		{
		}
		else return false;
	}
	else return false;
	

	// 全ての軸に〇と☓が混同している
	return true;
}
