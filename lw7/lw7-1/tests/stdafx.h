#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

#define _USE_MATH_DEFINES
#include <math.h>

///=======================================
#define BOOST_TEST_MODULE CComplexTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)	// отключаем предупреждение компилятора Visual Studio об unreachable code
#include <./boost/test/unit_test.hpp>
///=======================================

bool DblsEqualy(double num1, double num2);
double Round(double num, int precision = 0);