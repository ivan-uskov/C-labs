#pragma once

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
    bool ParseTranslation(std::string & phrase, std::string & translation)const;
};

