#ifndef ENEMY_AI_DEFEND_H_
#define ENEMY_AI_DEFEND_H_

#include "EnemyAIBase.h"

namespace PacMan
{
	/*
		���AI�N���X
	*/
	class EnemyAIDeffend : public EnemyAIBase
	{
	public:
		/*
			�R���X�g���N�^
		*/
		EnemyAIDeffend(IVec2* enemyPos_, EnemyParameter* enemyParam_, Stage* stage_);

		/*
			�f�X�g���N�^
		*/
		~EnemyAIDeffend(){}

		/*
			�X�V�֐�
			���ɍs�������Ԃ�Ԃ�
		*/
		ActionStateList Update() override;

	private:
		/*
			�A�C�e���̈ʒu�Ɉړ�����֐�
			����������true��Ԃ�
		*/
		bool HeadForItemPosition();

		
	};


}

#endif