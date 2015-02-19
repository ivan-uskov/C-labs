#pragma once
#include "Complex.h"

struct EquationRoots3
{
    int numRoots;
    double roots[3];
};

EquationRoots3 Solve3(double a, double b, double c, double d);
