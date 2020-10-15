#ifndef TIC_ENEMY_H_
#define TIC_ENEMY_H_

#include "ObjectBase.h"

namespace TicTacToe
{
	class Enemy : public ObjectBase
	{
		// エネミーのステップ項目
		enum class EnemyStep : unsigned char
		{
			STEP_INIT,		// 初期化ステップ
			STEP_UPDATE,	// 更新ステップ
			STEP_RELEASE,	// 解放ステップ
		};


	public:
		// コンストラクタ
		Enemy() :
			ObjectBase(ObjectType::TYPE_ENEMY),
			m_CurrentStep(EnemyStep::STEP_INIT)
		{}

		// デストラクタ
		~Enemy() {}

		// 初期化関数
		void Init() override;

		// ステップの更新関数
		void StepUpdate() override;


	private:

		// どのマスの横軸に置くかを決める関数
		__int8 SelectHorizontal() override;

		// どのマスの縦軸に置くかを決める関数
		__int8 SelectVertical() override;


	private:
		// 現在のステップを保存する変数
		EnemyStep m_CurrentStep;

	};
}

#endif