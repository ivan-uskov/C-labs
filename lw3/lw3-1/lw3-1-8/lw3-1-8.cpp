#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<double> buffer;
    if (!ReadVecOfDouble(cin, buffer))
    {
        cout << "Please enter a double number sequence!" << endl;
        return 1;
    }

    ProcessVector(buffer);

    PrintVector(cout, buffer, " ");

    return 0;
}

