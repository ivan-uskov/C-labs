#include "stdafx.h"
#include "WordCounter.h"

using namespace std;

int main(int argc, char* argv[])
{
    string str;
    CWordCounter counter;

    while (cin >> str)
    {
        counter(str);
    }

    counter.PrintWords(cout);

    return 0;
}

