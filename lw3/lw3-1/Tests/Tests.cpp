#include "stdafx.h"
#include "../lw3-1-8/VectorProcessor.cpp"
#include "../lw3-1-8/Transformer.cpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(VectorProcessingTests)

BOOST_AUTO_TEST_CASE(SumVector)
{
    double nums[] = { 1, 7, -2, 3, -4, 1, -42 };
    vector<double> vec(nums, nums + sizeof(nums) / sizeof(*nums));

    BOOST_CHECK(SumPositive(vec) == 12);
}

BOOST_AUTO_TEST_CASE(VectorProcessing)
{
    double nums[] = { 1, 7, -2, 3, -4, 1, -42 };
    vector<double> vec(nums, nums + sizeof(nums) / sizeof(*nums));

    ProcessVector(vec);

    double resultNums[] = { -84, -11, -9, -8, -5, -4, 2 };
    vector<double> resultVec(resultNums, resultNums + sizeof(resultNums) / sizeof(*resultNums));

    BOOST_CHECK(vec.size() == resultVec.size());
    BOOST_CHECK(equal(vec.begin(), vec.end(), resultVec.begin()));
}

BOOST_AUTO_TEST_SUITE_END()
