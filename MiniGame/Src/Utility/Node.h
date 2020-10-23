#ifndef NODE_H_
#define NODE_H_

#include "Cell.h"
#include <vector>

struct Node
{
	Node() :
		Node(0, 0)
	{}

	Node(int x_, int y_) :
		m_Pos(x_, y_), m_HeuristicCost(0), m_TotalCost(0)
	{}

	// ノードの座標
	Cell				m_Pos;

	// 隣接するノード
	std::vector<Node*>	m_Edges;

	// ヒューリスティックコスト
	float				m_HeuristicCost;

	// トータルコスト
	float				m_TotalCost;

};

#endif