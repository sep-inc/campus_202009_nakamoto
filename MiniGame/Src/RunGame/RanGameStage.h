#ifndef RAN_STAGE_H_
#define RAN_STAGE_H_

#include "RanDefinition.h"
#include "../Utility/Vec2.h"

namespace RunGame
{
	/**
	* @brief ステージクラス
	*/
	class RanGameStage
	{
	public:
		/**
		* @brief   コンストラクタ
		* @details 必要な情報を初期化する
		*/
		RanGameStage() :
			m_Stage{ 0 },
			m_Draw_Range_Min{ 0 },
			m_Draw_Range_Max{ 0 }
		{}

		/**
		* @brief   デストラクタ
		*/
		~RanGameStage() {}

		/**
		* @brief   初期化関数
		* @details ゲームの初期化時に1度だけ呼ぶ
		*/
		void Init();

		/**
		* @brief   描画関数関数
		* @details ステージに保存する
		*/
		void Draw();

		/**
		* @brief   当たり判定関数関数
		* @details プレイヤーの右の辺とブロックの左の辺との当たり判定
		*/

		/**
		* @brief     プレイヤーの右の辺とブロックの左の辺との当たり判定を行う関数
		* @param[in] pos_    プレイヤーの座標
		* @param[in] width_  横幅
		* @param[in] height_ 縦幅
		* @return  bool 当たっていたらTrueを返す
		*/
		bool HitPlyaerAndBlockLeftEdge(Vec2 pos_, int width_, int height_);

		/**
		* @brief     プレイヤーの下の辺とブロックの上の辺との当たり判定を行う関数
		* @param[in]  pos_        プレイヤーの座標
		* @param[in]  width_      横幅
		* @param[in]  height_     縦幅
		* @param[out] contactPos_ 当たったY軸の座標を返す
		* @return  bool 当たっていたらTrueを返す
		*/
		bool HitPlayerAndBlockTopEdge(Vec2 pos_, int width_, int height_, float* contactPos_);

		/**
		* @brief      ステージにセットする関数
		* @param[in]  pos_     座標
		*/
		void SetStage(Vec2 pos_);

	private:
		//! ステージを保存する変数
		int m_Stage[RANGAME_STAGE_HEIGHT][RANGAME_STAGE_WIDTH];

		//! 描画範囲の左端を保存する変数
		int m_Draw_Range_Min;

		//! 描画範囲の右端を保存する変数
		int m_Draw_Range_Max;

	};
}

#endif