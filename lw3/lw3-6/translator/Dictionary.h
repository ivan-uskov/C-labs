#pragma once

class CDictionary
{
public:

    CDictionary(std::string const& translationsFilePath);
    ~CDictionary();

    std::string operator()(std::string const& engWord)const;

    bool Add(std::string const& key, std::string const& value);
    bool IsModified()const;
    bool IsError()const;
    void FlushNewWords();

private:

    bool m_error;
    std::vector<std::string> m_newWords;
    const std::string m_translationsFilePath;
    std::map<std::string, std::string> m_dictionary;

    std::string GetLower(std::string const& str)const;
    void ReadTranslations(std::ifstream & input);
    void TryReadTranslation(std::string const& str);
};

