#include "stdafx.h"

bool DblsEqualy(double num1, double num2)
{
    return std::abs(num1 - num2) < DBL_EPSILON;
}