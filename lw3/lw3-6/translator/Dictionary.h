#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>

class CDictionary
{
public:

    CDictionary(std::string const& translationsFilePath);
    ~CDictionary();

    std::string Translate(std::string const& engWord)const;
    bool AddTranslation(std::string const& key, std::string const& value);
    bool IsModified()const;
    bool IsError()const;
    void FlushNewWords()const;

private:

    bool m_error;
    std::vector<std::string> m_newWords;
    const std::string m_translationsFilePath;
    std::map<std::string, std::string> m_dictionary;

    void ReadTranslations(std::ifstream & input);
    bool ParseTranslation(std::string const& phrase, std::string & key, std::string & translation)const;
};

