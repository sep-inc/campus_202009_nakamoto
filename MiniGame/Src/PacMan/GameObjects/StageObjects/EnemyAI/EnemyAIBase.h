#ifndef ENEMY_AI_BASE_H_
#define ENEMY_AI_BASE_H_

#include "../CharacterPlayer.h"

class EnemyAIBase
{
public:
	EnemyAIBase(){}

	virtual ~EnemyAIBase(){}

	virtual void Init() = 0;

	virtual void Update() = 0;
	
	

};

#endif