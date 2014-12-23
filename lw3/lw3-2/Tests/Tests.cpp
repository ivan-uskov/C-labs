#include "stdafx.h"
#include "../RemoveExtraBlanks/BlanksRemover.cpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(VectorProcessingTests)

BOOST_AUTO_TEST_CASE(CheckEmptyString)
{
    BOOST_CHECK_EQUAL(RemoveExtraSpaces({}), "");
}

BOOST_AUTO_TEST_CASE(CheckCorrectString)
{
    BOOST_CHECK_EQUAL(RemoveExtraSpaces({ "1234 1234" }), "1234 1234");
}

BOOST_AUTO_TEST_CASE(CheckNonTrimedString)
{
    BOOST_CHECK_EQUAL(RemoveExtraSpaces({ "  1234 1234  " }), "1234 1234");
}

BOOST_AUTO_TEST_CASE(CheckFullSpacesString)
{
    BOOST_CHECK_EQUAL(RemoveExtraSpaces({ "  1    2    3    4 1   2    3     4  " }), "1 2 3 4 1 2 3 4");
}

BOOST_AUTO_TEST_SUITE_END()
