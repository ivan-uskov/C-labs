#include "stdafx.h"
#include "../RemoveExtraBlanks/BlanksRemover.cpp"
using namespace std;

BOOST_AUTO_TEST_SUITE(VectorProcessingTests)

BOOST_AUTO_TEST_CASE(CheckEmptyString)
{
    string str;

    BOOST_CHECK(RemoveExtraSpaces(str) == "");
}

BOOST_AUTO_TEST_CASE(CheckCorrectString)
{
    string str("1234 1234");

    BOOST_CHECK(RemoveExtraSpaces(str) == "1234 1234");
}

BOOST_AUTO_TEST_CASE(CheckNonTrimedString)
{
    string str("  1234 1234  ");

    BOOST_CHECK(RemoveExtraSpaces(str) == "1234 1234");
}

BOOST_AUTO_TEST_CASE(CheckFullSpacesString)
{
    string str("  1    2    3    4 1   2    3     4  ");

    BOOST_CHECK(RemoveExtraSpaces(str) == "1 2 3 4 1 2 3 4");
}

BOOST_AUTO_TEST_SUITE_END()
