#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <list>
#include <exception>
#include <functional>
#include <algorithm>

///=======================================
#define BOOST_TEST_MODULE TranslatorTestsModule
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702) // отключаем предупреждение компилятора Visual Studio об unreachable code
#include <boost/test/unit_test.hpp>
///=======================================
