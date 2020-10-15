#ifndef ENEMY_ARRAY_H_
#define ENEMY_ARRAY_H_

#include "Enemy.h"

namespace PacMan
{
	class EnemyArray
	{
	public:
		/*
			コンストラクタ
		*/
		EnemyArray(Stage* stage_);

		/*
			デストラクタ
		*/
		~EnemyArray();

		/*
			初期化関数
		*/
		void Init();

		/*
			更新関数
		*/
		void Update();

		/*
			描画関数
		*/
		void Draw();

	private:
		Enemy* m_Enemy[ENEMY_NUM];

	};
}


#endif