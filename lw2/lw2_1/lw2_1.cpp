#include "stdafx.h"

using namespace std;

vector<int> FindStreamSubStrings(ifstream & input, string const& search)
{
    vector<int> results;
    string currStr;
    int currRow = 1;

    while (!input.eof())
    {
        getline(input, currStr);
        if (currStr.find(search) != string::npos)
        {
            results.push_back(currRow);
        }
        ++currRow;
    }
    return results;
}

void PrintSubStrings(vector<int> subStrings)
{
    if (!subStrings.empty())
    {
        for (vector<int>::const_iterator it = subStrings.cbegin(); it != subStrings.cend(); ++it)
        {
            cout << *it << '\n';
        }
    }
    else
    {
        cout << "Text not found\n";
    }
}

int main(int argc, char * argv[])
{
    const int PARAMS_COUNT = 2;
    if (argc <= PARAMS_COUNT)
    {
        printf("Expected arguments: [input_file] [outputfile]\n");
        return 1;
    }

    ifstream input(argv[1]);

    if (input.bad())
    {
        std::cout << "Input file doesn't exists!\n";
        return 1;
    }

    string subString(argv[2]);
    vector<int> found = FindStreamSubStrings(input, subString);
    PrintSubStrings(found);

    return 0;
}