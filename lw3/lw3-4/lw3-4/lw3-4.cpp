#include "stdafx.h"
#include "PrimeNumbersGenerator.h"
#include <boost/lexical_cast.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Enter Parameter: upper bound" << endl;
        return 1;
    }

    auto primes = GeneratePrimeNumbersSet(boost::lexical_cast<int>(argv[1]));

    ostream_iterator<int> output(cout, " ");
    copy(primes.begin(), primes.end(), output);
    cout << endl;

    return 0;
}

