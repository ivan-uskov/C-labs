#include "stdafx.h"
#include "BlanksRemover.h"

using namespace std;


int main(int argc, char* argv[])
{
    while (!cin.eof())
    {
        string str;
        getline(cin, str);

        cout << RemoveExtraSpaces(str) << endl;
    }

    return 0;
}
