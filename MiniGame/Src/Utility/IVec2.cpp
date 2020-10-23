#include "IVec2.h"

bool IVec2::Zero() const
{
    if (m_X != 0) return false;
    else if (m_Y != 0) return false;
    return true;
}
