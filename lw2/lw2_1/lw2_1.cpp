#include "stdafx.h"

using namespace std;

bool FindStreamSubStrings(ifstream & input, string const& search, vector<int> & foundRowsNumbers)
{
    string currStr;
    int currRow = 1;

    while (!input.eof())
    {
        getline(input, currStr);
        if (currStr.find(search) != string::npos)
        {
            foundRowsNumbers.push_back(currRow);
        }
        ++currRow;
    }
    return !foundRowsNumbers.empty();
}

void PrintNumbers(vector<int> const& numbers)
{
    for (auto const& item : numbers)
    {
        cout << item << '\n';
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
    vector<int> foundRowsNumbers;

    if (FindStreamSubStrings(input, subString, foundRowsNumbers))
    {
        PrintNumbers(foundRowsNumbers);
    }
    else
    {
        cout << "Text not found\n";
    }

    return 0;
}