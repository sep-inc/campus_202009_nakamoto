#ifndef ENEMY_AI_CHASE_H_
#define ENEMY_AI_CHASE_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	class EnemyAIChase : public EnemyAIBase
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyAIChase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			デストラクタ
		*/
		~EnemyAIChase() {}

		/*
			更新関数
			次に行動する状態を返す
		*/
		ActionStateList Update() override;

		/*
			初期化関数
			AIが切り替わった時に一度だけ呼ぶ
		*/
		void Init() override;

	private:

		/*
			先回りする関数
			見失ったらfalseを返す
		*/
		bool Forestall();

		/*
			追いかける関数
			見失ったらfalseを返す
		*/
		bool Chase();

	private:
		// プレイヤーの前の前の座標を保存しておく変数
		IVec2 m_PlayerOldPos;

	};
}

#endif