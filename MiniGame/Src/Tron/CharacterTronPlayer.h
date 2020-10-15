#ifndef TRON_PLAYER_H_
#define TRON_PLAYER_H_

#include "CharacterBase.h"

namespace Tron
{
	/**
* @brief プレイヤークラス
*/
	class CharacterTronPlayer : public CharacterBase
	{
		/**
		* @enum Enum
		* プレイヤーのステップ
		*/
		enum class PlayerStep
		{
			STEP_INIT,
			STEP_UPDATE,
		};

	public:
		/**
		* @brief コンストラクタ
		* @param[in] stage_　ステージクラスのアドレス
		*/
		CharacterTronPlayer(TronStage* stage_) :
			CharacterBase{ stage_, ObjectType::TYPE_PLAYRE },
			m_CurrentStep{ PlayerStep::STEP_INIT }
		{}

		/**
		* @brief   初期化関数
		* @details ゲームの初期化時に1度だけ呼ぶ
		*/
		void Init() override;

		/**
		* @brief 　更新関数
		* @details 1フレームに一度だけ呼ぶ
		*/
		void Update() override;

	private:
		/**
		* @brief   移動する方向を選ぶ関数
		* @details 矢印キーで入力された方向を保存する
		*/
		void DecideDirection() override;

		/**
		* @brief   現在の座標にオブジェクトがあるかどうかを調べる関数
		* @return  bool 空ならtrue 空以外ならfalse を返す
		* @details 移動後ステージに情報を送る前に何があるかを調べる
		*/
		bool CheckHitObject();

	private:
		//! 現在のステップを保存する変数
		PlayerStep m_CurrentStep;

	};
}

#endif