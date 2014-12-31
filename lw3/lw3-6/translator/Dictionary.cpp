#include "stdafx.h"
#include "Dictionary.h"
#include <boost\algorithm\string.hpp>
#include <clocale>

using namespace std;

std::string ToLower(std::string const& str)
{
    string becomeLowerCased(str);
    boost::algorithm::to_lower(becomeLowerCased);
    return becomeLowerCased;
}

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

/* Public methods */

std::string CDictionary::Translate(std::string const& engWord)const
{
    auto it = m_dictionary.find(ToLower(engWord));
    return it != m_dictionary.end() ? it->second : string();
}

bool CDictionary::IsError()const
{
    return m_error;
}

bool CDictionary::IsModified()const
{
    return m_newWords.size() > 0;
}

bool CDictionary::AddTranslation(std::string const& key, std::string const& value)
{
    string lowerKey(ToLower(key));
    if (m_dictionary.find(lowerKey) == m_dictionary.end())
    {
        m_dictionary[lowerKey] = value;
        m_newWords.push_back(lowerKey);
        return true;
    }
    return false;
}

void CDictionary::FlushNewWords()const
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
    string phrase, translation;
    while (!input.eof())
    {
        getline(input, phrase);
        translation = "oormveienrovenive";
        if (ParseTranslation(phrase, translation))
        {
            m_dictionary[phrase] = translation;
        }
    }
}

bool CDictionary::ParseTranslation(string & phrase, string & translation)const
{
    smatch matches;
    regex checker("^\\[([a-z]+)\\]\\s(.+)$", regex_constants::ECMAScript);

    if (regex_match(phrase, matches, checker))
    {
        string translationText(matches[2].str());

        phrase = matches[1].str();
        translation = translationText;
        return true;
    }
    return false;
}