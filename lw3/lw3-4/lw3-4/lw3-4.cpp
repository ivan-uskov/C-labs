#include "stdafx.h"
#include "PrimeNumbersGenerator.h"
#include <boost/lexical_cast.hpp>

using namespace std;

size_t GetUpperBound(string const& arg)
{
    auto upperBound = boost::lexical_cast<size_t>(arg);
    if (!CheckUpperBound(upperBound))
    {
        throw bad_cast("upper bound less then 2 or more then max size_t");
    }
    return upperBound;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Enter Parameter: upper bound" << endl;
        return 1;
    }

    size_t upperBound;
    try
    {
        upperBound = GetUpperBound(argv[1]);
    }
    catch (std::bad_cast const& e)
    {
        cout << "Invalid argument!" << endl;
        return 1;
    }

    auto primes = GeneratePrimeNumbersSet(upperBound);

    ostream_iterator<size_t> output(cout, " ");
    copy(primes.begin(), primes.end(), output);
    cout << endl;

    return 0;
}

