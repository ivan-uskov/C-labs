#include "stdafx.h"
#include "Dictionary.h"
#include <boost\algorithm\string.hpp>
#include <clocale>

using namespace std;

CDictionary::CDictionary(string const& translationsFilePath)
    : m_error(false)
    , m_translationsFilePath(translationsFilePath)
{
    setlocale(LC_ALL, "Russian");
    ifstream input(m_translationsFilePath);
    if (!input.bad())
    {
        ReadTranslations(input);
        input.close();
    }
    else
    {
        m_error = true;
    }
}


CDictionary::~CDictionary()
{
}

/* Operators */

std::string CDictionary::operator()(std::string const& engWord)const
{
    auto it = m_dictionary.find(GetLower(engWord));
    return it != m_dictionary.end() ? it->second : string();
}

/* Public methods */

bool CDictionary::IsError()const
{
    return m_error;
}

bool CDictionary::IsModified()const
{
    return m_newWords.size() > 0;
}

bool CDictionary::Add(std::string const& key, std::string const& value)
{
    string lowerKey(GetLower(key));
    if (m_dictionary.find(lowerKey) == m_dictionary.end())
    {
        m_dictionary[lowerKey] = value;
        m_newWords.push_back(lowerKey);
        return true;
    }
    return false;
}

void CDictionary::FlushNewWords()
{
    ofstream output(m_translationsFilePath, ios::app);
    output << endl;

    for (string const& str : m_newWords)
    {
        auto it = m_dictionary.find(str);
        if (it != m_dictionary.end())
        {
            output << "[" << it->first << "] " << it->second << endl;
        }
    }

    output.close();
}

/* Private methods */

void CDictionary::ReadTranslations(ifstream & input)
{
    string str;
    while (!input.eof())
    {
        getline(input, str);
        TryReadTranslation(GetLower(str));
    }
}

void CDictionary::TryReadTranslation(std::string const& str)
{
    smatch matches;
    regex checker("^\\[([a-z]+)\\]\\s(.+)$", regex_constants::ECMAScript);
    if (regex_match(str, matches, checker))
    {
        m_dictionary[matches[1].str()] = matches[2].str();
    }
}

std::string CDictionary::GetLower(std::string const& str)const
{
    string becomeLowerCased(str);
    boost::algorithm::to_lower(becomeLowerCased);
    return becomeLowerCased;
}