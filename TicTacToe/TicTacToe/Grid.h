#ifndef GRID_H_
#define GRID_H_

#include "ObjectType.h"
#include "ObjectDefinition.h"

namespace TicTacToe
{
	/*
	グリッドクラス
*/
	class Grid
	{
		// グリッドのステップ項目
		enum class GRID_STEP : unsigned char
		{
			STEP_INIT,		// 初期化ステップ
			STEP_UPDATE,	// 更新ステップ
			STEP_RELEASE,	// 解放ステップ
		};

	public:
		// コンストラクタ
		Grid() :
			m_Grid(),
			m_CurrentStep(GRID_STEP::STEP_INIT)
		{
			Init();
		}

		// デストラクタ
		~Grid() {}

		// 初期化関数
		void Init();

		// どのマスに置くのかを決める関数
		// true  成功
		// false 失敗
		bool Select(__int8 x_, __int8 y_, ObjectType type_);

		// 描画関数
		// バッファに送る
		void Draw();

	private:
		// 勝敗判定関数
		// 引数のオブジェクトが勝っているかどうか
		bool JudgmentWinner(ObjectType type_);

		// 引き分けかを調べる関数
		bool DrawJudgment();

	private:
		// グリッド
		ObjectType m_Grid[GRID_HEIGHT][GRID_WIDTH];

		// 現在のステップを保存する変数
		GRID_STEP m_CurrentStep;
	};
}


#endif