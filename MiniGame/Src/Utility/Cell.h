#ifndef CELL_H_
#define CELL_H_

struct Cell
{
	Cell() :
		m_X(-1), m_Y(-1)
	{}

	Cell(int x_, int y_) :
		m_X(x_), m_Y(y_)
	{}

	int m_X;	// マスの横軸
	int m_Y;	// マスの縦軸

};

#endif