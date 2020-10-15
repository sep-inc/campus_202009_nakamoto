#ifndef ENEMY_ARRAY_H_
#define ENEMY_ARRAY_H_

#include "Enemy.h"

namespace PacMan
{
	class EnemyArray
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyArray(Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~EnemyArray();

		/*
			�������֐�
		*/
		void Init();

		/*
			�X�V�֐�
		*/
		void Update();

		/*
			�`��֐�
		*/
		void Draw();

	private:
		Enemy* m_Enemy[ENEMY_NUM];

	};
}


#endif