#include "Grid.h"
#include "GrobalObject.h"
#include "../System/Drawer.h"


/*

	コンストラクタ
*/
TicTacToe::Grid::Grid() :
	m_Grid(),
	m_CurrentStep(GRID_STEP::STEP_INIT),
	m_DrawBlankGrid{ "\0" },
	m_DrawGrid	   { "\0" }
{
	Init();

#pragma region 描画用ボードの初期化

	// フレーム初期化
	for (int y = GRID_FRAME_MIN_X; y < GRID_FRAME_HEIGHT; ++y) {
		for (int x = GRID_FRAME_MIN_Y; x < GRID_FRAME_WIDTH; ++x) {
			// 

			// xが奇数、yが1
			if (x % 2 == 1 && y == 1) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "┬ ");
			}

			// xが奇数、yがフレームの下段
			else if (x % 2 == 1 && y == GRID_FRAME_MAX_Y) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "┴ ");
			}

			// xが左端、yが奇数の時
			else if (x == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "├ ");
			}

			// xが右端、yが奇数の時
			else if (x == GRID_FRAME_MAX_X && y % 2 == 1) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "┤ ");
			}

			// xが偶数yが奇数なら
			else if (x % 2 == 0 && y % 2 == 1) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "─ ");
			}

			// xが奇数yが偶数なら
			else if (x % 2 == 1 && y % 2 == 0) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "│ ");
			}

			// xもyも偶数なら空白
			else if (x % 2 == 0 && y % 2 == 0) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "  ");
			}

			// xもyも奇数なら
			else if (x % 2 == 1 && y % 2 == 1) {
				strcpy_s(m_DrawBlankGrid[y][x], CHAR_SIZE, "┼ ");
			}
		}

	}

	// 角
	strcpy_s(m_DrawBlankGrid[GRID_FRAME_MIN_Y][GRID_FRAME_MIN_X], CHAR_SIZE, "┌ ");
	strcpy_s(m_DrawBlankGrid[GRID_FRAME_MIN_Y][GRID_FRAME_MAX_X], CHAR_SIZE, "┐ ");
	strcpy_s(m_DrawBlankGrid[GRID_FRAME_MAX_Y][GRID_FRAME_MIN_X], CHAR_SIZE, "└ ");
	strcpy_s(m_DrawBlankGrid[GRID_FRAME_MAX_Y][GRID_FRAME_MAX_X], CHAR_SIZE, "┘ ");


	// X軸に対するカウント
	__int8 count_x = 0;
	// Y軸に対するカウント
	__int8 count_y = 0;

	char buf[CHAR_SIZE] = { '\0' };

	for (int x = 0; x < GRID_FRAME_WIDTH; ++x)
	{
		if (x % 2 == 0 && x != 0)
		{
			buf[0] = 'A' + count_x;
			buf[1] = ' ';

			strcpy_s(m_DrawBlankGrid[0][x], CHAR_SIZE, buf);

			// カウントを進める
			count_x++;
		}
		else {
			strcpy_s(m_DrawBlankGrid[0][x], CHAR_SIZE, "　");
		}
	}


	for (int y = 0; y < GRID_FRAME_HEIGHT; ++y)
	{
		if (y % 2 == 0 && y != 0) {
			// バッファに文字コードAに対してカウントを足したものを代入する
			buf[0] = '1' + count_y;
			buf[1] = ' ';

			strcpy_s(m_DrawBlankGrid[y][0], CHAR_SIZE, buf);

			// カウントを進める
			count_y++;
		}
		else {
			strcpy_s(m_DrawBlankGrid[y][0], CHAR_SIZE, "　");
		}
	}

#pragma endregion
}



/*
	どのマスに置くのかを決める関数
	成功したら保存してtrueを返す
	失敗したらfalseを返す
*/
bool TicTacToe::Grid::Select(__int8 x_, __int8 y_, ObjectType type_)
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
		else if (DrawJudgment() == true) {
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
void TicTacToe::Grid::Draw()
{
	memcpy(m_DrawGrid, m_DrawBlankGrid, sizeof(m_DrawBlankGrid));

	for (__int8 y = 0; y < GRID_HEIGHT; ++y) {
		for (__int8 x = 0; x < GRID_WIDTH; ++x) {
			
			if (m_Grid[y][x] == ObjectType::TYPE_EMPTY) {
				strcpy_s(m_DrawGrid[y * 2 + 2][x * 2 + 2], "　");
				continue;
			}
			else if (m_Grid[y][x] == ObjectType::TYPE_PlAYER) {
				strcpy_s(m_DrawGrid[y * 2 + 2][x * 2 + 2], "〇");
			}
			else if (m_Grid[y][x] == ObjectType::TYPE_PlAYER) {
				strcpy_s(m_DrawGrid[y * 2 + 2][x * 2 + 2], "×");
			}
		}
	}

	for (__int8 y = 0; y < GRID_FRAME_HEIGHT; ++y) {
		for (__int8 x = 0; x < GRID_FRAME_WIDTH; ++x) {

			Drawer::GetInstance().SetDrawBuffer(x, y, m_DrawGrid[y][x]);
		}
	}
}


// 初期化関数
void TicTacToe::Grid::Init()
{
	// 全て空で埋める
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			m_Grid[y][x] = ObjectType::TYPE_EMPTY;
		}
	}
}


bool TicTacToe::Grid::JudgmentWinner(ObjectType type_)
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
bool TicTacToe::Grid::DrawJudgment()
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
				continue;
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
				continue;
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
			|| m_Grid[1][1] == ObjectType::TYPE_ENEMY
			|| m_Grid[2][2] == ObjectType::TYPE_ENEMY)
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
