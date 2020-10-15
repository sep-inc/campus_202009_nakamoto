#ifndef STAGE_H_
#define STAGE_H_

#include "../Definition.h"
#include "../Utility/Vec2.h"
#include "StageObjects/ItemArray.h"

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
		const ObjectType GetStageObject(Vec2 pos_) const { return m_Stage[pos_.m_Y][pos_.m_X]; }

		/*
			アイテムと当たっているかを調べる関数
			あたっていた場合アイテムを消す
		*/
		bool HitItem(Vec2 pos_);

		/*
			オブジェクトの移動後ステージにセットする関数

			moveSource_ 移動元
			moveDest_   移動先
			type_       オブジェクトの種類
		*/
		void SetStage(Vec2 moveSource_, Vec2 moveDest_, ObjectType type_);

		/*
			アイテムが存在するかどうかを返す関数
		*/
		bool EmptyItem();

		/*
			プレイヤーとエネミーが当たったかどうかを返す関数
		*/
		bool HitPlayerAndEnemy()const { return m_IsGameOver; }

	private:
		// 初期化用の空のステージデータ
		static const int m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH];

		// ステージの情報を保存する変数
		ObjectType m_Stage[STAGE_HEIGHT][STAGE_WIDTH];

		ItemArray* m_ItemArray;

		// プレイヤーと敵が当たったかどうかを保存する変数
		bool m_IsGameOver;

	};
}

#endif