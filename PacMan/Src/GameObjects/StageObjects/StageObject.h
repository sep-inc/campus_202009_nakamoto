#ifndef STAGE_OBJECT_H_
#define STAGE_OBJECT_H_

#include "../../Utility/Vec2.h"
#include "../../Definition.h"

class Stage;

/*
	�X�e�[�W�ɔz�u����I�u�W�F�N�g�̊��N���X
*/
class StageObject
{
public:
	StageObject(Stage* stage_);

	virtual ~StageObject(){}

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual inline ObjectType GetObjectType() const = 0;

	inline void SetPos(Vec2 vec_) { m_Pos = vec_; }


protected:
	Vec2 m_Pos;
	Stage* m_RefStage;


};

#endif