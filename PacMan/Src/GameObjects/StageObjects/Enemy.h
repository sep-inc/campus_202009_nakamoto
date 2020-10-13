#ifndef ENEMY_H_
#define ENEMY_H_

#include "../StageObjects/StageObject.h"


class Enemy : public StageObject
{
public:
	Enemy(Stage* stage_);

	~Enemy(){}

	void Init() override;

	void Update() override;

	void Draw() override;

	virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_ENEMY; }


private:
	void Move();

private:
	int m_Timer;

};

#endif