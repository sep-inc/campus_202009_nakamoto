#ifndef ENEMY_AI_SAUNTERING_H_
#define ENEMY_AI_SAUNTERING_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	/*
		徘徊のAI
	*/
	class EnemyAISauntering : public EnemyAIBase
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyAISauntering(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
		* デストラクタ
		*/
		~EnemyAISauntering(){}
		
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
			移動可能な方向を返す関数
		*/
		std::vector<IVec2> GetAbleMoveDirection();

	private:
		/*
			現在のアイテムの数を保存する変数
		*/
		int m_CurrentItemTotalNum;
		
	};
}


#endif