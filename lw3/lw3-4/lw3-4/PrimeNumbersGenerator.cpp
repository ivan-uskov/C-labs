#include "stdafx.h"
#include "PrimeNumbersGenerator.h"
#include <boost/iterator/counting_iterator.hpp>
#include <cmath>
#include <vector>

using namespace std;

void EraseNumberSequence(vector<bool> & numbers, const size_t start)
{
    size_t current = start + start;
    const size_t NUMBERS_SIZE = numbers.size();

    while (current < NUMBERS_SIZE)
    {
        numbers[current] = false;
        current += start;
    }
}

void EraseCompositeNums(vector<bool> & numbers)
{
    size_t currStartNum = 2;
    const size_t MAX_START_NUM = static_cast<size_t>(sqrt(numbers.size()));

    while (currStartNum <= MAX_START_NUM)
    {
        EraseNumberSequence(numbers, currStartNum++);
    }
}

bool CheckUpperBound(const size_t upperBound)
{
    return 1 < upperBound && upperBound <= std::numeric_limits<size_t>::max();
}

set<size_t> SieveToSet(vector<bool> const& sieve)
{
    const size_t FIRST_PRIME_NUM = 2;
    set<size_t> primes;

    for (size_t i = FIRST_PRIME_NUM; i < sieve.size(); ++i)
    {
        if (sieve[i])
        {
            primes.insert(primes.end(), i);
        }
    }

    return primes;
}

set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
    if (!CheckUpperBound(upperBound))
    {
        return {};
    }

    vector<bool> numbers(upperBound + 1, true);
    EraseCompositeNums(numbers);

    return SieveToSet(numbers);
}
