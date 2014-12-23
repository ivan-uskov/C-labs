#include "stdafx.h"
#include "CalculateWords.h"
#include <boost\algorithm\string.hpp>

using namespace std;

WordFrequencies CalculateWordFrequencies(std::istream & stream)
{
    WordFrequencies words;
    string word;

    while (stream >> word)
    {
        boost::algorithm::to_lower(word);
        ++words[word];
    }

    return words;
}