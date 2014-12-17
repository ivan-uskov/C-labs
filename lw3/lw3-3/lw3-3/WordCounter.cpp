#include "stdafx.h"
#include "WordCounter.h"
#include <boost/algorithm/string.hpp>

using namespace std;

CWordCounter::CWordCounter()
{
}


CWordCounter::~CWordCounter()
{
}

/* Operators */

void CWordCounter::operator()(string const& word)
{
    auto wordInLower = GetLowerCase(word);
    auto it = m_words.find(wordInLower);
    if (it != m_words.end())
    {
        ++(it->second);
    }
    else
    {
        m_words[wordInLower] = 1;
    }
}

/* Public methods */

CWordCounter::Words const& CWordCounter::GetWords()const
{
    return m_words;
}

void CWordCounter::PrintWords(ostream & output)const
{
    ostream_iterator<string> out(output);
    auto FormatPair = [](std::pair<string, size_t> pair)
    {
        return pair.first + to_string(pair.second) + "\n";
    };
    transform(m_words.begin(), m_words.end(), out, FormatPair);
}

/* Private methods */

std::string CWordCounter::GetLowerCase(std::string const& word)
{
    string lowerCaseWord(word);
    boost::algorithm::to_lower(lowerCaseWord);

    return lowerCaseWord;
    
}