#ifndef ENEMY_ARRAY_H_
#define ENEMY_ARRAY_H_

#include "Enemy.h"

namespace PacMan
{
	class EnemyManager
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyManager(Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~EnemyManager();

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