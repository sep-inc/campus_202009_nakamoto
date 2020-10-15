#ifndef CHARACTERBASE_H_
#define CHARACTERBASE_H_

#include "Definition.h"
#include "Stage.h"

namespace Tron
{
	/**
* @brief キャラクター基底クラス
* @details プレイヤーとエネミーはこのクラスを継承する
*/
	class CharacterBase
	{
	public:

		/**
		* @brief コンストラクタ
		* @param[in] stage_ ステージクラスのアドレス
		* @param[in] type_  オブジェクトの種類
		*/
		CharacterBase(Stage* stage_, ObjectType type_) :
			m_PosX{ 0 },
			m_PosY{ 0 },
			m_IsDeath{ false },
			m_Type{ type_ },
			m_Direction{ Direction::DIRECTION_UP },
			m_RefStage{ stage_ }
		{}

		/**
		* @brief デストラクタ
		*/
		~CharacterBase() {}

		/**
		* @brief 初期化関数
		*/
		virtual void Init() = 0;

		/**
		* @brief 更新関数
		*/
		virtual void Update() = 0;

		/**
		* @brief   死んでいるかどうかを返す関数
		* @return  bool 死んでいたらtrueを返す
		*/
		inline bool IsDeath() { return m_IsDeath; }

	protected:
		/**
		* @brief 　移動方向を決める関数関数
		* @details 継承先のクラスはこの関数を定義し移動方向を決める
		*/
		virtual void DecideDirection() = 0;

		/**
		* @brief 　移動関数
		* @details 現在の方向を参照しその方向に1マス進む、事前に方向を決めておく必要がある
		*/
		void Move();

		/**
		* @brief 　ステージに座標とタイプを送る関数
		* @details 移動後この関数を使用することでステージの情報を更新することができる
		*/
		void SendToStage();

	protected:
		//! X座標を保存する変数
		__int8     m_PosX;

		//! Y座標を保存する変数
		__int8     m_PosY;

		//! 死亡しているかどうかを保存する変数
		bool       m_IsDeath;

		//! 識別変数
		ObjectType m_Type;

		//! 向いている方向を保存する変数
		Direction  m_Direction;

		//! ステージクラスの参照用変数
		Stage* m_RefStage;
	};
}

#endif