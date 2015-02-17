// stdafx.cpp : source file that includes just the standard includes
// numbers.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

bool DblsEqualy(double num1, double num2)
{
    return std::abs(num1 - num2) < DBL_EPSILON;
}

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
