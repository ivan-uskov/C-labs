#include "stdafx.h"
#include "../chat/Censure.cpp"

BOOST_AUTO_TEST_SUITE(CensureCheckerTests)

BOOST_AUTO_TEST_CASE(CheckInitCensure)
{
    CCensure censure("../noncensured_words");
    BOOST_CHECK(!censure.IsError());
}

BOOST_AUTO_TEST_CASE(CheckCensured)
{
    CCensure censure("../noncensured_words");
    BOOST_CHECK(!censure("beer"));
    BOOST_CHECK(censure("programming"));
}


BOOST_AUTO_TEST_SUITE_END()
