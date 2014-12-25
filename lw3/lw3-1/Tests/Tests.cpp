#include "stdafx.h"
#include "../lw3-1-8/VectorProcessor.cpp"

using namespace std;

bool TestVectorProcessing(vector<double> start, vector<double> processed)
{
    ProcessVector(start);
    return start == processed;
}

BOOST_AUTO_TEST_SUITE(VectorProcessingTests)

BOOST_AUTO_TEST_CASE(SumEmptyVector)
{
    BOOST_CHECK_EQUAL(SumPositive({}), 0);
}

BOOST_AUTO_TEST_CASE(SumNegativeVector)
{
    BOOST_CHECK_EQUAL(SumPositive({ -2, -3, -4, -1, -42 }), 0);
}

BOOST_AUTO_TEST_CASE(SumVector)
{
    BOOST_CHECK_EQUAL(SumPositive({ 1, 7, -2, 3, -4, 1, -42 }), 12);
}

BOOST_AUTO_TEST_CASE(VectorProcessing)
{
    BOOST_CHECK(TestVectorProcessing({ 1, 7, -2, 3, -4, 1, -42 }, { -84, -11, -9, -8, -5, -4, 2 }));
}

BOOST_AUTO_TEST_SUITE_END()
