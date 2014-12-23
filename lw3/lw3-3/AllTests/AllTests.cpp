#include "stdafx.h"
#include "../lw3-3/CalculateWords.cpp"
#include <sstream>

using namespace std;

// Возвращает true, если вычисленные частоты встеречаемости слов в переданном тексте совпадают с ожидаемыми
bool WordFrequenciesCalculationIsCorrect(std::string const& inputText, WordFrequencies const& expectedWordFrequencies)
{
    auto calculetedWordFrequncies = CalculateWordFrequencies(istringstream(inputText));
    return calculetedWordFrequncies == expectedWordFrequencies;
}

BOOST_AUTO_TEST_SUITE(WordCounterTests, WordCounterFixture)

    BOOST_AUTO_TEST_CASE(TestInsertOneWord)
    {
        BOOST_CHECK(WordFrequenciesCalculationIsCorrect("Hello", { { "hello", 1 } }));
    }

    BOOST_AUTO_TEST_CASE(TestInsertTwoWords)
    {
        BOOST_CHECK(WordFrequenciesCalculationIsCorrect("Hello Privet", { { "hello", 1 }, { "privet", 1 } }));
    }

    BOOST_AUTO_TEST_CASE(TestInsertWordTwice)
    {
        BOOST_CHECK(WordFrequenciesCalculationIsCorrect("Privet PriveT", { { "privet", 2 } }));
    }

BOOST_AUTO_TEST_SUITE_END()