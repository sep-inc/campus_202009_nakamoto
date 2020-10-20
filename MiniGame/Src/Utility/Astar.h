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
			ノードの初期化
		*/
		void InitCost();

		/*
			指定された座標がセルの範囲内に入っているかを調べる
		*/
		bool IsCellWithinTheRange(int x_, int y_);

		/*
			ヒューリスティックコストの計算
			ユークリッド距離で返る
		*/
		float CalclaterHeuristicCost(const Node* node_, const Node* goal_);

		// セル比較
		bool IsEqualCell(const Cell& a, const Cell& b);

		// ノードの削除
		EraseResult EraseNode(std::list<Node*>& list, Node* node, float cost);

		// オープンリストに追加
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

				// セルの座標を保存
				m_Graph[y][x].m_Pos.m_X = x;
				m_Graph[y][x].m_Pos.m_Y = y;

				// 隣接するノードを検索と追加
				Cell adjacent_cells[] = {
					Cell(x, y - 1),
					Cell(x, y + 1),
					Cell(x - 1, y),
					Cell(x + 1, y),
				};

				for (const Cell& adjacent_cell : adjacent_cells)
				{
					// もし、隣接しているノードが有効なノードの場合追加する
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
		// オープンリストとクローズリストの作成
		std::list<Node*> open_list;
		std::list<Node*> close_list;

		// スタート地点とゴール地点のノードを保存する
		const Node* start_node = &m_Graph[startCell_.m_Y][startCell_.m_X];
		const Node* goal_node = &m_Graph[goalCell_.m_Y][goalCell_.m_X];

		Cell last_update_cells[TABLE_HEIGHT][TABLE_WIDTH];

		InitCost();

		// スタート地点のノードをオープンリストに追加
		open_list.push_back(&m_Graph[startCell_.m_Y][startCell_.m_X]);

		// オープンリストがなくなるまで繰り返す
		while (!open_list.empty())
		{
			// オープンリストからノードを取り出す
			// トータルコストで昇順ソートしてあるので、初めのノードを取り出す
			Node* search_node = *open_list.begin();

			// 取り出したのでオープンリストから削除する
			open_list.erase(open_list.begin());

			// 取り出したノードがゴールかどうかを判定する
			if (IsEqualCell(search_node->m_Pos, goal_node->m_Pos) == true)
			{
				// もしゴール地点に到着したら終わり
				close_list.push_back(search_node);
				break;
			}

			// 隣接しているノードをオープンリストに追加する
			for (Node* adjacent_node : search_node->m_Edges)
			{
				// ヒューリスティックコストの計算を行う
				if (adjacent_node->m_HeuristicCost == _INFINITY)
				{
					adjacent_node->m_HeuristicCost = CalclaterHeuristicCost(adjacent_node, goal_node);
				}

				// ノード間のコストを取得
				float edge_cost = m_CostTable[adjacent_node->m_Pos.m_Y][adjacent_node->m_Pos.m_X];
				// トータルコストを算出
				float total_cost = edge_cost + search_node->m_HeuristicCost + search_node->m_TotalCost;

				// オープンリストにノードを追加する
				if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
				{
					// トータルコストを更新
					adjacent_node->m_TotalCost = total_cost;

					// 経路を更新したセルを保存
					last_update_cells[adjacent_node->m_Pos.m_Y][adjacent_node->m_Pos.m_X] = search_node->m_Pos;
				}
			}

			bool is_add_close = false;

			// 
			for (const auto& v : close_list)
			{
				// 現在のノードと同じセルがあるかを調べる
				if (IsEqualCell(search_node->m_Pos, v->m_Pos) == true)
				{
					// 同じセルがあった場合追加しない
					is_add_close = true;
					break;
				}
			}

			// クローズリストに探索し終えたノードを追加する
			if (is_add_close == false) close_list.push_back(search_node);

			auto less = [](Node* a_, Node* b_) {
				if (a_->m_TotalCost < b_->m_TotalCost) {
					return true;
				}

				return false;
			};

			// オープンリストをソートする
			open_list.sort(less);
		}


		// オープンリストが空になり経路探索が終了したら
		// 経路を復元する

		std::list<Cell> route_list;

		// ゴールから追加していく
		route_list.push_back(goalCell_);
		while (!route_list.empty())
		{
			Cell route = route_list.front();

			// スタート地点なら終了
			if (IsEqualCell(route, start_node->m_Pos) == true)
			{
				break;
			}
			else
			{
				if (IsCellWithinTheRange(route.m_X, route.m_Y) == true)
				{
					// 追加
					route_list.push_front(last_update_cells[route.m_Y][route.m_X]);
				}
				else {
					// 見つからなかった
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
		// クローズリストチェック
		for (auto itr = list_.begin(); itr != list_.end(); itr++)
		{
			// ノードと同じセルがあるか調べる
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
		// クローズリストに同じノードがあってリストの方のコストが高いなら削除
		if (EraseNode(closeList_, adjacentNode_, cost_) == EraseResult::CouldntErased)
		{
			can_update = false;
		}

		// オープンリストに同じノードがあってリストの方のコストが高いなら削除
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