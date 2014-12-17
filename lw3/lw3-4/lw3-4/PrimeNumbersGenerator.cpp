#include "stdafx.h"
#include "PrimeNumbersGenerator.h"
#include <boost/iterator/counting_iterator.hpp>
#include <cmath>

using namespace std;

void EraseNumSequence(set<int> & numbers, const int startNum)
{
    const int MAX_NUMBER = *numbers.rbegin();
    int erasedItem = startNum + startNum;
    set<int>::iterator it;

    while (erasedItem <= MAX_NUMBER)
    {
        if ((it = numbers.find(erasedItem)) != numbers.end())
        {
            numbers.erase(it);
        }
        erasedItem += startNum;
    }
}

void EraseComponentNums(set<int> & numbers, const int upperBound)
{
    int maxSequnceStartNum = static_cast<int>(sqrt(upperBound));
    auto item = numbers.begin();

    while (*item <= maxSequnceStartNum)
    {
        EraseNumSequence(numbers, *item);
        ++item;
    }
}

bool CheckUpperBound(const int upperBound)
{
    return 1 < upperBound && upperBound <= MAX_UPPER_BOUND;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    if (!CheckUpperBound(upperBound))
    {
        return {};
    }

    set<int> numbers
    (
        boost::counting_iterator<int>(2),
        boost::counting_iterator<int>(upperBound + 1)
    );

    EraseComponentNums(numbers, upperBound);

    return numbers;
}
