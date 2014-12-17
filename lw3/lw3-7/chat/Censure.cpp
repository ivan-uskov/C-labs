#include "stdafx.h"
#include "Censure.h"
#include <boost\algorithm\string.hpp>

using namespace std;


CCensure::CCensure(string const& censureFilePath)
    : m_error(false)
{
    ifstream input(censureFilePath);
    if (!input.bad())
    {
        ReadBadWords(input);
        input.close();
    }
    else
    {
        m_error = true;
    }
}


CCensure::~CCensure()
{
}

/* Operators */

bool CCensure::operator()(string const& word)const
{
    string lowerCase(word);
    boost::algorithm::to_lower(lowerCase);
    return !(m_badWords.find(lowerCase) != m_badWords.end());
}

/* Public methods */

bool CCensure::IsError()const
{
    return m_error;
}

/* Private methods */

void CCensure::ReadBadWords(std::istream & input)
{
    string str; 
    while (input >> str)
    {
        boost::algorithm::to_lower(str);
        m_badWords.insert(str);
    }
}