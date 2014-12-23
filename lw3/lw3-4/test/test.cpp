#include "stdafx.h"
#include "../lw3-4/PrimeNumbersGenerator.cpp"

using namespace std;

bool IsSetsEqual(set<size_t> set1, set<size_t> set2)
{
    return set1 == set2;
}

BOOST_AUTO_TEST_SUITE(PrimeGeneratorTests)

    BOOST_AUTO_TEST_CASE(TestEmptySet)
    {
        BOOST_CHECK(IsSetsEqual(GeneratePrimeNumbersSet(0), {}));
    }

    BOOST_AUTO_TEST_CASE(TestOneElement)
    {
        BOOST_CHECK(IsSetsEqual(GeneratePrimeNumbersSet(2), { 2 }));
    }

    BOOST_AUTO_TEST_CASE(TestTwoElements)
    {
        BOOST_CHECK(IsSetsEqual(GeneratePrimeNumbersSet(3), { 2, 3 }));
    }

    BOOST_AUTO_TEST_CASE(TestFiveElements)
    {
        BOOST_CHECK(IsSetsEqual(GeneratePrimeNumbersSet(12), { 2, 3, 5, 7, 11 }));
    }

    BOOST_AUTO_TEST_CASE(TestSixtyElements)
    {
        BOOST_CHECK(IsSetsEqual(GeneratePrimeNumbersSet(60),
            { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 }));
    }

BOOST_AUTO_TEST_SUITE_END()