#ifndef STAGE_H_
#define STAGE_H_

#include "Definition.h"

namespace Tron
{
	/**
* @brief ステージクラス
*/
	class Stage
	{
	public:
		/**
		* @brief   コンストラクタ
		* @details 初期化用のステージを初期化する
		*/
		Stage() :
			m_Stage{ ObjectType::TYPE_EMPTY },
			m_BlankStage{ ObjectType::TYPE_EMPTY }
		{
			// 上下の行を壁で埋める
			for (int i = 0; i < MAP_WIDTH; i++) {
				m_BlankStage[0][i] = ObjectType::TYPE_WALL;
				m_BlankStage[MAP_HEIGHT - 1][i] = ObjectType::TYPE_WALL;
			}

			// 左右の行を壁で埋める
			for (int i = 0; i < MAP_HEIGHT; i++) {
				m_BlankStage[i][0] = ObjectType::TYPE_WALL;
				m_BlankStage[i][MAP_WIDTH - 1] = ObjectType::TYPE_WALL;
			}
		}

		/**
		* @brief   デストラクタ
		*/
		~Stage() {}

		/**
		* @brief   初期化関数
		* @details ゲームの初期化時に1度だけ呼ぶ
		*/
		void Init();

		/**
		* @brief ステージにオブジェクトの情報を保存する関数
		* @param[in] x_ 　　X座標
		* @param[in] y_  　 Y座標
		* @param[in] type_  オブジェクトの種類
		* @details 引数の座標を壁付きの座標に変換して保存する
		*/
		void SetStage(__int8 x_, __int8 y_, ObjectType type_);

		/**
		* @brief ステージのオブジェクトの種類を返す関数
		* @param[in] x_ 　　X座標
		* @param[in] y_  　 Y座標
		*/
		inline ObjectType GetStageObject(__int8 x_, __int8 y_) { return m_Stage[y_ + 1][x_ + 1]; }

		/**
		* @brief 描画関数
		* @details ステージの情報をみて描画用の文字列を作成し描画クラスに送る
		*/
		void Draw();


	private:
		//! オブジェクトを保存するためのステージ配列
		ObjectType m_Stage[MAP_HEIGHT][MAP_WIDTH];

		//! 初期化用の壁だけのステージ配列
		ObjectType m_BlankStage[MAP_HEIGHT][MAP_WIDTH];

	};
}

#endif