#pragma once
#include "stdafx.h"

class CWordCounter
{
public:

    typedef  std::map<std::string, size_t> Words;

    CWordCounter();
    ~CWordCounter();

    void operator()(std::string const& word);

    Words const& GetWords()const;
    void PrintWords(std::ostream & output)const;

private:

    std::string GetLowerCase(std::string const& word);
    Words m_words;
};

