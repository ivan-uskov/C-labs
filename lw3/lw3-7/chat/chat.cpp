#include "stdafx.h"
#include "Censure.h"

using namespace std;

void PrintCensured(CCensure const& censure, string const& str)
{
    string word;
    istringstream iss(str);
    while (iss >> word)
    {
        if (censure(word))
        {
            cout << word << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Argument occured, usage: noncensured words file path!" << endl;
        return 1;
    }

    CCensure censure(argv[1]);
    if (censure.IsError())
    {
        cout << "Noncensured words filevdoesn't exists!" << endl;
        return 1;
    }

    while (!cin.eof())
    {
        string str;
        getline(cin, str);
        PrintCensured(censure, str);
    }

    return 0;
}

