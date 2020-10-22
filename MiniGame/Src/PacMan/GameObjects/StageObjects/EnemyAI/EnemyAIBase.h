#ifndef ENEMY_AI_BASE_H_
#define ENEMY_AI_BASE_H_

#include "../../Stage.h"
#include "EnemyParamater.h"

namespace PacMan
{
	/*
		敵AIの基底クラス
	*/
	class EnemyAIBase
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyAIBase(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			デストラクタ
		*/
		virtual ~EnemyAIBase() {}


		/*
			更新関数
			次に行動する状態を返す
		*/
		virtual ActionStateList Update() = 0;

		/*
			初期化関数
		*/
		virtual void Init() {};

	protected:
		/*
			プレイヤーを見つけたかどうかを返す関数
		*/
		bool FoundPlayer(IVec2* enemyPos_, Stage* stage_,__int8 range_, IVec2* FoundPos_ = nullptr);


	protected:
		// エネミーの位置情報
		IVec2* m_RefEnemyPos;
		// エネミーのparameter情報
		EnemyParameter* m_EnemyParam;
		// ステージクラスの参照用変数
		Stage* m_RefStage;
	};
}

#endif