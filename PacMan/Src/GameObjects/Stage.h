#ifndef STAGE_H_
#define STAGE_H_

#include "../Definition.h"
#include "../Utility/Vec2.h"
#include "StageObjects/StageObject.h"

// ステージ情報を扱うクラス
class Stage
{
public:
	Stage();

	~Stage(){}

	void Draw();

	void SetRandomPlacementObject(StageObject* stageObject_);

	const ObjectType GetStageObject(Vec2 pos_) const { return m_Stage[pos_.m_Y][pos_.m_X]; }
	
private:
	// 初期化用の空のステージデータ
	static const int m_BlankStage[STAGE_HEIGHT][STAGE_WIDTH];

	ObjectType m_Stage[STAGE_HEIGHT][STAGE_WIDTH];

};

#endif