#include "Calc.h"

__int8 Calc::Abs(__int8 a)
{
    if (a >= 0) {
        return a;
    }
    else {
        return -a;
    }
}
