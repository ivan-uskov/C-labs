#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

///=======================================
#define BOOST_TEST_MODULE CCarTests
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)	// отключаем предупреждение компилятора Visual Studio об unreachable code
#include <./boost/test/unit_test.hpp>
///=======================================

