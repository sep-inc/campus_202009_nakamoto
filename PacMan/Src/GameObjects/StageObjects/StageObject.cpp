#include "StageObject.h"
#include "../Stage.h"

StageObject::StageObject(Stage* stage_) :
	m_Pos{ 0,0 }, m_RefStage{ stage_ }
{
}

