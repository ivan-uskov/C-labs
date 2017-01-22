#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <list>
#include <exception>
#include <functional>
#include <algorithm>
#include <iterator>

#include <boost/algorithm/string/replace.hpp>

///=======================================
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702) // отключаем предупреждение компилятора Visual Studio об unreachable code
#include <boost/test/unit_test.hpp>
///=======================================
