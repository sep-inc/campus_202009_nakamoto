#ifndef ITEM_H_
#define ITEM_H_

#include "StageObject.h"

class Item : public StageObject
{
public:
	Item(Stage* stage_);

	~Item(){}

	void Init() override{}

	void Update() override{}

	void Draw() override;

	virtual inline ObjectType GetObjectType() const { return ObjectType::TYPE_ITEM; }


private:
	static int m_InstanceNum;

	int m_Id;

};

#endif