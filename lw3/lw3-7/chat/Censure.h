#pragma once
#include "stdafx.h"

class CCensure
{
public:

    CCensure(std::string const& censureFilePath);
    ~CCensure();

    bool operator()(std::string const& word)const;

    bool IsError()const;

private:

    bool m_error;
    std::set<std::string> m_badWords;

    void ReadBadWords(std::istream & input);

};

