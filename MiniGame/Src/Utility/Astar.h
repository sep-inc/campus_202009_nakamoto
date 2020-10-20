#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"
#include <list>
#include <math.h>

namespace MyAStarAlgorithm
{

	enum class EraseResult : unsigned char
	{
		NotFound,
		Erased,
		CouldntErased
	};


	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	class Astar
	{
	public:

		Astar() {}

		void CreateGraph(int(*costTable_)[TABLE_WIDTH]);

		std::list<Cell>  GetShortestPath(Cell startCell_, Cell goalCell_);

	private:

		/*
			�m�[�h�̏�����
		*/
		void InitCost();

		/*
			�w�肳�ꂽ���W���Z���͈͓̔��ɓ����Ă��邩�𒲂ׂ�
		*/
		bool IsCellWithinTheRange(int x_, int y_);

		/*
			�q���[���X�e�B�b�N�R�X�g�̌v�Z
			���[�N���b�h�����ŕԂ�
		*/
		float CalclaterHeuristicCost(const Node* node_, const Node* goal_);

		// �Z����r
		bool IsEqualCell(const Cell& a, const Cell& b);

		// �m�[�h�̍폜
		EraseResult EraseNode(std::list<Node*>& list, Node* node, float cost);

		// �I�[�v�����X�g�ɒǉ�
		bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost);
	private:
		const int _INFINITY = 100000.0f;

		Node m_Graph[TABLE_HEIGHT][TABLE_WIDTH];
		int  m_CostTable[TABLE_HEIGHT][TABLE_WIDTH];

	};



	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline void Astar<TABLE_WIDTH, TABLE_HEIGHT>::CreateGraph(int(*costTable_)[TABLE_WIDTH])
	{
		for (int y = 0; y < TABLE_HEIGHT; ++y) {
			for (int x = 0; x < TABLE_WIDTH; ++x) {
				m_CostTable[y][x] = costTable_[y][x];
			}
		}

		for (int y = 0; y < TABLE_HEIGHT; ++y) {
			for (int x = 0; x < TABLE_WIDTH; ++x) {

				// �Z���̍��W��ۑ�
				m_Graph[y][x].m_Pos.m_X = x;
				m_Graph[y][x].m_Pos.m_Y = y;

				// �אڂ���m�[�h�������ƒǉ�
				Cell adjacent_cells[] = {
					Cell(x, y - 1),
					Cell(x, y + 1),
					Cell(x - 1, y),
					Cell(x + 1, y),
				};

				for (const Cell& adjacent_cell : adjacent_cells)
				{
					// �����A�אڂ��Ă���m�[�h���L���ȃm�[�h�̏ꍇ�ǉ�����
					if (this->IsCellWithinTheRange(adjacent_cell.m_X, adjacent_cell.m_Y) == true &&
						m_CostTable[adjacent_cell.m_Y][adjacent_cell.m_X] == 1)
					{
						m_Graph[y][x].m_Edges.push_back(&m_Graph[adjacent_cell.m_Y][adjacent_cell.m_X]);
					}
				}
			}
		}
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline std::list<Cell> Astar<TABLE_WIDTH, TABLE_HEIGHT>::GetShortestPath(Cell startCell_, Cell goalCell_)
	{
		// �I�[�v�����X�g�ƃN���[�Y���X�g�̍쐬
		std::list<Node*> open_list;
		std::list<Node*> close_list;

		// �X�^�[�g�n�_�ƃS�[���n�_�̃m�[�h��ۑ�����
		const Node* start_node = &m_Graph[startCell_.m_Y][startCell_.m_X];
		const Node* goal_node = &m_Graph[goalCell_.m_Y][goalCell_.m_X];

		Cell last_update_cells[TABLE_HEIGHT][TABLE_WIDTH];

		InitCost();

		// �X�^�[�g�n�_�̃m�[�h���I�[�v�����X�g�ɒǉ�
		open_list.push_back(&m_Graph[startCell_.m_Y][startCell_.m_X]);

		// �I�[�v�����X�g���Ȃ��Ȃ�܂ŌJ��Ԃ�
		while (!open_list.empty())
		{
			// �I�[�v�����X�g����m�[�h�����o��
			// �g�[�^���R�X�g�ŏ����\�[�g���Ă���̂ŁA���߂̃m�[�h�����o��
			Node* search_node = *open_list.begin();

			// ���o�����̂ŃI�[�v�����X�g����폜����
			open_list.erase(open_list.begin());

			// ���o�����m�[�h���S�[�����ǂ����𔻒肷��
			if (IsEqualCell(search_node->m_Pos, goal_node->m_Pos) == true)
			{
				// �����S�[���n�_�ɓ���������I���
				close_list.push_back(search_node);
				break;
			}

			// �אڂ��Ă���m�[�h���I�[�v�����X�g�ɒǉ�����
			for (Node* adjacent_node : search_node->m_Edges)
			{
				// �q���[���X�e�B�b�N�R�X�g�̌v�Z���s��
				if (adjacent_node->m_HeuristicCost == _INFINITY)
				{
					adjacent_node->m_HeuristicCost = CalclaterHeuristicCost(adjacent_node, goal_node);
				}

				// �m�[�h�Ԃ̃R�X�g���擾
				float edge_cost = m_CostTable[adjacent_node->m_Pos.m_Y][adjacent_node->m_Pos.m_X];
				// �g�[�^���R�X�g���Z�o
				float total_cost = edge_cost + search_node->m_HeuristicCost + search_node->m_TotalCost;

				// �I�[�v�����X�g�Ƀm�[�h��ǉ�����
				if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
				{
					// �g�[�^���R�X�g���X�V
					adjacent_node->m_TotalCost = total_cost;

					// �o�H���X�V�����Z����ۑ�
					last_update_cells[adjacent_node->m_Pos.m_Y][adjacent_node->m_Pos.m_X] = search_node->m_Pos;
				}
			}

			bool is_add_close = false;

			// 
			for (const auto& v : close_list)
			{
				// ���݂̃m�[�h�Ɠ����Z�������邩�𒲂ׂ�
				if (IsEqualCell(search_node->m_Pos, v->m_Pos) == true)
				{
					// �����Z�����������ꍇ�ǉ����Ȃ�
					is_add_close = true;
					break;
				}
			}

			// �N���[�Y���X�g�ɒT�����I�����m�[�h��ǉ�����
			if (is_add_close == false) close_list.push_back(search_node);

			auto less = [](Node* a_, Node* b_) {
				if (a_->m_TotalCost < b_->m_TotalCost) {
					return true;
				}

				return false;
			};

			// �I�[�v�����X�g���\�[�g����
			open_list.sort(less);
		}


		// �I�[�v�����X�g����ɂȂ�o�H�T�����I��������
		// �o�H�𕜌�����

		std::list<Cell> route_list;

		// �S�[������ǉ����Ă���
		route_list.push_back(goalCell_);
		while (!route_list.empty())
		{
			Cell route = route_list.front();

			// �X�^�[�g�n�_�Ȃ�I��
			if (IsEqualCell(route, start_node->m_Pos) == true)
			{
				break;
			}
			else
			{
				if (IsCellWithinTheRange(route.m_X, route.m_Y) == true)
				{
					// �ǉ�
					route_list.push_front(last_update_cells[route.m_Y][route.m_X]);
				}
				else {
					// ������Ȃ�����
					break;
				}
			}
		}

		return route_list;
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline void Astar<TABLE_WIDTH, TABLE_HEIGHT>::InitCost()
	{
		for (int y = 0; y < TABLE_HEIGHT; ++y) {
			for (int x = 0; x < TABLE_WIDTH; ++x) {
				m_Graph[y][x].m_HeuristicCost = _INFINITY;
				m_Graph[y][x].m_TotalCost = 0;
			}
		}
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline bool Astar<TABLE_WIDTH, TABLE_HEIGHT>::IsCellWithinTheRange(int x_, int y_)
	{
		if (x_ >= 0 && x_ < TABLE_WIDTH &&
			y_ >= 0 && y_ < TABLE_HEIGHT)
		{
			return true;
		}

		return false;
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline float Astar<TABLE_WIDTH, TABLE_HEIGHT>::CalclaterHeuristicCost(const Node* node_, const Node* goal_)
	{
		float x = (float)(goal_->m_Pos.m_X - node_->m_Pos.m_X);
		float y = (float)(goal_->m_Pos.m_Y - node_->m_Pos.m_Y);

		return sqrtf(x * x + y * y);
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline bool Astar<TABLE_WIDTH, TABLE_HEIGHT>::IsEqualCell(const Cell& a_, const Cell& b_)
	{
		if (a_.m_X == b_.m_X &&
			a_.m_Y == b_.m_Y)
		{
			return true;
		}

		return false;
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline EraseResult Astar<TABLE_WIDTH, TABLE_HEIGHT>::EraseNode(std::list<Node*>& list_, Node* node_, float cost_)
	{
		// �N���[�Y���X�g�`�F�b�N
		for (auto itr = list_.begin(); itr != list_.end(); itr++)
		{
			// �m�[�h�Ɠ����Z�������邩���ׂ�
			if (IsEqualCell(node_->m_Pos, (*itr)->m_Pos) == true)
			{
				if (cost_ < (*itr)->m_TotalCost)
				{
					list_.erase(itr);
					return EraseResult::Erased;
				}
				else
				{
					return EraseResult::CouldntErased;
				}
			}
		}
		return EraseResult::NotFound;
	}

	template<int TABLE_WIDTH, int TABLE_HEIGHT>
	inline bool Astar<TABLE_WIDTH, TABLE_HEIGHT>::AddAdjacentNode(std::list<Node*>& openList_, std::list<Node*>& closeList_, Node* adjacentNode_, float cost_)
	{
		bool can_update = true;
		// �N���[�Y���X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
		if (EraseNode(closeList_, adjacentNode_, cost_) == EraseResult::CouldntErased)
		{
			can_update = false;
		}

		// �I�[�v�����X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
		if (EraseNode(closeList_, adjacentNode_, cost_) == EraseResult::CouldntErased)
		{
			can_update = false;
		}

		if (can_update == true)
		{
			openList_.push_back(adjacentNode_);
			return true;
		}

		return false;
	}

}


#endif