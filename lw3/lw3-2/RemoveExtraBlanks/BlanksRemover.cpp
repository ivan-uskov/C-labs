#include "stdafx.h"
#include "BlanksRemover.h"

using namespace std;

string RemoveExtraSpaces(string const& arg)
{
    string str, temp;
    istringstream iss(arg);
    istream_iterator<string> start(iss);
    istream_iterator<string> end;

    copy(start, end, str.begin());
    /*
    while (iss >> temp)
    {
        str += temp + " ";
    }*/
    if (str.size() > 0)
    {
        str.pop_back();
    }

    return str;
}