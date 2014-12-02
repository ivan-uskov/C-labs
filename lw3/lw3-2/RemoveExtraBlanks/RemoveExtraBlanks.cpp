#include "stdafx.h"
#include "BlanksRemover.h"

using namespace std;

int main(int argc, char* argv[])
{
    string str;
    getline(cin, str);

    cout << RemoveExtraSpaces(str) << endl;

    return 0;
}
