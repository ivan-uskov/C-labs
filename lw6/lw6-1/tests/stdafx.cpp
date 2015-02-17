#include "stdafx.h"

//=================================================
#include <./boost/test/included/unit_test.hpp>
//=================================================

bool DblsEqualy(double num1, double num2)
{
    return std::abs(num1 - num2) < DBL_EPSILON;
}