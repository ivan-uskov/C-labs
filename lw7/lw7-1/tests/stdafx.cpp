#include "stdafx.h"

//=================================================
#include <./boost/test/included/unit_test.hpp>
//=================================================

bool DblsEqualy(double num1, double num2)
{
    return std::abs(num1 - num2) < DBL_EPSILON;
}

double Round(double num, int precision)
{
    for (int i = precision; i > 0; --i)
    {
        num *= 10;
    }

    num = std::round(num);

    for (int i = precision; i > 0; --i)
    {
        num /= 10;
    }

    return num;
}