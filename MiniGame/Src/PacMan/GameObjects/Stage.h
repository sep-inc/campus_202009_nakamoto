#ifndef STAGE_H_
#define STAGE_H_

#include "../PacManDefinition.h"
#include "../../Utility/IVec2.h"
#include "StageObjects/ItemArray.h"
#include "../../Utility/Astar.h"
#include <list>

namespace PacMan
{
	// ステージ情報を扱うクラス
	class Stage
	{
	public:
		/*
			コンストラクタ
		*/
		Stage();

		/*
			デストラクタ
		*/
		~Stage();

		/*
			初期化関数
		*/
		void Init();

		/*
			描画関数
		*/
		void Draw();

		/*
			オブジェクトをランダムに配置する関数
		*/
		void SetRandomPlacementObject(StageObject* stageObject_);

		/*
			引数に設定した座標にどのオブジェクトがあるのかを返す関数
		*/
		const ObjectType GetStageObject(IVec2 pos_) const { return m_Stage[pos_.m_Y][pos_.m_X]; }

		/*
			アイテムと当たっているかを調べる関数
			あたっていた場合アイテムを消す
		*/
		bool HitItem(IVec2 pos_);

		/*
			オブジェクトの移動後ステージにセットする関数

			moveSource_ 移動元
			moveDest_   移動先
			type_       オブジェクトの種類
		*/
		void SetStage(IVec2 moveSource_, IVec2 moveDest_, PacMan::ObjectType type_);

		/*
			アイテムが存在するかどうかを返す関数
		*/
		bool EmptyItem();

		/*
			アイテムの数を返す関数
		*/
		int ItemTotalNum() const;

		/*
			ステージ上にあるどれかのアイテムの座標を返す
		*/
		IVec2 GetRandomItemPos();

		/*
			プレイヤーとエネミーが当たったかどうかを返す関数
		*/
		bool HitPlayerAndEnemy()const { return m_IsGameOver; }

		bool FindShortestPath(std::vector<IVec2>* traceList_, IVec2 sourcePos_, IVec2 destPos_);

	private:
		// 初期化用の空のステージデータ
		static const int m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH];

		// ステージの情報を保存する変数
		PacMan::ObjectType m_Stage[STAGE_HEIGHT][STAGE_WIDTH];

		ItemArray* m_ItemArray;

		// プレイヤーと敵が当たったかどうかを保存する変数
		bool m_IsGameOver;

		
		int m_CostTable[STAGE_HEIGHT][STAGE_WIDTH];
		MyAStarAlgorithm::Astar<STAGE_WIDTH, STAGE_HEIGHT> m_Ater;

	};
}

#endif