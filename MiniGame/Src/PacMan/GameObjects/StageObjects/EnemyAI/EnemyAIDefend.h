#ifndef ENEMY_AI_DEFEND_H_
#define ENEMY_AI_DEFEND_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	/*
		守備AIクラス
	*/
	class EnemyAIDeffend : public EnemyAIBase
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyAIDeffend(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			デストラクタ
		*/
		~EnemyAIDeffend(){}

		/*
			更新関数
			次に行動する状態を返す
		*/
		ActionStateList Update() override;

	private:
		/*
			アイテムの位置に移動する関数
			到着したらtrueを返す
		*/
		bool HeadForItemPosition();

		
	};


}

#endif