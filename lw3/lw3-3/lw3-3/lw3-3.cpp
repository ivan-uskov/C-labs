#include "stdafx.h"
#include "CalculateWords.h"

using namespace std;

void PrintWords(ostream & output, WordFrequencies wordFrequencies)
{
    ostream_iterator<string> out(output);
    auto FormatPair = [](std::pair<string, size_t> pair)
    {
        return pair.first + to_string(pair.second) + "\n";
    };

    transform(wordFrequencies.begin(), wordFrequencies.end(), out, FormatPair);
}

int main(int argc, char* argv[])
{
    auto wordFrequencies = CalculateWordFrequencies(cin);
    PrintWords(cout, wordFrequencies);

    return 0;
}

