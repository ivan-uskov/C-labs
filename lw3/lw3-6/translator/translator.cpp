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
    cout << "����������� ����� �" << eng << "�. ������� ������� ��� ������ ������ ���������." << endl;
    if (ReadLine(rus))
    {
        dictionary.AddTranslation(eng, rus);
        cout << "����� �" << eng << "� ��������� � ������� ��� �" << rus << "�." << endl;
    }
}

void AskForSaveChanges(CDictionary & dictionary)
{
    string str;
    cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << endl;
    if (ReadLine(str) && (str == "Y" || str == "y"))
    {
        dictionary.FlushNewWords();
        cout << "��������� ���������! ";
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

    cout << "�� ��������!" << endl;

    return 0;
}