#ifndef PLAYER_H_
#define PLAYER_H_

#include "StageObject.h"

class Player : public StageObject
{
public:
	Player(Stage* stage_);

	~Player(){}

	void Init() override;

	void Update() override;

	void Draw() override;

	virtual inline ObjectType GetObjectType()const override { return ObjectType::TYPE_PLAYER; }

private:


};

#endif