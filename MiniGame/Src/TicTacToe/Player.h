#ifndef TIC_PLAYER_H_
#define TIC_PLAYER_H_

#include "ObjectBase.h"

namespace TicTacToe
{
	/*
	プレイヤークラス
*/
	class Player : public ObjectBase
	{
		// プレイヤーのステップ項目
		enum class PlayerStep : unsigned char
		{
			STEP_INIT,		// 初期化ステップ
			STEP_UPDATE,	// 更新ステップ
			STEP_RELEASE,	// 解放ステップ
		};

	public:
		// コンストラクタ
		Player() :
			ObjectBase(ObjectType::TYPE_PlAYER),
			m_CurrentStep(PlayerStep::STEP_INIT)
		{}

		// デストラクタ
		~Player() {}

		// 初期化関数
		void Init() override;

		// ステップの更新関数
		void StepUpdate() override;

	private:
		// どのマスの横軸に置くかを決める関数
		__int8 SelectHorizontal() override;

		// どのマスの縦軸に置くかを決める関数
		__int8 SelectVertical() override;



		// 現在のステップを保存する変数
		PlayerStep m_CurrentStep;

	};
}

#endif