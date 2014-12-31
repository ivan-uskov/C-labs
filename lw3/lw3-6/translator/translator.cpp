#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

bool ReadLine(string & str)
{
    cout << "> ";
    getline(cin, str);
    return !str.empty();
}

bool ReadEngWord(string & str)
{
    
    return (ReadLine(str)) && (str != "...");
}

bool PrintTranslation(CDictionary const& dictionary, string const& eng)
{
    string rus(dictionary.Translate(eng));
    if (!rus.empty())
    {
        cout << rus << endl;
        return true;
    }
    return false;
}

void AskForAddTranslation(CDictionary & dictionary, string const& eng)
{
    string rus;
    cout << "Ќеизвестное слово У" << eng << "Ф. ¬ведите перевод или пустую строку дл€отказа." << endl;
    if (ReadLine(rus))
    {
        dictionary.AddTranslation(eng, rus);
        cout << "—лово У" << eng << "Ф сохранено в словаре как У" << rus << "Ф." << endl;
    }
}

void AskForSaveChanges(CDictionary & dictionary)
{
    string str;
    cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом." << endl;
    if (ReadLine(str) && (str == "Y" || str == "y"))
    {
        dictionary.FlushNewWords();
        cout << "»зменени€ сохранены! ";
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    CDictionary dictionary("../translations");
    if (dictionary.IsError())
    {
        cout << "Error in reading translations file(" << endl;
        return 1;
    }

    string eng, rus;
    while (ReadEngWord(eng))
    {
        if (!PrintTranslation(dictionary, eng))
        {
            AskForAddTranslation(dictionary, eng);
        }
    }

    if (dictionary.IsModified())
    {
        AskForSaveChanges(dictionary);
    }

    cout << "ƒо свидани€!" << endl;

    return 0;
}