#ifndef CURSOR_H_
#define CURSOR_H_

#include "../../Utility/IVec2.h"


class Cursor
{
public:
	Cursor(IVec2 initPos_);


	inline void SetCursorPos(IVec2 pos_) { m_CursorPos = pos_; }

	inline IVec2 GetCursorPos() const { return m_CursorPos; }

private:
	IVec2 m_CursorPos;

};

#endif