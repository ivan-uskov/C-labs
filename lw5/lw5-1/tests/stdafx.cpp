#include "stdafx.h"

//=================================================
#include <./boost/test/included/unit_test.hpp>
//=================================================

bool CheckDoublesAreEqual(double num1, double num2)
{
    return (num1 - num2) < DBL_EPSILON;
}