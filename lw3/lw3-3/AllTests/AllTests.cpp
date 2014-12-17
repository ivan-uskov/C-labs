#include "stdafx.h"
#include "../lw3-3/WordCounter.cpp"

using namespace std;

struct WordCounterFixture
{
    CWordCounter counter;
};

bool IsEqualWordCounts(CWordCounter::Words const& words1, CWordCounter::Words const& words2)
{
    return words1 == words2;
}

BOOST_FIXTURE_TEST_SUITE(WordCounterTests, WordCounterFixture)

    BOOST_AUTO_TEST_CASE(TestInsertOneWord)
    {
        counter("Hello");

        BOOST_CHECK(IsEqualWordCounts(counter.GetWords(), { { "hello", 1 } }));
    }

    BOOST_AUTO_TEST_CASE(TestInsertTwoWords)
    {
        counter("Hello");
        counter("Privet");

        BOOST_CHECK(IsEqualWordCounts(counter.GetWords(), { { "hello", 1 }, { "privet", 1 } }));
    }

    BOOST_AUTO_TEST_CASE(TestInsertWordTwice)
    {
        counter("Privet");
        counter("Privet");

        BOOST_CHECK(IsEqualWordCounts(counter.GetWords(), { { "privet", 2 } }));
    }

BOOST_AUTO_TEST_SUITE_END()