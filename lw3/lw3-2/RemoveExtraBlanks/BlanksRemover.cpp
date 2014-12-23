#include "stdafx.h"
#include "BlanksRemover.h"

using namespace std;

bool IsNotSpace(char ch)
{
    return ch != ' ';
}

string::const_iterator FindFirstNotSpaceChar(string const& str)
{
    auto firstCharId = str.find_first_not_of(" ");
    return (firstCharId != string::npos) ? str.begin() + firstCharId : str.begin();
}

string RemoveExtraSpaces(string const& arg)
{
    string result;
    result.reserve(arg.size());

    //true is current character is part of word
    bool isWord = true;

    //print words and add spaces at beginning
    for (auto it = FindFirstNotSpaceChar(arg); it < arg.end(); ++it)
    {
        if (IsNotSpace(*it))
        {
            if (!isWord)
            {
                isWord = true;
                result.push_back(' ');
            }
            result.push_back(*it);
        }
        else
        {
            isWord = false;
        }
    }

    return result;
}

string RemoveExtraSpacesSlow(string const& arg)
{
    istringstream iss(arg);
    string result, tmp;

    while (iss >> tmp)
    {
        result += tmp + ' ';
    }

    if (result.size() > 0)
    {
        result.pop_back();
    }
    return result;
}