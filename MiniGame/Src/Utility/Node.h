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

	// �m�[�h�̍��W
	Cell				m_Pos;

	// �אڂ���m�[�h
	std::vector<Node*>	m_Edges;

	// �q���[���X�e�B�b�N�R�X�g
	float				m_HeuristicCost;

	// �g�[�^���R�X�g
	float				m_TotalCost;

};

#endif